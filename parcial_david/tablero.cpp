#include <iostream>
#include <cstring>
#include <istream>
#include "tablero.H"
#include <fstream>
#include <ctime>
#include <sstream>

using namespace std;

void Tablero::CambiarTurno(){
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

char Tablero::IntaChar(int n){ //esta funcion servira para que cuando el usuario ingrese un numero, este este asociado a una letra
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
Tablero::Tablero():turno(1),jugador_comienzo(2),fichas_restantes(1),fichas_maximas(1){} // constructor de la clase tablero

int Tablero::GetFilas() const{ //devuelve la filas del tablero con la ayuda del metodo getfilas de la clase matriz
    return tablero.GetFilas();
}

int Tablero::GetColumnas() const{ //devuelve las columnas del tablero con la ayuda del metodo getcolumnas de la clase matriz
    return tablero.GetColumnas();
}

int Tablero::GetPosicion(const int& i, const int& j) const{
    if(i < 0 || j < 0 || i > GetFilas() || j > GetColumnas()){ //sirve para saber si el usuario intodujo mal el numero de la fila o columna
        return -1;
    }
    return tablero.GetPosicion(i,j); // de lo contrario, entrega la posicion que corresponde en la matriz
}

int Tablero::GetTurnoActual() const{
    return turno; // retorna el turno
}

bool Tablero::FinPartida() const{
    if(turno == 0){ // si turno es cero, variable la cual cambiara con el uso del programa, indicará que acabrá la partida
        return false;
    }

    return true;

}

int Tablero::Ganador() const{ // funcion que dará al ganador de la partida
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

int Tablero::GetPuntuacion(const int& n) const{ // obtendremos la puntacion de un jugador en especifico
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

bool Tablero::CanSetFicha(){
    for(int i = 0; i < GetFilas(); i++){
        for(int j = 0; j < GetColumnas(); j++){ //iteramos sobre la matriz
            if(PosicionValida(i,j)){ // verificamos si se es valido colocar una ficha en esa posicion
                return true;
            }
        } // retorna true si se puede, false si no
    }
    return false;

}

void Tablero::InicializarTablero(){ // inicalizamos el tablero
    tablero.SetPosicion((GetFilas()/2)-1,(GetColumnas()/2)-1,1); // ficha del juegador uno en el medio del tablero, pero osea la fila del medio arriba
    tablero.SetPosicion((GetFilas()/2)-1,(GetColumnas()/2),2); // ficha del jugador dos en el medio deltablero, pero osea la fila del medio arriba
    tablero.SetPosicion((GetFilas()/2),(GetColumnas()/2)-1,2); // ficha del jugador dos en el medio deltablero, en la fila del medio
    tablero.SetPosicion((GetFilas()/2),(GetColumnas()/2),1); // ficha del juegador uno en el medio del tablero
}

void Tablero::SetTurno(int&n){ //le da un valor al atributo turno del tablero
    turno = n;
}

bool Tablero::PosicionValida(const int& x, const int& y) const {
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

void Tablero::SetFicha(const int& x, const int& y){
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

    char c = 'a'; // para darle un valor a las columnas

    cout << "  "; // espacio

    for(int i = 0; i < tablero.GetFilas();  i++){
        cout << "\033[1;34m" << c << "\033[1;0m" << " "; // por medio del codigo asscci podemos ir aumentado de a,b,c....
        c++;
    }

    cout << endl; //salto de linea

    cout << " ";

    for(int i = 0; i < tablero.GetFilas(); i++){
        cout << "--" ; // lineas que delimitan
    }

    cout << endl; // salto de linea

    for(int i = 0; i < tablero.GetFilas(); i++){
        cout << "\033[1;34m" << i << "\033[1;0m" << "|";  // el numero de la fila El código de escape \033[1;34m cambia el color del texto a azul brillante, y \033[1;0m restablece el color del texto a su valor predeterminado. Por lo tanto, la letra se imprimirá en azul brillante.
        for(int j = 0; j < tablero.GetFilas(); j++){ // vamos a iterar sobre la matriz
            if(tablero.GetPosicion(i,j) == 1){ // si la posicion es igual a 1
                cout << "\033[1;93m" << IntaChar(tablero.GetPosicion(i,j)) << "\033[1;0m"; //va a cambiar ese numero a un char, lo imprime en colo amarillo brillante por codigo ansi
            }

            if(tablero.GetPosicion(i,j) == 2){
                cout << "\033[1;32m" << IntaChar(tablero.GetPosicion(i,j)) << "\033[1;0m"; // cambia el 2 encontrado por el _ y lo imprime en color verde por codigo ansi
            }

            if(tablero.GetPosicion(i,j) == 0 && !PosicionValida(i,j)){ // y aqui va a imprimir el espacio en blanco
                cout  << IntaChar(tablero.GetPosicion(i,j));
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
        cout << "Turno  "
             << (fichas_maximas - fichas_restantes + 1)
             << "/"
             << fichas_maximas
             << " del jugador "
             << GetTurnoActual()
             << ": "
             << " ("
             << IntaChar(GetTurnoActual())
             << ")"
             << endl;
    }
    else{
        cout<< "Partida finalizada." ;
    }
}


