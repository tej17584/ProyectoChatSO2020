// To compile: g++ -o server server.cpp -lpthread
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <vector>
#include <string.h>
#include <sstream>
#include "mensaje.pb.h" //include de la libreria
using namespace std;
using namespace chat;
// #include "mensaje.pb.h"

// ------------------------------------------------S T A R T -----------------------------------------//
#define MAX_CLIENTS 35 // number of students in class (assuming each one will be a client)
#define BUFSIZE 1024
int portno2;

class ClienteData
{
public:
	struct sockaddr_in cli_addr; //ClienteSocket addres
	int fdconn;					 //fFile de la conexion es un int
	int ClientID;				 //identificador unico
	string ClientIP = "";		 //Direccion IP del cliente
	string ClientStatus = "";	 //Estado del cliente
	string ClientUserName = "";	 //username
};

ClienteData listadoClientes[MAX_CLIENTS]; //almacenamiento de los clientes
//this method define error to show in console
void error(const char *msg)
{
	perror(msg);
	exit(1);
}
//define composite data to connect with socket and client
struct connection_data
{
	int cli_socket;
	int tid;
	struct sockaddr_in cli_addr;
	socklen_t cli_len;
	int opcionServer;
};

//OPCION CAMBIO STATU
void CambioStatus(int clientSocket, char *Buffer)
{
	ClientMessage *m(new ClientMessage);
	m->ParseFromString(Buffer);
	//cout << "El nuevo estatus sera : " << m->changestatus().status() << endl;

	//Cambiamos el estado
	int i;
	for (i = 0; i < MAX_CLIENTS; i++)
	{
		ClienteData Cliente = listadoClientes[i];
		if (Cliente.ClientID == m->userid())
		{

			Cliente.ClientStatus = m->changestatus().status();
			listadoClientes[i].ClientStatus = Cliente.ClientStatus;
		}
	}

	//Ahora enviamos la confirmacion
	//ChangeStatusResponse * status_res(new ChangeStatusResponse);
	ChangeStatusResponse *SR(new ChangeStatusResponse);
	SR->set_status(m->changestatus().status());
	SR->set_userid(m->userid());

	ServerMessage *server_res(new ServerMessage);
	server_res->set_option(6);
	server_res->set_allocated_changestatusresponse(SR);

	// Se serializa la respuesta a string
	string binary;
	server_res->SerializeToString(&binary);

	char cstr[binary.size() + 1];
	strcpy(cstr, binary.c_str());
	send(clientSocket, cstr, strlen(cstr), 0);
}

//OPCION CAMBIO STATU
void GetUserInfo(int clientSocket, char *Buffer)
{

	ClientMessage *m(new ClientMessage);
	m->ParseFromString(Buffer);
	if (m->connectedusers().userid() < 0)
	{
		cout << "Se envio algo menor a 0 " << m->connectedusers().userid() << endl;
		//Construimos  un connectedUserResponse
		//Construimos mensaje dle server

		ConnectedUserResponse *CUR(new ConnectedUserResponse);
		ServerMessage *server_res(new ServerMessage);
		//El 5 es la response del usuario
		server_res->set_option(5);

		//Buscamos la info de la persona
		//Cambiamos el estado
		int i;
		for (i = 1; i < MAX_CLIENTS; i++)
		{
			//Construimos un connectedUSerREquest
			ClienteData Cliente = listadoClientes[i];
			if (Cliente.ClientUserName != "")
			{ //Asignamos valores al protocolo
				ConnectedUser *cu = CUR->add_connectedusers();
				cout << "A : " << Cliente.ClientID << endl;
				cout << "B: " << Cliente.ClientUserName << endl;
				cout << "C: " << Cliente.ClientIP << endl;
				cout << "D: " << Cliente.ClientStatus << endl;
				cu->set_userid(Cliente.ClientID);
				cu->set_username(Cliente.ClientUserName);
				cu->set_ip(Cliente.ClientIP);
				cu->set_status(Cliente.ClientStatus);
			}
		}
		server_res->set_allocated_connecteduserresponse(CUR);
		// Se serializa la respuesta a string
		string binary;
		server_res->SerializeToString(&binary);

		char cstr[binary.size() + 1];
		strcpy(cstr, binary.c_str());
		send(clientSocket, cstr, strlen(cstr), 0);
		cout << "Enviando info al cliente de TODOS los clientes" << endl;
	}
	else
	{

		cout << "El UserName a consultar es: " << m->connectedusers().username() << endl;
		//Construimos  un connectedUserResponse
		ConnectedUserResponse *CUR(new ConnectedUserResponse);
		bool encontrado;
		//Buscamos la info de la persona
		//Cambiamos el estado
		int i;
		for (i = 0; i < MAX_CLIENTS; i++)
		{
			ClienteData Cliente = listadoClientes[i];

			if (Cliente.ClientUserName == m->connectedusers().username())
			{
				//Construimos un connectedUSerREquest
				ConnectedUser *cu = CUR->add_connectedusers();
				//Asignamos valores al protocolo
				cu->set_userid(Cliente.ClientID);
				cu->set_username(Cliente.ClientUserName);
				cu->set_ip(Cliente.ClientIP);
				cu->set_status(Cliente.ClientStatus);
				encontrado = true;
			}
		}

		if (encontrado == true)
		{
			//Construimos mensaje dle server
			ServerMessage *server_res(new ServerMessage);
			//El 5 es la response del usuario
			server_res->set_option(5);
			server_res->set_allocated_connecteduserresponse(CUR);
			// Se serializa la respuesta a string
			string binary;
			server_res->SerializeToString(&binary);

			char cstr[binary.size() + 1];
			strcpy(cstr, binary.c_str());
			send(clientSocket, cstr, strlen(cstr), 0);
			cout << "Enviando info al cliente" << endl;
		}
		else if (encontrado == false)
		{
			//Construimos mensaje dle server
			ServerMessage *server_res(new ServerMessage);
			//El 3 es para error
			server_res->set_option(3);
			ErrorResponse *error(new ErrorResponse);
			error->set_errormessage("NO existe ningun usuario con ese nombre, intenta otra vez");

			string binary;
			server_res->SerializeToString(&binary);

			char cstr[binary.size() + 1];
			strcpy(cstr, binary.c_str());
			send(clientSocket, cstr, strlen(cstr), 0);
			cout << "Enviando info de ERROR al cliente" << endl;
		}
	}
}

