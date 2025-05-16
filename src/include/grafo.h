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

    bool operator !=(DijkstraPath& d){
        return this->dist != d.dist && this->from != d.from;
    }
};

class Grafo{
public:
    Grafo(const std::string& path);
    void print();
    void generarDistancias();
    ListaEnlazada<Vecino> getVecinos(string nodo);
    NodoDatos getNodo(string nodo);
    HashMap<string, NodoDatos> getNodos();
    HashMap<string, DijkstraPath> dijkstra();
    string start;
    string end;
private:
    HashMap<string, ListaEnlazada<Vecino>> adyacentes;
    HashMap<string, NodoDatos> nodos;
    Parser parser;
};