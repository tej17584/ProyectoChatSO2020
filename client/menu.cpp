#include <iostream>
#include <stdio.h>

using namespace std;

//metodos donde se imprime un mensaje dependiendo del estado del servidor
void confirmacion()  {
    cout << "Enviando confirmación\n";
}

void respuesta()  {
    cout << "El servidor ha recibido la solicitud\n";
}

void envio()  {
    cout << "Enviando solicitud al servidor\n";
}

//metodo para hacer cambio de estatus
void cambioEstatus() {
    //variable para ver la opcion que se desea realizar
    int var;
    //variable donde se guarda el estado
    string input3;
    
    //menu de cambio de estado
    do
    {
        cout << "Cambio de estatus\n";
        cout << "Ingrese el numero de la opcion que desea:\n";
        cout << "1. Activo\n" ;
        cout << "2. Ocupado\n" ;
        cout << "3. Inactivo\n" ;
        cout << "4. Salir\n" ;
        cout << "\n" ;
        
        do{
            cout <<  "Introduzca la opcion que desea ejecutar (1-4 : \n" ;
            cin >> var;
            cout <<  "\n";
        }
        
        while ( var < 1 || var > 4 );
            
            switch (var)
            {
                //Activo
                case 1:
                    cout << "Cambio a estatus Activo\n" ;
                    input3 = "Activo";
                    var = 4;
                    break;
                 
                //Ocupado
                case 2:
                    cout << "Cambio a estatus Ocupado\n" ;
                    input3 = "Ocupado";
                    var = 4;
                    break;
                
                //Inactivo
                case 3:
                    cout << "Cambio a estatus Inactivo\n" ;
                    input3 = "Inactivo";
                    var = 4;
                    break;
            }
        } while ( var != 4 );
}


//funcion de broadcast
//void broadcast() {
//
//    string opcion1;
//    cout << "-------------------\n";
//    cout << "BROADCAST\n";
//    cout << "-------------------\n";
//    cout << "\n";
//
//    cout << "Ingrese su mensaje o ingrese 0 para regresar al menu\n";
//    while (getline(cin, opcion1))
//    if (opcion1 != "")
//      break;
//    cout <<  "\n";
//
//    if (opcion1 == "0") {
//        menu();
//    }
//    else{
//        cout << "mensaje";
//    }
//}


int main()  {
    //variable para ver la opcion que se desea realizar
    int opcion;
    string opcion1;
    
    //variables donde se guarda el input del usuario
    char input11 [20];
    string input12 = "";
    

    string input2 = "";
    
    char input5 [20];
    
    //menu principal del chat
    do
    {
        cout << "\n";
        cout << "---------------------------------------------------\n";
        cout << "Bienvenido a Chat SISTOS\n";
        cout << "---------------------------------------------------\n";
        cout << "\n";
        cout << "Ingrese el numero de la opcion que deasea ejecutar\n";
        cout << "1. Mensaje directo\n";
        cout << "2. Broadcasting (Chat general) \n";
        cout << "3. Cambio de status\n";
        cout << "4. Listado de usuarios\n";
        cout << "5. Informacion de un usuario\n";
        cout << "6. Salir \n";
        cout << "\n";
        
        do{
            cout <<  "Introduzca la opcion que desea ejecutar (1-6): \n";
            cin >> opcion;
            cout <<  "\n";
        }
        
        while ( opcion < 1 || opcion > 6 );
        
        switch (opcion)
        {
            //Mensaje directo
            case 1:
                cout << "MENSAJE DIRECTO\n";
                cout << "Ingrese el nombre de usuario\n";
                cin.sync();
                cin >> input11;
                cout << "\n";
                
                cout << "Ingrese el mensaje que desea enviar\n";
                while (getline(cin, input12))
                if (input12 != "")
                  break;
                cout << "\n";
                
                cout << "Usuario:\n";
                cout << input11;
                cout << "\n";
                cout << "Mensaje:\n";
                cout << input12;
                cout << "\n";
                break;
             
            //Broadcast
            case 2:
                cout << "-------------------\n";
                cout << "BROADCAST\n";
                cout << "-------------------\n";
                cout << "\n";

                cout << "Ingrese su mensaje o ingrese 0 para regresar al menu\n";
                while (getline(cin, opcion1))
                if (opcion1 != "")
                  break;
                cout <<  "\n";
                cout << "mensaje: " << opcion1;
                cout <<  "\n";
                
                if (opcion1 == "0") {
                    break;
                }
                else{
                    while (opcion1 != "0") {
                        cout << "Ingrese su mensaje o ingrese 0 para regresar al menu\n";
                        while (getline(cin, opcion1))
                        if (opcion1 != "")
                          break;
                        cout <<  "\n";
                        cout << "mensaje: " << opcion1;
                        cout <<  "\n";
                    }
                }
                break;
            
            //Cambio de estatus
            case 3:
                cambioEstatus();
                break;
               
            //Listado de usuarios
            case 4:
                cout << "Listado de usuarios registrados\n";
                break;
              
            //Informacion de usuario
            case 5:
                cout << "Informacion de usuario\n";
                cout << "Ingrese nombre de usuario\n";

                cin >>  input5;
                cout << "\n";
                cout << input5;
                break;
        }
    } while ( opcion != 6 );
    
    return 0;
}
