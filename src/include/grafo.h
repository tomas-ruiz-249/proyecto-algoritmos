#pragma once
#include "nodo_datos.h"
#include "parser.h"

using std::string;

struct DijkstraEntry{
    string nombre;
    double dist;
    string from;

    DijkstraEntry(){
        this->nombre = "";
        this->dist = -1;
        this->from = "";
    }

    DijkstraEntry(string node, double dist, string from){
        this->nombre = node;
        this->dist = dist;
        this->from = from;
    }

    friend std::ostream& operator<< (std::ostream& os, DijkstraEntry& e){
        os << "(" << e.nombre << ", " << e.dist << ", " << e.from << ")";
        return os;
    }

    bool operator<(const DijkstraEntry& e){
        return this->dist < e.dist;
    }


    bool operator>(const DijkstraEntry& e){
        return this->dist > e.dist;
    }


    bool operator==(const DijkstraEntry& e){
        return this->dist == e.dist;
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
    void dijkstra(string A, string B);
    string start;
    string end;
private:
    HashMap<string, ListaEnlazada<Vecino>> adyacentes;
    HashMap<string, NodoDatos> nodos;
    Parser parser;
};