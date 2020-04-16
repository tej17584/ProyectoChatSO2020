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
using namespace std;
// #include "mensaje.pb.h"

// ------------------------------------------------S T A R T -----------------------------------------// 
#define MAX_CLIENTS 35 // number of students in class (assuming each one will be a client)
#define BUFSIZE 1024

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
};

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
		strcpy(buffer, "EL SERVIDOR HA ESTABLECIDO CONEXIÓN DE FORMA CORRECTA\n");
		send(cli_socket, buffer, cli_len, 0);

		do
		{
			printf("\nCLIENTE: ");
			recv(cli_socket, buffer, BUFSIZE, 0);
			printf("%s", buffer);
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

	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR, No se pudo realizar la función Bind");

	if (listen(sockfd, MAX_CLIENTS) == 0)
		printf("Escuchando por nuevos clientes\n");
	else
		error("ERROR, No se ha podido establecer la funcion de escucha");

	int client_in_room = 0;

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
	return 0;
}