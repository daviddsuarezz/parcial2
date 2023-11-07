
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
    time_t ahora = time(0); // Obtiene la hora actual en segundos desde la época Unix (1 de enero de 1970)
    tm *ltm = localtime(&ahora); // Convierte la hora actual a la hora local
    string ganador; // Declara una variable para almacenar el nombre del ganador
    Partida partida; // Crea un objeto de la clase Partida
    partida.jugador1 = j1.getNombre(); // Obtiene el nombre del jugador 1
    partida.fichas1 = j1.GetPuntuacion(); // Obtiene la puntuación del jugador 1
    partida.jugador2 = j2.getNombre(); // Obtiene el nombre del jugador 2
    partida.fichas2 = j2.GetPuntuacion(); // Obtiene la puntuación del jugador 2
    partida.fecha = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year); // Formatea la fecha actual en el formato DD/MM/AAAA
    partida.hora = to_string(ltm->tm_hour) + ":" +to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec); // Formatea la hora actual en el formato HH:MM:SS
    if(partida.fichas1 > partida.fichas2){ // Comprueba si el jugador 1 tiene más fichas que el jugador 2
        ganador = partida.jugador1; // Si es así, el jugador 1 es el ganador
    }else{
        ganador = partida.jugador2; // Si no, el jugador 2 es el ganador
    }
    partida.ganador = ganador; // Almacena el nombre del ganador en el objeto partida
    ofstream archivo("historico.txt", ios_base::app); // Abre el archivo "historico.txt" en modo de agregar
    if(!archivo){ // Comprueba si el archivo se abrió correctamente
        cout<<"Error al guardar el archivo historico.txt"; // Si no se abrió correctamente, muestra un mensaje de error
        exit(EXIT_FAILURE); // Y termina el programa
    }
    archivo << partida.fecha << ";" // Escribe la fecha de la partida en el archivo
            << partida.hora << ";" // Escribe la hora de la partida en el archivo
            << partida.jugador1 << ";" // Escribe el nombre del jugador 1 en el archivo
            << to_string(partida.fichas1) << ";" // Escribe la puntuación del jugador 1 en el archivo
            << partida.jugador2 << ";" // Escribe el nombre del jugador 2 en el archivo
            << to_string(partida.fichas2) << ";" // Escribe la puntuación del jugador 2 en el archivo
            << partida.ganador // Escribe el nombre del ganador en el archivo
            << "\n"; // Añade un salto de línea al final
    archivo.close(); // Cierra el archivo
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
    ifstream archivo("historico.txt"); // Abre el archivo "historico.txt" para lectura

    if(!archivo){ // Comprueba si el archivo se abrió correctamente
        cout<<"Error al abrir el archivo historico.txt"; // Si no se abrió correctamente, muestra un mensaje de error
        exit(EXIT_FAILURE); // Y termina el programa
    }

    string linea; // Declara una variable para almacenar cada línea del archivo

    while (std::getline(archivo, linea)) { // Lee el archivo línea por línea
        istringstream iss(linea); // Crea un flujo de entrada a partir de la línea
        string fecha, hora, jugador1, jugador2, ganador; // Declara variables para almacenar los datos de la partida
        int fichas1, fichas2; // Declara variables para almacenar las puntuaciones de los jugadores

        getline(iss, fecha, ';'); // Lee la fecha de la partida
        getline(iss, hora, ';'); // Lee la hora de la partida
        getline(iss, jugador1, ';'); // Lee el nombre del jugador 1
        iss >> fichas1; // Lee la puntuación del jugador 1
        iss.ignore();  // Ignora el delimitador ';'
        getline(iss, jugador2, ';'); // Lee el nombre del jugador 2
        iss >> fichas2; // Lee la puntuación del jugador 2
        iss.ignore();  // Ignora el delimitador ';'
        getline(iss, ganador); // Lee el nombre del ganador

        // Ahora puedes usar los datos leídos
        // Por ejemplo, imprimirlos en la consola:
        cout
            << "Fecha: " << fecha << "\n" // Imprime la fecha de la partida
            << "Hora: " << hora << "\n" // Imprime la hora de la partida
            << "Jugador 1: " << jugador1 << ", Fichas: " << fichas1 << "\n" // Imprime el nombre y la puntuación del jugador 1
            << "Jugador 2: " << jugador2 << ", Fichas: " << fichas2 << "\n" // Imprime el nombre y la puntuación del jugador 2
            << "Ganador: " << ganador // Imprime el nombre del ganador
            << "\n------------------------\n"
            <<endl;

    }

    archivo.close(); // Cierra el archivo
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

    while(t.FinPartida()){ // Mientras la partida no haya terminado

        if(t.CanSetFicha()){ // Si se puede colocar una ficha

            if(t.GetTurnoActual()==1){ // Si es el turno del jugador 1
                if(jugador_1.escogePosicion(t)){ // El jugador 1 escoge una posición
                }
            }

            if(t.GetTurnoActual()==2){ // Si es el turno del jugador 2
                if(jugador_2.escogePosicion(t)){ // El jugador 2 escoge una posición

                }
            }
        }
    }

    t.Imprimir_tablero(); // Imprime el tablero

    if(t.Ganador() == 1){ // Si el ganador es el jugador 1
        jugador_1.PartidaGanada(); // El jugador 1 gana la partida
        cout << endl << "Ganador jugador ";
        jugador_1.MostrarNombreJugador(); // Muestra el nombre del jugador 1
        cout << "." << endl;
    }else if(t.Ganador() == 2){ // Si el ganador es el jugador 2
        jugador_2.PartidaGanada(); // El jugador 2 gana la partida
        cout << endl  << "Ganador jugador ";
        jugador_2.MostrarNombreJugador(); // Muestra el nombre del jugador 2
        cout << "." << endl;
    }
    else{
        cout << "Ha habido un empate." << endl; // Si no hay ganador, se declara un empate
    }

    jugador_1.TotalScore(t); // Calcula la puntuación total del jugador 1
    jugador_2.TotalScore(t); // Calcula la puntuación total del jugador 2

    cout << "Resultados tras esta partida: " << endl; // Muestra los resultados de la partida

    cout << "\t-";
    jugador_1.MostrarNombreJugador(); // Muestra el nombre del jugador 1
    cout << " hizo una puntuacion de: " << jugador_1.GetPuntuacion() << endl; // Muestra la puntuación del jugador 1
    cout << "\t-";
    jugador_2.MostrarNombreJugador(); // Muestra el nombre del jugador 2
    cout   << " hizo una puntuacion de: " << jugador_2.GetPuntuacion() << endl; // Muestra la puntuación del jugador 2
    GuardarPartida(jugador_1,jugador_2); // Guarda los detalles de la partida
    cout << endl;
    cout << endl;
    return 1; // Termina la función con un valor de retorno de 1
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


            // Validación para asegurar que el nombre no esté vacío ni sea solo espacios en blanco
            // Validación para asegurar que el nombre no esté vacío, verficamos que toda la linea no cuente solo espacios vacios
            while(strlen(linea) == 0 || linea[0] == ' ') {
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
            while(strlen(linea_2) == 0 || linea_2[0] == ' ') { // strleen mide el tamaño del char
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


