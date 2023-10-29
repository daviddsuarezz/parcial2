#include <QCoreApplication>
#include <ctime>
#include <sstream>
#include <cstring>
#include <istream>
#include <fstream>
#include <iostream>

using namespace std;
struct Partida {
    string jugador1;
    int fichas1;
    string jugador2;
    int fichas2;
    string fecha;
    string hora;
    string ganador;
};

void GuardarPartida(jugador j1, jugador j2){
    time_t ahora = time(0);
    tm *ltm = localtime(&ahora);

    Partida partida;
    partida.jugador1 = j1;
    partida.fichas1 = j1.GetPuntuacion(1);
    partida.jugador1 = j2;
    partida.fichas2 = j2.GetPuntuacion(2);
    partida.fecha = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
    partida.hora = to_string(ltm->tm_hour) + ":" +to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);
    if(partida.fichas1 > partida.fichas2){
        ganador = j1.GetNombre;
    }else{
        ganador = j2.GetNombre;
    }
    partida.ganador = ganador;
}
void guardarHistorico(Partida partida) {

    // Abre el archivo en modo de agregar
    std::ofstream archivo("historico.txt", std::ios_base::app);

    // Escribe los detalles de la partida en el archivo
    archivo << partida.fecha << ":"
            << partida.hora << ":"
            << partida.jugador1 << ":"
            << partida.fichas1 << ":"
            << partida.jugador2 << ":"
            << partida.fichas2 << ":"
            << partida.ganador
            << "\n";

    // Cierra el archivo
    archivo.close();

}
void leerHistorico() {
    ifstream archivo("historico.txt"); //archivo
    string linea;

    while (std::getline(archivo, linea)) {
        istringstream iss(linea); // string dinamico
        string fecha, hora, jugador1, jugador2, ganador;
        int fichas1, fichas2;

        getline(iss, fecha, ':'); // lee hasta los separadores, char por char
        getline(iss, hora, ':');
        getline(iss, jugador1, ':');
        iss >> fichas1; // lo toma completo
        iss.ignore();  // Ignora el delimitador ':'
        getline(iss, jugador2, ':');
        iss >> fichas2;
        iss.ignore();  // Ignora el delimitador ':'
        getline(iss, ganador);

        // Ahora puedes usar los datos leídos
        // Por ejemplo, imprimirlos en la consola:
        cout << "Fecha: " << fecha << "\n"
                  << "Hora: " << hora << "\n"
                  << "Jugador 1: " << jugador1 << ", Fichas: " << fichas1 << "\n"
                  << "Jugador 2: " << jugador2 << ", Fichas: " << fichas2 << "\n"
                  << "Ganador: " << ganador
                  << "\n------------------------\n";
    }

    archivo.close();
}
