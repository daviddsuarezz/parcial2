#include "matriz.h"
#include <cassert>
#include <iostream>

Matriz::Matriz(){ //constructor
    filas = columnas = 0; // le damos valor 0 a los atrbutos filas, columnas
    datos = NULL; // declaramos null el puntero tipo int
}

Matriz::Matriz(const int& f, const int& c){ //constructor sobre cargado, recibe los parametros f y c haciendo alucion a las filas y columnas por referencia, debido al trabajo ne la memoria dinamica
    filas = f;
    columnas = c;
    datos = new int[filas*columnas]; //declaramos un arreglo con el tamañoo de la matriz
    for(int i=0; i < filas; i++){
        for(int j=0; j < columnas; j++){
            datos[i*columnas+j] = 0;
        }
    }
}
Matriz::~Matriz(){ // destructor de la matriz
    delete [] datos;
}

int Matriz::GetFilas() const{ // obtener las filas
    return filas;
}

int Matriz::GetColumnas() const{ //obtener las columnas
    return columnas;
}

int Matriz::GetPosicion(const int& i, const int& j)const{ // pide dos parametros, la i hace referencia a las filas y la j a las columnase
    return datos[i*columnas+j]; // algebra de punteros para encontrar la posicion y retorne el valor asociadao a esta
}

void Matriz::SetPosicion(int i, int j, int n){ // tres parametros, el primero para la fila, el segundo para la columna, y el tercero para la ficha
    assert(i >= 0 && j >= 0); // assert verfica la condicion, si da falso detiene el programa
    datos[i*columnas+j] = n;
}
