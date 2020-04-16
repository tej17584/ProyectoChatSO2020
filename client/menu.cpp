#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

void confirmacion() {
    cout << "Enviando confirmación\n";
}

void respuesta() {
    cout << "El servidor ha recibido la solicitud\n";
}

void envio() {
    cout << "Enviando solicitud al servidor\n";
}

void cambioEstatus(){
    
    int var;
    
    do
    {
       printf("Cambio de estatus\n");
        printf("Ingrese el numero de la opcion que desea:\n");
        printf("1. Activo\n");
        printf("2. Ocupado\n");
        printf("3. Inactivo\n");
        printf("4. Salir\n");
        printf("\n");
        
        do{
            printf( "Introduzca la opcion que desea ejecutar (1-4): \n");
            scanf( "%d", &var );
            cout << "\n";
        }
        
        while ( var < 1 || var > 4 );
            
            switch (var)
            {
                //Activo
                case 1:
                    printf("Cambio a estatus Activo\n");
                    var = 4;
                    break;
                 
                //Ocupado
                case 2:
                    printf("Cambio a estatus Ocupado\n");
                    var = 4;
                    break;
                
                //Inactivo
                case 3:
                    printf("Cambio a estatus Inactivo\n");
                    var = 4;
                    break;
            }
        } while ( var != 4 );
}

int main() {
    
    int n, opcion;
    char input [100];
    
    do
    {
        printf("\n");
        printf("---------------------------------------------------\n");
        printf("Bienvenido a Chat SISTOS\n");
        printf("---------------------------------------------------\n");
        printf("\n");
        printf("Ingrese el numero de la opcion que deasea ejecutar\n");
        printf("1. Mensaje directo\n");
        printf("2. Broadcasting (Chat general)\n");
        printf("3. Cambio de status\n");
        printf("4. Listado de usuarios\n");
        printf("5. Informacion de un usuario\n");
        printf("6. Salir \n");
        printf("\n");
        
        do{
            printf( "Introduzca la opcion que desea ejecutar (1-6): \n");
            scanf( "%d", &opcion );
            cout << "\n";
        }
        
        while ( opcion < 1 || opcion > 6 );
        
        switch (opcion)
        {
            //Mensaje directo
            case 1:
                printf("MENSAJE DIRECTO\n");
                printf("Ingrese el nombre de usuario\n");
                printf("\n");
                scanf( "%99s", input1 );
                printf("\n");
                
                printf("ingrese el mensaje que desea enviar\n");
                scanf( "%99s", input1 );
                printf("\n");
                break;
             
            //Broadcast
            case 2:
                printf("Broadcast");
                printf("Ingrese el mensaje que desea enviar\n");
                printf("\n");

                scanf( "%99s", input );
                printf("%s", input);
                break;
            
            //Cambio de estatus
            case 3:
                cambioEstatus();
                break;
               
            //Listado de usuarios
            case 4:
                printf("Listado de usuarios");
                break;
              
            //Informacion de usuario
            case 5:
                printf("Informacion de usuario\n");
                printf("Ingrese nombre de usuario\n");

                scanf( "%99s", input );
                printf("%s", input);
                break;
        }
    } while ( opcion != 6 );
    
    return 0;
}

    /*
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
            printf << "MENSAJE DIRECTO\n";
            printf << "Ingrese el nombre de usuario seguido del mensaje que desea enviar\n";
            printf << "Ejemplo: Alejandro Hola\n";
            printf << "\n";
            
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

*/
