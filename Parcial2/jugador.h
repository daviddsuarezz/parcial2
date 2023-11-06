#ifndef JUGADOR_H
#define JUGADOR_H

#include "tablero.h"

struct Posicion{
    char columna;
    int fila;
};


class Jugador
{
private:
    char* nombre;
    int num_turno;
    int puntuacion;
    int partidas_ganadas;

public:
    Jugador();

    Jugador(int n);

    Jugador(const Jugador& j);

    ~Jugador();


    void TotalScore(const Tablero& t);


    bool escogePosicion(Tablero& t);

    int NumPosValidas(Tablero& t);

    void MostrarNombreJugador();

    void PartidaGanada();

    int NumeroPartidasGanadas();

    int longitudNombre(char c[]);

    void setNombre(char c[]);

    void setNumTurno(int newNum_turno);

    int GetPuntuacion();

    char *getNombre() const;
};

#endif // JUGADOR_H
