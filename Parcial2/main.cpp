
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
    /**
 * @brief Estructura para almacenar información sobre una partida de juego.
 *
 * Esta estructura almacena detalles sobre una partida de juego, incluyendo los nombres de los jugadores,
 * el número de fichas que cada jugador tiene al final de la partida, la fecha y hora de la partida, y el ganador de la partida.
 */
    string jugador1;
    int fichas1;
    string jugador2;
    int fichas2;
    string fecha;
    string hora;
    string ganador;
};


void GuardarPartida(Jugador& j1, Jugador& j2){
    /**
 * @brief Guarda los detalles de una partida en un archivo.
 *
 * Esta función guarda los detalles de una partida, incluyendo los nombres de los jugadores, sus puntuaciones,
 * la fecha y hora de la partida, y el ganador de la partida, en un archivo llamado "historico.txt".
 *
 * @param j1 Una referencia al primer jugador.
 * @param j2 Una referencia al segundo jugador.
 */
    time_t ahora = time(0);
    tm *ltm = localtime(&ahora);
    string ganador;
    Partida partida;
    partida.jugador1 = j1.getNombre();
    partida.fichas1 = j1.GetPuntuacion();
    partida.jugador2 = j2.getNombre();
    partida.fichas2 = j2.GetPuntuacion();
    partida.fecha = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year); //por tema de funcionalidad de la libreria se le agrega 1900
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
    /**
 * @brief Lee el historial de partidas desde un archivo y lo imprime en la consola.
 *
 * Esta función abre un archivo llamado "historico.txt" y lee los detalles de las partidas que se han jugado.
 * Cada línea del archivo representa una partida y los detalles de la partida están separados por el carácter ';'.
 * Los detalles de la partida incluyen la fecha, la hora, los nombres de los jugadores, sus puntuaciones y el ganador de la partida.
 * Después de leer los detalles de una partida, la función los imprime en la consola.
 */
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
    /**
 * @brief Función principal del juego Reversi.
 *
 * @param jugador_1 Referencia al primer jugador.
 * @param jugador_2 Referencia al segundo jugador.
 * @param t Referencia al tablero de juego.
 *
 * @return Retorna 1 cuando el juego termina.
 *
 * Esta función controla el flujo del juego Reversi. En cada turno, verifica si el jugador actual puede hacer un movimiento.
 * Si es posible, el jugador elige una posición en el tablero para colocar su ficha. Este proceso se repite hasta que el juego termina.
 *
 * Al final del juego, se imprime el tablero y se anuncia el ganador. También se actualizan las puntuaciones de los jugadores y se guarda la partida.
 */

        while(t.FinPartida()){


            if(t.CanSetFicha()){

                if(t.GetTurnoActual()==1){
                    if(jugador_1.escogePosicion(t)){
                    }
                }

                if(t.GetTurnoActual()==2){
                    if(jugador_2.escogePosicion(t)){

                    }
                }
            }
        }

        t.Imprimir_tablero();

        if(t.Ganador() == 1){
            jugador_1.PartidaGanada();
            cout << endl << "Ganador jugador ";
            jugador_1.MostrarNombreJugador();
            cout << "." << endl;
        }else if(t.Ganador() == 2){
            jugador_2.PartidaGanada();
            cout << endl  << "Ganador jugador ";
            jugador_2.MostrarNombreJugador();
            cout << "." << endl;
        }
        else{
            cout << "Ha habido un empate." << endl;
        }

        jugador_1.TotalScore(t);
        jugador_2.TotalScore(t);


        cout << "Resultados tras esta partida: " << endl;

        cout << "\t-";
        jugador_1.MostrarNombreJugador();
        cout << " hizo una puntuacion de: " << jugador_1.GetPuntuacion() << endl;
        cout << "\t-";
        jugador_2.MostrarNombreJugador();
        cout   << " hizo una puntuacion de: " << jugador_2.GetPuntuacion() << endl;
        GuardarPartida(jugador_1,jugador_2);
        cout << endl;
        cout << endl;
        return 1;
}

int main(){
        /**
 * @brief Función principal para el juego de Reversi.
 *
 *
 * Esta función muestra un menú de opciones al usuario y realiza acciones basadas en la opción seleccionada por el usuario.
 * Las opciones son las siguientes:
 * 1. Jugar: Inicia un nuevo juego de Reversi. Pide a los usuarios que ingresen sus nombres y el tamaño del tablero, y luego llama a la función `Reversi`.
 * 2. Ver historial: Muestra el historial de partidas jugadas anteriormente llamando a la función `leerHistorico`.
 * 3. Reglas: Muestra las reglas del juego de Reversi.
 * 0. Salir: Termina el programa.
 *
 * Por favor, ten en cuenta que esta es una descripción general y puede que necesites ajustarla según las implementaciones específicas de tus clases y funciones.
 */
    int opcion= 5;
    while(opcion>0){

        cout<<"Bienvenido a REVERSI\n"<<endl;


        cout << "Ingrese una opcion.\n1.Jugar\n2.Ver historial\n3.Reglas\n0.salir"<<endl;
        while(!(cin >> opcion)){
                cout << "Por favor, ingrese un número válido." << endl;
                cin.clear();
                cin.ignore();
        }
        cout << endl;
        if(opcion==1){
            Jugador jugador_1, jugador_2;
            int n;
            int f;
            cout << "¿De que tamanio quieres la matriz cuadrada?: ";
                // Validación para asegurar que el usuario solo ingrese números
                while(!(cin >> f)) {
                    cout << "Por favor, ingresa un número válido: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
            }
            Tablero t(f,f);
            t.InicializarTablero();
            cout << "Inserta el nombre del jugador 1 (NEGRAS): ";
            char linea[100];
            n = 1;
            cin.ignore();
            cin.getline(linea,100);

            // Validación para asegurar que el nombre no esté vacío
            while(strlen(linea) == 0) {
                    cout << "El nombre no puede estar vacío. Por favor, inténtalo de nuevo: ";
                    cin.getline(linea,100);
            }

            jugador_1.setNombre(linea);
            jugador_1.setNumTurno(n);
            cout << endl;

            cout << "Inserta el nombre del jugador 2 (BLANCAS): ";
            char linea_2[100];
            n = 2;
            cin.getline(linea_2,100);

            // Validación para asegurar que el nombre no esté vacío
            while(strlen(linea_2) == 0) {
                    cout << "El nombre no puede estar vacío. Por favor, inténtalo de nuevo: ";
                    cin.getline(linea_2,100);
            }

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


