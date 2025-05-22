#include <limits>
#include <cmath>
#include "include/grafo.h"
#include "priority_queue.h"
#include <string>

Grafo::Grafo(const std::string& path) : parser(path) {
    parser.leer();
    nodos = parser.getNodos();
    adyacentes = parser.getAdyacentes();
    nodos.print();
    adyacentes.print();
    generarDistancias();
}

Grafo::Grafo() : parser("data.txt") {
    parser.leer();
    nodos = parser.getNodos();
    adyacentes = parser.getAdyacentes();
    nodos.print();
    adyacentes.print();
    generarDistancias();
}

void Grafo::print() {
    adyacentes.print();
}

void Grafo::generarDistancias() {
    double dx;
    double dy;
    double distancia;
    NodoDatos actual;
    ListaEnlazada<Vecino> vecinos;

    for (auto nodo : adyacentes) {
        actual = nodos[nodo.key];
        vecinos = nodo.value;
        for (auto& vecino : vecinos) {
            NodoDatos nodoVecino = nodos[vecino.nombre];
            dx = actual.x - nodoVecino.x;
            dy = actual.y - nodoVecino.y;
            distancia = sqrt(dx * dx + dy * dy);
            vecino.dist = distancia;
        }
    }
}

ListaEnlazada<Vecino> Grafo::getVecinos(string nodo) {
    return adyacentes[nodo];
}

NodoDatos Grafo::getNodo(string nodo) {
    return nodos[nodo];
}

HashMap<string, NodoDatos> Grafo::getNodos() {
    return nodos;
}

HashMap<string, DijkstraPath> Grafo::dijkstra() {
    string A = start;
    PriorityQueue<Vecino> queue;
    HashMap<string, DijkstraPath> known;
    for (auto& nodo : nodos) {
        string nombre = nodo.key;
        if (nombre == A) {
            known[nombre] = DijkstraPath(0, "");
        }
        else {
            known[nombre] = DijkstraPath(std::numeric_limits<double>::max(), "");
        }
    }
    queue.enqueue(Vecino(A, 0));
    while (!queue.isEmpty()) {
        Vecino a = queue.dequeue();
        for (auto ady : getVecinos(a.nombre)) {
            double newdist = known[a.nombre].dist + ady.dist;
            if (known[ady.nombre].dist > newdist) {
                known[ady.nombre].dist = newdist;
                known[ady.nombre].from = a.nombre;
                queue.enqueue(Vecino(ady.nombre, known[ady.nombre].dist));
            }
        }
    }
    HashMap<string, DijkstraPath> path;
    DijkstraPath current = known[end];
    path[end] = current;
    while (current.from != "") {
        path[current.from] = known[current.from];
        current = known[current.from];
    }
    path.print();
    return path;
}
