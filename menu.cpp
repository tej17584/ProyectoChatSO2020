#include <iostream>
#include <string>

using namespace std;

int opcion;
string x;
bool adentro = true;


void confirmacion() {
    cout << "Enviando confirmación\n";
}

void respuesta() {
    cout << "El servidor ha recibido la solicitud\n";
}

void envio() {
    cout << "Enviando solicitud al servidor\n";
}


void menu(){
    cout << "\n";
    cout << "---------------------------------------------------\n";
    cout << "Bienvenido a Chat SISTOS\n";
    cout << "---------------------------------------------------\n";
    cout << "\n";
    cout << "Ingrese el numero de la opcion que deasea ejecutar\n";
    cout << "1. Mensaje directo\n";
    cout << "2. Broadcasting (Chat general)\n";
    cout << "3. Cambio de status\n";
    cout << "4. Listado de usuarios\n";
    cout << "5. Informacion de un usuario\n";
    cout << "0. Salir \n";
    cout << "\n";
}

int main() {
    while (adentro == true) {
        menu();
        
        cout << "Opcion: ";
        cin >> opcion;
        cout << "\n";

        if (opcion == 0) {
            adentro = false;
        }
        
        //Mensaje directo
        else if (opcion == 1) {
            cout << "MENSAJE DIRECTO\n";
            cout << "Ingrese el nombre de usuario seguido del mensaje que desea enviar\n";
            cout << "Ejemplo: Alejandro Hola\n";
            cout << "\n";
            
            cin >> x;
            cout << x;
        }
        
        //Broadcast
        else if (opcion == 2) {
            cout << "MENSAJE DIRECTO\n";
            cout << "Ingrese el mensaje que desea enviar\n";
            cout << "\n";
            
            cin >> x;
            cout << x;
        }
        
        //Cambio de status
        else if (opcion == 3) {
            cout << "MENSAJE DIRECTO\n";
            cout << "Ingrese el numero de la opcion que desea:\n";
            cout << "1. Activo\n";
            cout << "2. Ocupado\n";
            cout << "3. Inactivo\n";
            cout << "\n";
            
            cout << "Opcion: ";
            cin >> x;
            if (x > 3) {
                cout << "Ingrese un numero valido\n"
            }
            else{
                cout << x;
            }
        }
        
        //Listado de usuarios
        else if (opcion == 4) {
            cout << "Listado de los usuarios conectados:\n";
            cout << "\n";
        }
        
        //Informacion de un usuario
        else if (opcion == 5) {
            cout << "Informacion de un usuario:\n";
            cout << "Ingrese el nombre del usuario que desea ver\n";
            
            cin >> x;
            cout << x;
        }
        
        //validacion
        else if (opcion > 5) {
            cout << "ERROR. Ingrese un numero valido";
        }
    }
    return 0;
}



