<h1 align="center">
<br>
  <img src="https://cdn2.myket.ir/image/myket/icon/bd83259a-d072-4e38-b7cf-755950f7f97b_.png" alt="Voto" width="556"> 
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


##Compilación
El  proyecto consta de un servidor y la cantidad de clientes que se quieran hacer. Para poder crear un cliente primero hay que tener un servidor creado.

#Servidor:
Adentro de la carpeta de server correr el siguiente comando para compilar:
```bash
g++ server.cpp mensaje.pb.cc -o server -lpthread -lprotobuf
```
para crear el servidor correr el siguiente comando cambiando la palabra port por el puerto en donde se quiere crear el servidor:
```bash
./server port
```
 
#Cliente:
Adentro de la carpeta de client correr el siguiente comando para compilar:
```bash
g++ client.cpp mensaje.pb.cc -o client -lpthread -lprotobuf
```
para crear el cliente correr el siguiente comando cambiando la palabra port por el puerto en donde se creo el servidor:
```bash
./client localhost port
```