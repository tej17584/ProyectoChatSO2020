<h1 align="center">
<br>
  <img src="https://cdn2.myket.ir/image/myket/icon/bd83259a-d072-4e38-b7cf-755950f7f97b_.png" alt="Voto" width="400"> 
<br>
<br>Proyecto Chat - Sistemas Operativos
</h1>
    
<p align="center">
  
  <a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/static/v1?label=License&message=NoLicense&color=<COLOR>" alt="No license">
  </a>
</p>

<p align="center">Proyecto Universitario :mortar_board:</p>

<hr />


## Descripción
Este proyecto es parte del curso de Sistemas Operativos de la Universidad del Valle de Guatemala. El objetivo es crear un chat mediante uno o varios clientes que se comunican por medio de un servidor. Esto es posible mediante la implementación de sockets, pthreads y el uso de comunicación de procesos para logar un mejor manejo de recursos y viabilidad. También está basado en el medio de Protocolo de Google llamado Protobuf. 

## Requisitos:
* Protobuf de google links en documentación.
* Compilador de C (GCC y G++)
* Un sabor de Ubuntu


## Compilación
El  proyecto consta de un servidor y la cantidad de clientes que se quieran hacer. Para poder crear un cliente primero hay que tener un servidor creado.

### Servidor:
En una terminal ir a la carpeta server, ya adentro de la carpeta correr el siguiente comando para compilar:
```bash
g++ server.cpp mensaje.pb.cc -o server -lpthread -lprotobuf
```
Para levantar el servidor correr el siguiente comando cambiando la palabra "port" por el puerto en donde se desea crear el servidor (8080 por ejemplo):
```bash
./server port
```
 
### Cliente:
En otra terminal ir a la carpeta client, ya adentro de la carpeta correr el siguiente comando para compilar:
```bash
g++ client.cpp mensaje.pb.cc -o client -lpthread -lprotobuf
```
Ya con el servidor levantado, correr el siguiente comando, cambiando la palabra "port" por el puerto en donde se creó el servidor, para crear un cliente:
```bash
./client localhost port
```
Si se desea crear otro cliente se deben de seguir los mismo pasos en otra terminal.


## Funcionamiento:
Al momento de tener el servidor levantado y crear un cliente en la terminal de cliente se pedira un nombre de usuario y una ip (puede ser cualquier número).
El menu del chat tiene las siguientes 6 opciones:

#### Mensaje directo:
Para que funcione se necesita que existan al menos 2 usuarios para poder enviarse mensajes entre ellos, al momento de escoger esta opcion se le pedira que ingrese el nombre de usuario y el id del usuario al que se le quiere mandar el mensaje (si no sabe la información necesaria, puede correr la opción 4 antes).

#### Broadcast:
Broadcast es un chat en donde el mensaje que se envia le llegara a todos los usuarios que esten conectados al servidor
Para que funcione se necesita que existan al menos 2 usuario, al momento de escoger esta opcion se pedira que ingrese el mensaje que desea enviar.


#### Camibo de status:
Cada cliente tiene un status asociado, por default el status es "Activo". Al momento de escoger esta opción se pedira ingrese 1, 2 o 3 dependiendo del status al que quiera cambiar.

#### Listado de usuarios:
Al momento de escoger esta opción se desplieraga un listado con todos los usuarios que esten conectados.  

#### Información de usuario:
Al momento de escoger esta opción se pedira que ingrese el nombre de usuario del que quiere ver la información general.

#### Salir:
Al momento de escoger esta opción el usuario sera borrado del servidor y dejara de funcionar el chat para ese usuario.

## Links y Documentación:
### Threads 
* https://www.geeksforgeeks.org/reader-writer-problem-using-monitors-pthreads/
* https://blog.programster.org/php-multithreading-pool-example
* https://computing.llnl.gov/tutorials/pthreads/

### Protobuf
* https://vorbrodt.blog/2019/03/10/protocol-buffers-or-how-to-serialize-data/
* https://developers.google.com/protocol-buffers/docs/cpptutorial
* https://developers.google.com/protocol-buffers/docs/downloads?hl=es-419

### Modelo Cliente-Servidor
* https://github.com/lytsing/protobuf-demo 
* https://www.bogotobogo.com/cplusplus/sockets_server_client.php

### Sockets
* http://www.linuxhowtos.org/C_C++/socket.htm
* https://www.geeksforgeeks.org/introducing-threads-socket-programming-java/
