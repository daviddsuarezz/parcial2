
#include <ctime>
#include <sstream>
#include <cstring>
#include <istream>
#include <fstream>
#include <iostream>
#include "tablero.h"
#include "jugador.h"

using namespace std;
struct Partida {
    string jugador1;
    int fichas1;
    string jugador2;
    int fichas2;
    string fecha;
    string hora;
    string ganador;
};


void GuardarPartida(Jugador& j1, Jugador& j2){
    time_t ahora = time(0);
    tm *ltm = localtime(&ahora);
    string ganador;
    Partida partida;
    partida.jugador1 = j1.getNombre();
    partida.fichas1 = j1.GetPuntuacion();
    partida.jugador2 = j2.getNombre();
    partida.fichas2 = j2.GetPuntuacion();
    partida.fecha = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
    partida.hora = to_string(ltm->tm_hour) + ":" +to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);
    if(partida.fichas1 > partida.fichas2){
        ganador = partida.jugador1;
    }else{
        ganador = partida.jugador2;
    }
    partida.ganador = ganador;
    // Abre el archivo en modo de agregar
    ofstream archivo("historico.txt", ios_base::app);
    if(!archivo){
        cout<<"Error al guardar el archivo historico.txt";
        exit(EXIT_FAILURE);
    }

    // Escribe los detalles de la partida en el archivo
    archivo << partida.fecha << ";"
            << partida.hora << ";"
            << partida.jugador1 << ";"
            << to_string(partida.fichas1) << ";"
            << partida.jugador2 << ";"
            << to_string(partida.fichas2) << ";"
            << partida.ganador
            << "\n";

    // Cierra el archivo
    archivo.close();
}


void leerHistorico() {
    ifstream archivo("historico.txt"); //archivo

    if(!archivo){
        cout<<"Error al abrir el archivo historico.txt";
        exit(EXIT_FAILURE);
    }


    string linea;

    while (std::getline(archivo, linea)) {
        istringstream iss(linea); // string dinamico
        string fecha, hora, jugador1, jugador2, ganador;
        int fichas1, fichas2;

        getline(iss, fecha, ';'); // lee hasta los separadores, char por char
        getline(iss, hora, ';');
        getline(iss, jugador1, ';');
        iss >> fichas1; // lo toma completo
        iss.ignore();  // Ignora el delimitador ';'
        getline(iss, jugador2, ';');
        iss >> fichas2;
        iss.ignore();  // Ignora el delimitador ';'
        getline(iss, ganador);

        // Ahora puedes usar los datos leídos
        // Por ejemplo, imprimirlos en la consola:
        cout
             << "Fecha: " << fecha << "\n"
             << "Hora: " << hora << "\n"
             << "Jugador 1: " << jugador1 << ", Fichas: " << fichas1 << "\n"
             << "Jugador 2: " << jugador2 << ", Fichas: " << fichas2 << "\n"
             << "Ganador: " << ganador
             << "\n------------------------\n"
             <<endl;
    }

    archivo.close();
}

