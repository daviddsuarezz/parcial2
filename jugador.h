#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
class Jugador
{
private:
    std::string* nombre;
    int num_turno;
    int puntuacion;
    int partidas_ganadas;

public:
    Jugador();
    Jugador(int &n);


    void setNombre(std::string *newNombre);
    void setNum_turno(int newNum_turno);

    void MostrarNombreJugador();
    void PartidaGanada();
    int NumeroPartidasGanadas();
    int GetPuntuacion();

};

#endif // JUGADOR_H
