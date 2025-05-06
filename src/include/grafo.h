#pragma once
#include "nodo_datos.h"
#include "parser.h"

using std::string;

struct DijkstraPath{
    double dist;
    string from;

    DijkstraPath(){
        this->dist = -1;
        this->from = "";
    }

    DijkstraPath(double dist, string from){
        this->dist = dist;
        this->from = from;
    }

    friend std::ostream& operator<< (std::ostream& os, DijkstraPath& e){
        os << "(" << e.dist << ", " << e.from << ")";
        return os;
    }
};

class Grafo{
public:
    Grafo();
    void print();
    void generarDistancias();
    ListaEnlazada<Vecino> getVecinos(string nodo);
    NodoDatos getNodo(string nodo);
    HashMap<string, NodoDatos> getNodos();
    HashMap<string, DijkstraPath> dijkstra(string A, string B);
    string start;
    string end;
private:
    HashMap<string, ListaEnlazada<Vecino>> adyacentes;
    HashMap<string, NodoDatos> nodos;
    Parser parser;
};