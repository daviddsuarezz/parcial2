#ifndef MATRIZ_H
#define MATRIZ_H



class Matriz{

private:
    int* datos;
    int filas, columnas;

public:
    Matriz();

    Matriz(const int& f,  int const& c);

    ~Matriz();

    int GetFilas() const;

    int GetColumnas() const;

    int GetPosicion(const int& i, const int& j) const;

    void SetPosicion(int i,int j, int n);

};
#endif // MATRIZ_H
