#include "jugador.h"
#include <iostream>


Jugador::Jugador(){
    num_turno = 0;
    puntuacion = 0;
    partidas_ganadas = 0;
}

Jugador::Jugador(int& n){
    num_turno = n;
    puntuacion = 0;
    partidas_ganadas = 0;
}


void Jugador::setNombre(std::string *newNombre)
{
    nombre = newNombre;
}

void Jugador::setNum_turno(int newNum_turno)
{
    num_turno = newNum_turno;
}

void Jugador::MostrarNombreJugador()
{
    std::cout << nombre;
}

int Jugador::NumeroPartidasGanadas()
{
    return partidas_ganadas++;
}

int Jugador::GetPuntuacion()
{
    return puntuacion;
}

