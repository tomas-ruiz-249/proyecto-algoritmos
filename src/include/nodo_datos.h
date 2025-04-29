#pragma once
#include <string>

using std::string;

struct NodoDatos{
    double x;
    double y;
    string nombre;
    NodoDatos() = default;
    NodoDatos(double x, double y, string nombre);
    bool operator!=(const NodoDatos& n);
    string to_string();
};

struct Vecino{
    string nombre;
    int dist;
    Vecino() = default;
    Vecino(string nombre, int peso);
    bool operator!=(const Vecino& v);
    string to_string() const;
    friend std::ostream& operator<<(std::ostream& os, const Vecino& v);
};