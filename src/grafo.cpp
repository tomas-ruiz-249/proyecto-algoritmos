#include "include/grafo.h"

//nodoDatos
NodoDatos::NodoDatos(double x, double y, string name){
    this->x = x;
    this->y = y;
    this->name = name;
}

bool NodoDatos::operator!=(const NodoDatos& n){
    return name != n.name;
}

//Vecino
Vecino::Vecino(NodoDatos nodo, int peso){
    this->nodo = nodo;
    this->peso = peso;
}

bool Vecino::operator!=(const Vecino& v){
    return nodo != v.nodo && peso != v.peso;
}
string Vecino::to_string() const{
    return "[" + nodo.name + ", " + "dist: " + std::to_string(peso)+ "]";
}

std::ostream& operator<<(std::ostream& os, const Vecino& v){
    os << v.to_string();
    return os;
}

//Grafo
Grafo::Grafo(){
}

Grafo::Grafo(){
}

void Grafo::print(){
    adyacentes.print();
}