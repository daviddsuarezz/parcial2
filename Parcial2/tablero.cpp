#include <iostream>
#include <cstring>
#include <istream>
#include "tablero.h"
#include <fstream>
#include <ctime>
#include <sstream>

using namespace std;

void Tablero::CambiarTurno(){
    /**
 * @brief Cambia el turno del jugador.
 *
 * Si el jugador actual no puede hacer un movimiento, el turno pasa al otro jugador. Si ninguno de los jugadores puede hacer un movimiento, el juego termina.
 */
    if(turno == 1){// cambia el turno muy basico
        turno = 2;
    }
    else{
        turno = 1;
    }

    if(!CanSetFicha()){ // ! invierte el  booleano, y lo que pasa, es que si el juagador
        //no puede puede colocar ficha, pasa al otro jugador
        if(turno == 1){
            turno = 2;
        }

        else{
            turno = 1;
        }

        if(!CanSetFicha()){ // aqui verifica si el actual puede seguir haciendo, doble verificacion si no puede
            // se acaba el programa

            turno = 0;
        }
    }

}

char Tablero::IntaChar(int n){
    /**
 * @brief Convierte un entero a un carácter para representar una ficha en el tablero.
 *
 * @param n El entero a convertir.
 *
 * @return Un carácter que representa una ficha en el tablero (' ' para 0, '*' para 1, '_' para 2).
 */
    //esta funcion servira para que cuando el usuario ingrese un numero, este este asociado a una letra
    if(n == 0){
        return ' '; // si la ficha ingresada es un 0, se pone espacion en blanco
    }

    if(n == 1){
        return '*'; // si la ficha ingresada es uno, se pone x
    }

    if(n == 2){
        return '_'; // si la ficha ingresada es dos, se pone o
    }

    return ' ';
}
Tablero::Tablero(int f, int c): tablero(f,c){
    /**
 * @brief Constructor de la clase Tablero.
 *
 * @param f Número de filas del tablero.
 * @param c Número de columnas del tablero.
 *
 * Inicializa el tablero con las dimensiones especificadas, establece el turno inicial y las fichas restantes y máximas.
 */
    turno = 1;
    jugador_comienzo = 2;
    fichas_restantes = 1;
    fichas_maximas = 1;
}// constructor de la clase tablero

int Tablero::GetFilas() const{
    /**
 * @brief Obtiene el número de filas del tablero.
 *
 * @return Número de filas del tablero.
 */
    //devuelve la filas del tablero con la ayuda del metodo getfilas de la clase matriz
    return tablero.GetFilas();
}

int Tablero::GetColumnas() const{
    /**
 * @brief Obtiene el número de columnas del tablero.
 *
 * @return Número de columnas del tablero.
 */
    //devuelve las columnas del tablero con la ayuda del metodo getcolumnas de la clase matriz
    return tablero.GetColumnas();
}

int Tablero::GetPosicion(const int& i, const int& j) const{
    /**
 * @brief Obtiene el valor en una posición específica del tablero.
 *
 * @param i Índice de la fila.
 * @param j Índice de la columna.
 *
 * @return Valor en la posición (i, j) del tablero. Si los índices son inválidos, retorna -1.
 */
    if(i < 0 || j < 0 || i > GetFilas() || j > GetColumnas()){ //sirve para saber si el usuario intodujo mal el numero de la fila o columna
        return -1;
    }
    return tablero.GetPosicion(i,j); // de lo contrario, entrega la posicion que corresponde en la matriz
}

int Tablero::GetTurnoActual() const{
    /**
 * @brief Obtiene el turno actual.
 *
 * @return El turno actual.
 */
    return turno; // retorna el turno
}

bool Tablero::FinPartida() const{
    /**
 * @brief Verifica si la partida ha terminado.
 *
 * @return Verdadero si la partida aún está en curso, falso si la partida ha terminado.
 */
    if(turno == 0){ // si turno es cero, variable la cual cambiara con el uso del programa, indicará que acabrá la partida
        return false;
    }

    return true;

}