//define connection with client
void *connectClient(void *args)
{
	char buffer[BUFSIZE];
	bool out_chat_room = false;

	struct connection_data *data;
	data = (struct connection_data *)args;

	struct sockaddr_in serv_addr;
	int cli_socket = data->cli_socket;
	int tid = data->tid;
	struct sockaddr_in cli_addr = data->cli_addr;
	socklen_t cli_len = data->cli_len;

	if (cli_socket > 0)
	{
		//strcpy(buffer, "EL SERVIDOR HA ESTABLECIDO CONEXION DE FORMA CORRECTA\n");
		//Este es el envio del server
		//send(cli_socket, buffer, cli_len, 0);

		//En vez de un send, hacemos un receive
		recv(cli_socket, buffer, BUFSIZE, 0);
		//read(cli_socket, buffer, portno2);
		// Se deserealiza el string a un objeto Mensaje
		ClientMessage *m(new ClientMessage);
		m->ParseFromString(buffer);

		// Se puede accesar a los valores de la siguiente manera:
		//cout << "Opcion general enviada.... : " << m->option() << endl;
		//cout << "Username: " << m->synchronize().username() << endl;
		//cout << "Client IP: " << m->synchronize().ip() << endl;

		int DefaultOpcion = m->option();

		if (DefaultOpcion == 1) //opcion 1 es que se quiere conectar, entonces mandamos de vuelta
		{
			// Se crea instancia de respuesta para el cliente.
			MyInfoResponse *response(new MyInfoResponse);
			response->set_userid(tid);
			ServerMessage *Server_Message(new ServerMessage);
			Server_Message->set_option('4');
			Server_Message->set_allocated_myinforesponse(response);
			// Se serializa la respuesta a string
			string binary;
			Server_Message->SerializeToString(&binary);
			//volvemos char
			char cstr[binary.size() + 1];
			strcpy(cstr, binary.c_str());
			send(cli_socket, cstr, strlen(cstr), 0); //envio desde el server
			printf("PASO 2 Le contesto al cliente que me reciba....\n");

			//Ahora viene el read del acknolowdge
			recv(cli_socket, buffer, BUFSIZE, 0);
			//string ret2(buf, PORT); //se convierte el char a string

			ClientMessage *m2(new ClientMessage);
			//message2->ParseFromString(ret2);
			m2->ParseFromString(buffer);

			cout << "Acknowledge ID(deberia ser el mismo que el idcliente, procedo a crearte uno:  " << m2->userid() << endl;

			int currentid;
			//Le creamos un usuario en nuestra clase
			ClienteData clienteNuevo = listadoClientes[tid];
			if (m->synchronize().username() != clienteNuevo.ClientUserName && m2->userid() != clienteNuevo.ClientID)
			{
				clienteNuevo.cli_addr = data->cli_addr;
				clienteNuevo.fdconn = cli_socket;
				clienteNuevo.ClientID = m2->userid();
				currentid = m2->userid();
				clienteNuevo.ClientStatus = "Activo";
				clienteNuevo.ClientUserName = m->synchronize().username();
				clienteNuevo.ClientIP = m->synchronize().ip();
				listadoClientes[m2->userid()] = clienteNuevo;

				cout << "Felicidades, te agregaste al server con los siguientes datos: " << endl;
				cout << "Tu ID unico es: " << listadoClientes[m2->userid()].ClientID << endl;
				cout << "Tu Nombre es: " << listadoClientes[m2->userid()].ClientUserName << endl;
				cout << "Tu IP es: " << listadoClientes[m2->userid()].ClientIP << endl;
				cout << "Con Status: " << listadoClientes[m2->userid()].ClientStatus << endl;
			}
			else
			{
				cout << "ERROR al intentar registar. Pudo pasar por:..." << endl;
				cout << "1. Id o nombre ya existe" << endl;
				cout << "2. Ya no tenemos capacidad wey" << endl;
			}
			bzero(buffer, BUFSIZE);
		}

		int OpcionGeneral;
		do
		{
			printf("\nCLIENTE: ");
			recv(cli_socket, buffer, BUFSIZE, 0);

			//ecibimos el mensaje del cliente
			ClientMessage *messageGeneral(new ClientMessage);
			//message2->ParseFromString(ret2);
			messageGeneral->ParseFromString(buffer);
			cout << "Opcion general enviada.... : " << messageGeneral->option() << endl;
			OpcionGeneral = messageGeneral->option();
			if (OpcionGeneral == 3)
			{
				CambioStatus(cli_socket, buffer);
			}
			else if (OpcionGeneral == 2)
			{
				GetUserInfo(cli_socket, buffer);
			}
			else
			{
				printf("%s", buffer);
			}

			if (*buffer == '#')
			{
				printf("\nSERVER: El cliente ha abandonado la sala\nF principal\n");
				out_chat_room = true;
			}
		} while (*buffer != '#');

		printf("Se ha finalizado la conexión con: %s\n", inet_ntoa(cli_addr.sin_addr));
		close(cli_socket);
		out_chat_room = false;
	}

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	//Import google Protocol
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	//declare values
	int sockfd, portno;
	struct sockaddr_in serv_addr;
	vector<pthread_t> threadVector;
	pthread_t threadPool[MAX_CLIENTS];
	void *retvals[MAX_CLIENTS];

	if (argc < 2)
	{
		fprintf(stderr, "ERROR, No se ha podido obtener el puerto\n");
		exit(1);
	}
	//init a new SOCKET
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR, No se puedo establecer el enlace con el SOCKET");

	//sets all values in a buffer to zero
	bzero((char *)&serv_addr, sizeof(serv_addr));

	// <<portono>> stores the port number on which the server accepts connections
	portno = atoi(argv[1]);

	//setup (host_addr) to create Bind()
	serv_addr.sin_family = AF_INET;

	//IP
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	//!! convert int to network byte to use
	serv_addr.sin_port = htons(portno);
	portno2 = portno;

	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR, No se pudo realizar la función Bind");

	if (listen(sockfd, MAX_CLIENTS) == 0)
		printf("Escuchando por nuevos clientes\n");
	else
		error("ERROR, No se ha podido establecer la funcion de escucha");

	int client_in_room = 1;

	while (client_in_room < MAX_CLIENTS)
	{
		struct sockaddr_in cli_addr;
		socklen_t cli_len = sizeof(cli_addr);

		int newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len);

		if (newsockfd < 0)
			error("ERROR, No se pudo establecer conexión con cliente");
		else
		{
			printf("NUEVO CLIENTE HA INGRESADO A LA PLATAFORMA!\n");
		}
		//define composite data to get data and conection
		struct connection_data new_connection;
		new_connection.cli_socket = newsockfd;
		new_connection.cli_addr = cli_addr;
		new_connection.cli_len = cli_len;
		new_connection.tid = client_in_room;

		pthread_create(
			&threadPool[client_in_room],
			NULL,
			connectClient,
			(void *)&new_connection);

		client_in_room++;
	}

	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (pthread_join(threadPool[i], &retvals[i]) < 0)
			error("ERROR, No ha sido  posible cerrar el Thread Pool");
	}
	close(sockfd);
	google::protobuf::ShutdownProtobufLibrary(); //close google protocol
	return 0;
}