bool Reversi(Jugador& jugador_1, Jugador& jugador_2, Tablero& t){
    char otra_partida;
    do{

        while(t.FinPartida()){


            if(t.CanSetFicha()){

                if(t.GetTurnoActual()==1){
                    if(jugador_1.escogePosicion(t)){
                        //DialogoGuardar(jugador_1,jugador_2,t);
                    }
                }

                if(t.GetTurnoActual()==2){
                    if(jugador_2.escogePosicion(t)){
                        //DialogoGuardar(jugador_1,jugador_2,t);
                    }
                }
            }
        }

        t.Imprimir_tablero();

        if(t.Ganador() == 1){
            jugador_1.PartidaGanada();
            cout << "Ganador jugador " << t.Ganador() << "." << endl;
        }else if(t.Ganador() == 2){
            jugador_2.PartidaGanada();
            cout << "Ganador jugador " << t.Ganador() << "." << endl;
        }
        else{
            cout << "Ha habido un empate." << endl;
        }

        jugador_1.TotalScore(t);
        jugador_2.TotalScore(t);


        cout << "Resultados tras esta partida: " << endl;

        cout << "\t-";
        jugador_1.MostrarNombreJugador();
        cout << " lleva " << jugador_1.NumeroPartidasGanadas() << " partidas ganadas, acumulando un total de: " << jugador_1.GetPuntuacion() << endl;
        cout << "\t-";
        jugador_2.MostrarNombreJugador();
        cout << " lleva " << jugador_2.NumeroPartidasGanadas() << " partidas ganadas, acumulando un total de: " << jugador_2.GetPuntuacion() << endl;
        cout << "¿Jugar de nuevo(S/N)?: ";
        GuardarPartida(jugador_1,jugador_2);

            do{
            cin >> otra_partida;
            otra_partida = tolower(otra_partida);
        }while(otra_partida != 's' && otra_partida != 'n');

        if(otra_partida == 's'){
            t.VaciarTablero();
        }

    }while(otra_partida == 's');

    cout << "Resultados finales: " << endl;
    cout << " ";
    jugador_1.MostrarNombreJugador();
    cout << " " << jugador_1.NumeroPartidasGanadas() << " partidas ganadas, acumulando un total de: " << jugador_1.GetPuntuacion() << endl;
    cout << " ";
    jugador_2.MostrarNombreJugador();
    cout << " " << jugador_2.NumeroPartidasGanadas() << " partidas ganadas, acumulando un total de: " << jugador_2.GetPuntuacion() << endl;
    cout << endl;
    cout << "El juego ha finalizado." << endl;

    return 1;
}

int main(){

    int opcion= 5;
    while(opcion>0){

        cout<<"Bienvenido a REVERSI\n"<<endl;


        cout << "Ingrese una opcion.\n1.Jugar\n2.Ver historial\n3.Reglas"<<endl;
        cin>> opcion;
        cout<<endl;
        if(opcion==1){
            Jugador jugador_1, jugador_2;
            int n;
            int f;
            cout << "¿De que tamanio quieres la matriz cuadrada?: ";
            cin >> f;
            Tablero t(f,f);
            t.InicializarTablero();
            cout << "Inserta el nombre del jugador 1 (NEGRAS): ";
            char linea[100];

            n = 1;
            cin.ignore();
            cin.getline(linea,100);
            jugador_1.setNombre(linea);
            jugador_1.setNumTurno(n);


            cout << endl;

            cout << "Inserta el nombre del jugador 2 (BLANCAS): ";

            char linea_2[100];

            n = 2;
            cin.getline(linea_2,100);
            jugador_2.setNombre(linea_2);
            jugador_2.setNumTurno(n);

            cout << endl;

            Reversi(jugador_1,jugador_2,t);
        }

        else if(opcion==2){
            cout<<"historial de partidas:\n "<<endl;
            leerHistorico();

            cout<<"1.volver al menu principal.\n0.salir(cualquier otra tecla).\n";
            cin>>opcion;
            (opcion==1)?opcion=3:opcion=0;


        }

        else if(opcion==3){
            cout<<"Objetivo del juego: Teminar la partida con el mayor numero de fichas posibles.\n"
                  "-Solo podra incorporarse una ficha flanquendo a una o varias fichas contrarias.\n"
                  "-por flanquear se entiende como hacer un sandwich con las fichas del rival entre tus fichas\n"
                  "ya sea horizontal, vertical o diagonalmente.\n"
                  "-Cada vez que un jugador incorpora una ficha, y por lo tanto encierra a otras del contrario,\n"
                  "debe dar la vuelta a las fichas encerradas convirtiéndolas así en propias.\n"
                  "-Si al poner una ficha flanqueas mas de una linea, se voltearan todas las fichas involucradas.\n"
                  "-Si no es posible para el jugador encerrar las fichas del rival, debera pasar de turno.\n"
                  "\n"
                  "La partida finaliza cuando el tablero se llena o ningun jugador tiene movimientos validos.\n"
                  "Gana el jugador con mas fichas en el tablero.\n"
                 <<endl;

            cout<<"1.volver al menu principal.\n0.salir(cualquier otra tecla).\n"<<endl;
            cin>>opcion;
            (opcion==1)?opcion=3:opcion=0;

        }
    }
}


