#include "jugador.h"
//#include "tablero.h"
#include <iostream>
using namespace std;


char *Jugador::getNombre() const
/**
 * @brief Obtiene el nombre del jugador.
 *
 * Esta función devuelve un puntero al nombre del jugador. El nombre es almacenado
 * como una cadena de caracteres (char array) en la clase Jugador.
 *
 * @return char* Un puntero al nombre del jugador.
 */
{
    return nombre;
}

Jugador::Jugador()
/**
 * @brief Constructor por defecto de la clase Jugador.
 *
 * Este constructor inicializa un nuevo objeto Jugador con valores predeterminados.
 * Se invoca cuando se crea un nuevo objeto Jugador sin proporcionar ningún argumento.
 *
 * @note El nombre del jugador se inicializa como NULL. Asegúrate de asignarle un valor válido antes de usarlo.
 */
{
    num_turno = 0; // Inicializa el número de turno del jugador a 0
    puntuacion = 0; // Inicializa la puntuación del jugador a 0
    partidas_ganadas = 0; // Inicializa el número de partidas ganadas por el jugador a 0
    nombre = NULL; // Inicializa el nombre del jugador a NULL
}

Jugador::Jugador(int n){
    /**
 * @brief Constructor de la clase Jugador que acepta un número de turno.
 *
 * Este constructor inicializa un nuevo objeto Jugador con un número de turno específico y otros valores predeterminados.
 * Se invoca cuando se crea un nuevo objeto Jugador proporcionando un número de turno.
 *
 * @param n El número de turno para el jugador.
 *
 * @note El nombre del jugador se inicializa como NULL. Asegúrate de asignarle un valor válido antes de usarlo.
 */
    num_turno = n; // Inicializa el número de turno del jugador al valor proporcionado
    puntuacion = 0; // Inicializa la puntuación del jugador a 0
    partidas_ganadas = 0; // Inicializa el número de partidas ganadas por el jugador a 0
    nombre = NULL; // Inicializa el nombre del jugador a NULL

}

/**
 * @brief Destructor de la clase Jugador.
 *
 * Este destructor se invoca automáticamente cuando un objeto Jugador es destruido.
 * Libera la memoria asignada al nombre del jugador.
 */
Jugador::~Jugador(){
    delete [] nombre; // Libera la memoria asignada al nombre del jugador
}


void Jugador::TotalScore(const Tablero& t){
    /**
 * @brief Actualiza la puntuación total del jugador.
 *
 * Esta función suma la puntuación actual del jugador en el tablero a la puntuación total del jugador.
 *
 * @param t Una referencia constante al tablero del juego.
 */
    puntuacion += t.GetPuntuacion(num_turno); // Suma la puntuación actual del jugador en el tablero a la puntuación total del jugador
}


int Jugador::longitudNombre(char c[]){
    /**
 * @brief Calcula la longitud de una cadena de caracteres.
 *
 * Esta función recorre la cadena de caracteres proporcionada y cuenta el número de caracteres hasta que encuentra el carácter nulo ('\0'), que indica el final de la cadena.
 *
 * @param c[] Un array de caracteres para el cual se calculará la longitud.
 * @return int La longitud de la cadena de caracteres.
 */
    int longitud = 0;

    for(int i = 0; c[i] != '\0'; i++){
        longitud++;
    }

    return longitud;
}

void Jugador::setNombre(char c[]){
    /**
 * @brief Establece el nombre del jugador.
 *
 * Esta función asigna un nuevo nombre al jugador. Primero, libera la memoria previamente asignada al nombre del jugador.
 * Luego, calcula la longitud del nuevo nombre, reserva la memoria necesaria y copia el nuevo nombre en la memoria reservada.
 *
 * @param c[] Un array de caracteres que contiene el nuevo nombre para el jugador.
 */
    int longitud;

    delete [] nombre;

    longitud = longitudNombre(c);

    nombre = new char[longitud + 1];

    for(int i = 0; i < longitud; i++){
        nombre[i] = c[i];
    }

    nombre[longitud] = '\0';
}


bool Jugador::escogePosicion(Tablero& t){
    /**
 * @brief Permite al jugador escoger una posición en el tablero.
 *
 * Esta función solicita al jugador que ingrese una columna y una fila en el tablero donde desea colocar su ficha.
 * Si el jugador ingresa '!', la función retorna true, indicando que el jugador desea terminar el juego.
 * Si el jugador ingresa un valor que no es un número para la fila, se le solicita que ingrese un número válido.
 * La función verifica que la posición ingresada sea válida (es decir, que esté dentro de los límites del tablero y que la posición esté vacía).
 * Si la posición es válida, se coloca una ficha en esa posición.
 *
 * @param t Una referencia al tablero del juego.
 * @return bool Retorna true si el jugador desea terminar el juego, false en caso contrario.
 */
    int n=0;
    int aux;
    char c;
    bool termina = false;
            t.Imprimir_tablero();

            char d;
            d = (t.GetColumnas() + 'a') - 1;

            do{

                std::cout << nombre << " escoja un columna (a-" << d << ") " << "y una fila (1-" << t.GetFilas() << "):";
                std::cin >> c;

                if(c == '!'){
                    return true;
                }

                std::cin >> n;

                if(std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(1000,'\n');
                    std::cout << "Error de formato"<< std::endl;
                    n = -1;
                }

                c = tolower(c);

                aux = c - 'a';
            }while(aux > t.GetColumnas() || aux < 0 || n < 0 || n > t.GetFilas()+1 || !t.PosicionValida(n-1,aux));

        t.SetFicha(n-1,aux);


    return termina;
}

void Jugador::setNumTurno(int newNum_turno)
/**
 * @brief Establece el número de turno del jugador.
 *
 * @param newNum_turno El nuevo número de turno para el jugador.
 */
{
    num_turno = newNum_turno;
}

void Jugador::MostrarNombreJugador()
/**
 * @brief Muestra el nombre del jugador.
 *
 * Imprime el nombre del jugador en la consola.
 */
{
    std::cout << nombre;
}

int Jugador::GetPuntuacion()
/**
 * @brief Obtiene la puntuación del jugador.
 *
 * @return int La puntuación del jugador.
 */
{
    return puntuacion;
}

void Jugador::PartidaGanada(){
    partidas_ganadas++;
}

int Jugador::NumPosValidas(Tablero& t){
    /**
 * @brief Calcula el número de posiciones válidas en el tablero.
 *
 * Esta función recorre todas las posiciones en el tablero y cuenta cuántas de ellas son válidas.
 *
 * @param t Una referencia al tablero del juego.
 * @return int El número de posiciones válidas en el tablero.
 * */
    int n = 0;

    for(int i = 0; i < t.GetFilas(); i++){
            for(int j = 0; j < t.GetColumnas(); j++){
                if(t.PosicionValida(i,j)){
                    n++;
                }
            }
    }
    return n;
}

