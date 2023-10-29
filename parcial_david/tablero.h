#ifndef TABLERO_H
#define TABLERO_H
#include <iostream>
#include "matriz.h"
#endif // TABLERO_H

class Tablero{

private:

    Matriz tablero, tablero_original;
    int turno;
    int jugador_comienzo;
    int fichas_restantes;
    int fichas_maximas;


public:
    Tablero();

    Tablero(int f, int c);

    void CambiarTurno();

    char IntaChar(int n);

    int GetFilas() const;

    int GetColumnas() const;

    int GetPosicion(const int& i, const int& j) const;

    int GetTurnoActual() const;

    bool FinPartida() const;

    int Ganador() const;

    int GetPuntuacion(const int& n) const;

    bool PosicionValida(const int& i, const int& j) const;

    bool CanSetFicha();

    void SetTurno(int&n);

    void SetFicha(const int& f, const int& c);

    void VaciarTablero();

    void InicializarTablero();

    void Imprimir_tablero();

    bool checkDirection(const int& x, const int& y, const int& dx, const int& dy, const int& otra) const;

    void setFichasInDirection(const int& x, const int& y, const int& dx, const int& dy, const int& otra);


};