int Tablero::Ganador() const{
    /**
 * @brief Determina el ganador de la partida.
 *
 * @return El número del jugador que ha ganado la partida (1 o 2). Si hay un empate, retorna 0.
 *
 * Esta función cuenta el número de fichas de cada jugador en el tablero y determina el ganador en función de quién tiene más fichas.
 */
    // funcion que dará al ganador de la partida
    int contador1, contador2; // dos contadores para contar, el numero de fichas
    int resultado; // varianle resultado, la cual 1 es ganó el jugador1, y 2 ganó el jugador2

    contador1 = contador2 = 0;

    for (int i = 0; i < tablero.GetFilas(); i++){ //estamos iterando sobre la matriz
        for(int j = 0; j < tablero.GetColumnas(); j++){
            if(tablero.GetPosicion(i,j)== 1){ //utilizamos el metodo para ir a la posicion y evaluamos 1, lo que significa la ficha del jugador 1
                contador1++;
            }
            if(tablero.GetPosicion(i,j) == 2){
                contador2++;
            }
        } //con estos for, obtenemos las fichas dd cada jugador en el tablero

    }
    if(contador1 == contador2){
        resultado = 0; //hubo un empate
    }
    else if(contador1 > contador2){
        resultado = 1; //ganó el jugador 1
    }
    else if(contador1 < contador2){
        resultado = 2; //ganó el jugador 2
    }
    return resultado;
}

int Tablero::GetPuntuacion(const int& n) const{
    /**
 * @brief Obtiene la puntuación de un jugador específico.
 *
 * @param n El número del jugador (1 o 2).
 *
 * @return La puntuación del jugador especificado, que es el número de sus fichas en el tablero.
 */
    // obtendremos la puntacion de un jugador en especifico
    int puntuacion = 0;
    if(n == 1){
        for (int i = 0; i < tablero.GetFilas(); i++){ //estamos iterando sobre la matriz
            for(int j = 0; j < tablero.GetColumnas(); j++){
                if(tablero.GetPosicion(i,j)== 1){ // si lo que esta en esa posicion es uno, le suma a la puntuacion

                    puntuacion++;
                }
            }
        }

    }
    else if(n == 2){
        for (int i = 0; i < tablero.GetFilas(); i++){ //estamos iterando sobre la matriz
            for(int j = 0; j < tablero.GetColumnas(); j++){
                if(tablero.GetPosicion(i,j)== 2){ // si lo que esta en esa posicion es dos, le suma a la puntuacion

                    puntuacion++;
                }
            }
        }

    }
    return puntuacion;
}



void Tablero::InicializarTablero(){
    /**
 * @brief Inicializa el tablero para el comienzo de una partida.
 *
 * Coloca las fichas iniciales de cada jugador en el centro del tablero.
 */
    // inicalizamos el tablero
    tablero.SetPosicion((GetFilas()/2)-1,(GetColumnas()/2)-1,1); // ficha del juegador uno en el medio del tablero, pero osea la fila del medio arriba
    tablero.SetPosicion((GetFilas()/2)-1,(GetColumnas()/2),2); // ficha del jugador dos en el medio deltablero, pero osea la fila del medio arriba
    tablero.SetPosicion((GetFilas()/2),(GetColumnas()/2)-1,2); // ficha del jugador dos en el medio deltablero, en la fila del medio
    tablero.SetPosicion((GetFilas()/2),(GetColumnas()/2),1); // ficha del juegador uno en el medio del tablero
}

void Tablero::SetTurno(int&n){
    /**
 * @brief Establece el turno actual.
 *
 * @param n El número del jugador cuyo turno es (1 o 2).
 */
    //le da un valor al atributo turno del tablero
    turno = n;
}

