#include "matriz.h"
#include <cassert>
#include <iostream>

Matriz::Matriz(){
    /**
 * @brief Constructor por defecto de la clase Matriz.
 *
 * Inicializa los atributos `filas` y `columnas` en 0 y el puntero `datos` en NULL.
 */
 //constructor
    filas = columnas = 0; // le damos valor 0 a los atrbutos filas, columnas
    datos = NULL; // declaramos null el puntero tipo int
}

Matriz::Matriz(const int& f, const int& c){
    /**
 * @brief Constructor sobrecargado de la clase Matriz.
 *
 * @param f Número de filas de la matriz.
 * @param c Número de columnas de la matriz.
 *
 * Inicializa los atributos `filas` y `columnas` con los valores proporcionados y asigna memoria para el puntero `datos` de acuerdo al tamaño de la matriz. Luego, inicializa todos los elementos de la matriz en 0.
 */
    //constructor sobre cargado, recibe los parametros f y c haciendo alucion a las filas y columnas por referencia, debido al trabajo ne la memoria dinamica
    filas = f;
    columnas = c;
    datos = new int[filas*columnas]; //declaramos un arreglo con el tamañoo de la matriz
    for(int i=0; i < filas; i++){
        for(int j=0; j < columnas; j++){
            datos[i*columnas+j] = 0;
        }
    }
}
Matriz::~Matriz(){
    /**
 * @brief Destructor de la clase Matriz.
 *
 * Libera la memoria asignada al puntero `datos`.
 */
    // destructor de la matriz
    delete [] datos;
}

int Matriz::GetFilas() const{
    /**
 * @brief Obtiene el número de filas de la matriz.
 *
 * @return Número de filas de la matriz.
 */
    // obtener las filas
    return filas;
}

int Matriz::GetColumnas() const{
    /**
 * @brief Obtiene el número de columnas de la matriz.
 *
 * @return Número de columnas de la matriz.
 */

    //obtener las columnas
    return columnas;
}

int Matriz::GetPosicion(const int& i, const int& j)const{
    /**
 * @brief Obtiene el valor en una posición específica de la matriz.
 *
 * @param i Índice de la fila.
 * @param j Índice de la columna.
 *
 * @return Valor en la posición (i, j) de la matriz.
 */
    // pide dos parametros, la i hace referencia a las filas y la j a las columnase
    return datos[i*columnas+j]; // algebra de punteros para encontrar la posicion y retorne el valor asociadao a esta
}

void Matriz::SetPosicion(int i, int j, int n){

    /**
 * @brief Establece el valor en una posición específica de la matriz.
 *
 * @param i Índice de la fila.
 * @param j Índice de la columna.
 * @param n Nuevo valor a establecer en la posición (i, j).
 *
 * Esta función establece el valor `n` en la posición (i, j) de la matriz. Si los índices proporcionados son inválidos (es decir, negativos), la función terminará el programa con un mensaje de error.
 */

    // tres parametros, el primero para la fila, el segundo para la columna, y el tercero para la ficha
    assert(i >= 0 && j >= 0); // assert verfica la condicion, si da falso detiene el programa
    datos[i*columnas+j] = n;
}

