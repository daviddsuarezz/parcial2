#include "jugador.h"
//#include "tablero.h"
#include <iostream>


char *Jugador::getNombre() const
{
    return nombre;
}

Jugador::Jugador(){
    num_turno = 0;
    puntuacion = 0;
    partidas_ganadas = 0;
    nombre = NULL;
}

Jugador::Jugador(int n){
    num_turno = n;
    puntuacion = 0;
    partidas_ganadas = 0;
    nombre = NULL;

}
Jugador::~Jugador(){
    delete [] nombre;
}

Jugador& Jugador::operator=(Jugador& j){
    if(this != &j){
        setNombre(j.nombre);
        num_turno = j.num_turno;
        puntuacion = j.puntuacion;
        partidas_ganadas = j.partidas_ganadas;

    }

    return *this;
}

void Jugador::TotalScore(const Tablero& t){
    puntuacion += t.GetPuntuacion(num_turno);
}


int Jugador::longitudNombre(char c[]){
    int longitud = 0;

    for(int i = 0; c[i] != '\0'; i++){
        longitud++;
    }

    return longitud;
}

void Jugador::setNombre(char c[]){
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
    int n=0;
    int aux;
    char c;
    bool termina = false;


        if(NumPosValidas(t) == 1){
            for (int i = 0; i < t.GetFilas(); ++i){
                for (int j = 0; j < t.GetColumnas(); ++j){
                    if (t.PosicionValida(i,j)){
                        t.SetFicha(i,j);
                    }
                }
            }
        }

        else{

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
        }

        t.SetFicha(n-1,aux);


    return termina;
}
void Jugador::setNumTurno(int newNum_turno)
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

void Jugador::PartidaGanada(){
    partidas_ganadas++;
}

int Jugador::NumPosValidas(Tablero& t){
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

int Jugador::PosicionesValidasStruct(Tablero& t, Posicion v[]){
    int n = 0;

    for(int i = 0; i < t.GetFilas(); i++){
            for(int j = 0; j < t.GetColumnas(); j++){
                if(t.PosicionValida(i,j)){
                    v[n].fila = i;
                    v[n].columna = j;
                    n++;
                }
            }
    }

    return n;
}