bool Tablero::PosicionValida(const int& x, const int& y) const {

    /**
 * @brief Verifica si una posición específica en el tablero es válida para hacer un movimiento.
 *
 * @param x Índice de la fila.
 * @param y Índice de la columna.
 *
 * @return Verdadero si la posición es válida para hacer un movimiento, falso en caso contrario.
 *
 * Una posición es válida para hacer un movimiento si está vacía y al colocar una ficha en esa posición, se voltearía al menos una ficha del oponente.
 */
    if (GetPosicion(x, y) != 0) { // verifica si la posicion esta vacia
        return false;
    }

    int otra = (turno == 1) ? 2 : 1; //como debemos verificar las fichas del otro juagador, aqui se utiliza el operador
    //ternario para cambiar, 1 hace referencia al jugardo 1, y 2 referencia al jugardor 2

    // Lista de todas las direcciones a verificar
    int dirs[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    //esto representa, la verificacion, en la misma columna filas de arriba, misma columna filas de abajo
    //misma fila, columa de la izquierda, misma fila columnas derechas
    //digonal de la izquierda hacia abajo, diagonal de la izquierda hacia arriba
    //diagonal de la derecha hacia abajo, diagonal de la derecha hacia arriba
    //verificando toda la matriz

    for (int i = 0; i < 8; ++i) {
        if (checkDirection(x, y, dirs[i][0], dirs[i][1], otra)) { // va a pasar a verificar todas las direcciones, si es true retorna true
            return true;
        }
    }

    return false;
}

bool Tablero::checkDirection(const int& x, const int& y, const int& dx, const int& dy, const int& otra) const {

    /**
 * @brief Verifica si al colocar una ficha en una posición específica en una dirección específica, se voltearía al menos una ficha del oponente.
 *
 * @param x Índice de la fila.
 * @param y Índice de la columna.
 * @param dx Dirección en el eje x.
 * @param dy Dirección en el eje y.
 * @param otra El número del jugador oponente.
 *
 * @return Verdadero si se voltearía al menos una ficha del oponente, falso en caso contrario.
 */
    int iterador = 1;
    //recibe la misma, x y y, los dx y dy hacen referencia a los diferenciales, osea a la direccion donde se va a ir, otra hace referencia a la ficha del otro jugador

    while (GetPosicion(x + iterador * dx, y + iterador * dy) == otra) { //mientras en la direccion que estemos verificando es igual a otra, vamos a ir aumentando el iterador
        ++iterador;
        if (GetPosicion(x + iterador * dx, y + iterador * dy) == turno) { // si encontramos en esa direccion una ficha del jugador actual, retornaremos true
            return true;
        }
    }
    // si no retornaremos false, tener muy en vista, que la multiplicacion se hace de primer orden, y luego la suma
    return false;
}


bool Tablero::CanSetFicha(){
    /**
 * @brief Verifica si el jugador actual puede hacer un movimiento.
 *
 * @return Verdadero si el jugador actual puede hacer un movimiento, falso en caso contrario.
 *
 * Esta función verifica todas las posiciones en el tablero para ver si hay al menos una posición válida para hacer un movimiento.
 */
    for(int i = 0; i < GetFilas(); i++){
        for(int j = 0; j < GetColumnas(); j++){ //iteramos sobre la matriz
            if(PosicionValida(i,j)){ // verificamos si se es valido colocar una ficha en esa posicion
                return true;
            }
        } // retorna true si se puede, false si no
    }
    return false;

}

void Tablero::SetFicha(const int& x, const int& y){
    /**
 * @brief Coloca una ficha del jugador actual en una posición específica y voltea las fichas del oponente en consecuencia.
 *
 * @param x Índice de la fila.
 * @param y Índice de la columna.
 *
 * Esta función verifica primero si la posición es válida para hacer un movimiento. Si es válida, coloca una ficha del jugador actual en esa posición y voltea las fichas del oponente en todas las direcciones válidas. Luego, verifica si el jugador actual puede hacer otro movimiento. Si no puede, cambia el turno al otro jugador.
 */

    if(PosicionValida(x,y)){ //valida primero si la posicion que ingresó el usuario es valida
        int otra = (turno == 1) ? 2 : 1; //mismo cambio para verificar la ficha del rival

        // Lista de todas las direcciones a verificar
        int dirs[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}}; //todas las direcciones

        for (int i = 0; i < 8; ++i) {
            setFichasInDirection(x, y, dirs[i][0], dirs[i][1], otra); //va a poner direccion por direccion
        }
    }

    if(fichas_restantes > 1 && CanSetFicha()){ //para saber si se puede seguir colocando fichas
        fichas_restantes--; // resta las fichas que colocamos
    }
    else{
        fichas_restantes = fichas_maximas; // cambia en el atributo de tablero
        CambiarTurno(); // se le da el turno al otro jugador
    }


}

