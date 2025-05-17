#include "nodo_datos.h"
#include <iostream>
//nodoDatos
NodoDatos::NodoDatos(double x, double y, string nombre){
    this->x = x;
    this->y = y;
    this->nombre = nombre;
}

bool NodoDatos::operator!=(const NodoDatos& n){
    return nombre != n.nombre;
}

bool NodoDatos::operator==(const NodoDatos& n)const{
    return nombre == n.nombre;
}

string NodoDatos::to_string() const{
    return nombre + ", (" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

std::ostream& operator<<(std::ostream& os, const NodoDatos& n){
    os << n.to_string();
    return os;
}

//Vecino
Vecino::Vecino(string nombre, int peso){
    this->nombre = nombre;
    this->dist = dist;
}

bool Vecino::operator!=(const Vecino& v){
    return nombre != v.nombre && dist != v.dist;
}

string Vecino::to_string() const{
    return "[" + nombre + ", " + "dist: " + std::to_string(dist)+ "]";
}

std::ostream& operator<<(std::ostream& os, const Vecino& v){
    os << v.to_string();
    return os;
}

bool Vecino::operator<(const Vecino& v){
    return this->dist < v.dist;
}

bool Vecino::operator>(const Vecino& v){
    return this->dist > v.dist;
}

bool Vecino::operator==(const Vecino& v){
    return this->dist == v.dist;
}