#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "mensaje.pb.h" //include de la libreria
using namespace std;
using namespace chat;

#define BUFSIZE 1024

string usuario; //se guarda nombre de usuario
string ip; //se guarda la ip del usuario
int IdGlobal; //id global para el user
void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void CambioStatus(int ClienteIdP, string ClientStatusP, int clientSocket, char *Buffer)
{
    //Creamos un changeStatusRequest
    cout << "Preparando envio de status" << endl;
    ChangeStatusRequest *CambioStatusRequest(new ChangeStatusRequest);
    CambioStatusRequest->set_status(ClientStatusP);
    // Se crea instancia de Mensaje, se setea los valores deseados
    ClientMessage *message(new ClientMessage);
    message->set_option('3');
    message->set_userid(ClienteIdP);
    message->set_allocated_changestatus(CambioStatusRequest);
    //Se hace binario y string y luego char y se envia
    string binary;
    message->SerializeToString(&binary);

    char cstr[binary.size() + 1];
    strcpy(cstr, binary.c_str());
    send(clientSocket, cstr, strlen(cstr), 0);
}

int main(int argc, char *argv[])
{
    cout << "Ingrese el nombre de usuario: ";
    while (getline(cin, usuario))
    if (usuario != "")
      break;
    
    cout << "Ingrese su ip: ";
    while (getline(cin, ip))
    if (ip != "")
      break;
    
    //Import google Protocol
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    bool salir = false;
    char buffer[BUFSIZE];

    if (argc < 3)
    {
        fprintf(stderr, "Uso de %s puesto -- hostname \n", argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        error("ERROR, No se ha podido establecer un enlace con el SOCKET");

    server = gethostbyname(argv[1]);

    if (server == NULL)
    {
        fprintf(stderr, "ERROR, No existe la dirección del Host\n");
        exit(0);
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR, No se ha podido establecer una conexión con el servidor\n");
    }
    else
    {
        printf("Espere, el servidor está aprobando su solicitud\n");
        // Se crea instacia tipo MyInfoSynchronize y se setean los valores deseables
        MyInfoSynchronize *miInfo(new MyInfoSynchronize);
        miInfo->set_username(usuario);
        miInfo->set_ip(ip);

        // Se crea instancia de Mensaje, se setea los valores deseados
        ClientMessage *m(new ClientMessage);
        m->set_option(1);
        m->set_allocated_synchronize(miInfo);

        // Se serializa el message a string
        string binary;
        m->SerializeToString(&binary);

        //Convertimos a char
        char cstr[binary.size() + 1];
        strcpy(cstr, binary.c_str());

        //Enviamos por el socket todo
        send(sockfd, cstr, strlen(cstr), 0);
        printf("PASO 1 Ya envie el mensaje por protocolo, esperando a que le llegue....\n");
    }
    //Recibir el tercer paso
    recv(sockfd, buffer, BUFSIZE, 0);
    ServerMessage *ServerResponse(new ServerMessage);
    ServerResponse->ParseFromString(buffer);
    cout << "ID del server: " << ServerResponse->myinforesponse().userid() << endl;
    int idServer = ServerResponse->myinforesponse().userid(); //id que el servidor asigno al cliente
    IdGlobal = idServer;                                      //igualamos la Idglobal
    //Construimos el aAcknowledge
    MyInfoAcknowledge *ack(new MyInfoAcknowledge);
    ack->set_userid(idServer);

    ClientMessage *m2(new ClientMessage);
    m2->set_option('6');
    m2->set_userid(idServer);
    m2->set_allocated_acknowledge(ack);
    //lo volvemos string
    string binary2;
    m2->SerializeToString(&binary2);
    //lo volvemos char
    char cstr2[binary2.size() + 1];
    strcpy(cstr2, binary2.c_str());
    send(sockfd, cstr2, strlen(cstr2), 0);
    printf("PASO 3 Ya le dije al sERVER QUE SI QUIERO SER SU AMIGO\n");

    do
    {
        printf("\n");
        do
        {
            printf("Cliente: ");
            bzero(buffer, BUFSIZE);
            //CambioStatus(IdGlobal, "Inactivo", sockfd, buffer);
            fgets(buffer, BUFSIZE, stdin);
            send(sockfd, buffer, BUFSIZE, 0);
            if (*buffer == '#')
            {
                send(sockfd, buffer, BUFSIZE, 0);
                salir = true;
            }

        } while (*buffer != '#');

    } while (!salir);

    printf("CONEXIÓN TERMINADA\n");
    close(sockfd);
    google::protobuf::ShutdownProtobufLibrary(); //close google protocol
    return 0;
}