void Tablero::setFichasInDirection(const int& x, const int& y, const int& dx, const int& dy, const int& otra){
    /**
 * @brief Voltea las fichas del oponente en una dirección específica a partir de una posición específica.
 *
 * @param x Índice de la fila.
 * @param y Índice de la columna.
 * @param dx Dirección en el eje x.
 * @param dy Dirección en el eje y.
 * @param otra El número del jugador oponente.
 *
 * Esta función verifica si al colocar una ficha del jugador actual en la posición (x, y) y moverse en la dirección (dx, dy), se encontraría una ficha del jugador actual. Si es así, voltea todas las fichas del oponente entre las dos fichas del jugador actual.
 */
    int iterador = 1;

    while (GetPosicion(x + iterador * dx, y + iterador * dy) == otra) { // itera sobre toda esa direccion mientras sea igual a la del rival
        ++iterador; //iterador incrementa
        if (GetPosicion(x + iterador * dx, y + iterador * dy) == turno) { // si se llega a encontrar una ficha en esa posicion
            for(int it = 0; it <= iterador; it++) //vamos a iterar otra vez sobre la posiciones
                tablero.SetPosicion(x + it * dx,y + it * dy,turno); // iteramos por cada una de la posicion, cambiando la ficha en esa posicion
            break;
        }
    }
}





void Tablero::Imprimir_tablero(){
    /**
 * @brief Imprime el tablero de juego en la consola.
 *
 * Esta función imprime el tablero de juego en la consola. Las fichas del jugador 1 se representan con '*', las fichas del jugador 2 se representan con 'o', las posiciones vacías se representan con ' ' y las posiciones válidas para hacer un movimiento se representan con '.'. También imprime el turno actual y el número de fichas restantes y máximas. Si la partida ha terminado, imprime un mensaje indicando que la partida ha finalizado.
 */

    char c = 'a'; // para darle un valor a las columnas

    cout << "  "; // espacio

    for(int i = 0; i < tablero.GetFilas();  i++){
        cout  << c << " "; // por medio del codigo asscci podemos ir aumentado de a,b,c....
        c++;
    }

    cout << endl; //salto de linea

    cout << " ";

    for(int i = 0; i < tablero.GetFilas(); i++){
        cout << "--" ; // lineas que delimitan
    }

    cout << endl; // salto de linea

    for(int i = 0; i < tablero.GetFilas(); i++){
        cout << i+1 << "|";  // el numero de la fila El código de escape \033[1;34m cambia el color del texto a azul brillante, y \033[1;0m restablece el color del texto a su valor predeterminado. Por lo tanto, la letra se imprimirá en azul brillante.
        for(int j = 0; j < tablero.GetFilas(); j++){ // vamos a iterar sobre la matriz
            if(tablero.GetPosicion(i,j) == 1){ // si la posicion es igual a 1
                cout << "*"; //va a cambiar ese numero a un char, lo imprime en colo amarillo brillante por codigo ansi
            }

            if(tablero.GetPosicion(i,j) == 2){
                cout << "o";  // cambia el 2 encontrado por el _ y lo imprime en color verde por codigo ansi
            }

            if(tablero.GetPosicion(i,j) == 0 && !PosicionValida(i,j)){ // y aqui va a imprimir el espacio en blanco
                cout  << " ";
            }

            if(tablero.GetPosicion(i,j) == 0 && PosicionValida(i,j)){ // y aqui va a imprimir la posicion valida
                cout  << ".";
            }

            cout << "|";
        }
        cout << endl;
    }

    cout << " ";

    for(int i = 0; i < tablero.GetFilas(); i++){
        cout << "--" ; // debajo del tablero
    }

    cout << endl;

    if(turno == 1 || turno == 2){
        cout << "Turno"
             //<< (fichas_maximas - fichas_restantes + 1)
             //<< "/"
             //<< fichas_maximas
             << " del jugador "
             << GetTurnoActual()
             << ": "
             << " ("
             << (((GetTurnoActual())==1)?"*":"o")
             << ")\n"
             << "posiciones validas (.)"
             << endl;
    }
    else{
        cout<< "Partida finalizada." ;
    }
}

