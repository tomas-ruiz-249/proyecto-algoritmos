#pragma once
#include "nodo_datos.h"
#include "parser.h"

using std::string;

class Grafo{
public:
    Grafo();
    void print();
    void generarDistancias();
    ListaEnlazada<Vecino> getVecinos(string nodo);
    NodoDatos getNodo(string nodo);
    HashMap<string, NodoDatos> getNodos();
    string start;
    string end;
private:
    HashMap<string, ListaEnlazada<Vecino>> adyacentes;
    HashMap<string, NodoDatos> nodos;
    Parser parser;
};