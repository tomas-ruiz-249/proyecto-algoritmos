#include <limits>
#include "include/grafo.h"
#include "priority_queue.h"

//Grafo
Grafo::Grafo(){
    NodoDatos A(15, 90, string("A"));
    NodoDatos B(10, 50, string("B"));
    NodoDatos C(23, 80, string("C"));
    NodoDatos D(15, 10, string("D"));
    NodoDatos E(25, 40, string("E"));
    
    nodos[A.nombre] = A;
    nodos[B.nombre] = B;
    nodos[C.nombre] = C;
    nodos[D.nombre] = D;
    nodos[E.nombre] = E;

    ListaEnlazada<Vecino> vecinosA;
    ListaEnlazada<Vecino> vecinosB;
    ListaEnlazada<Vecino> vecinosC;
    ListaEnlazada<Vecino> vecinosD;
    ListaEnlazada<Vecino> vecinosE;

    vecinosA.append(Vecino(B.nombre, 3));
    vecinosA.append(Vecino(C.nombre, 2));

    vecinosB.append(Vecino(A.nombre, 3));
    vecinosB.append(Vecino(D.nombre, 2));

    vecinosC.append(Vecino(A.nombre, 2));
    vecinosC.append(Vecino(D.nombre, 1));
    vecinosC.append(Vecino(E.nombre, 4));

    vecinosD.append(Vecino(B.nombre, 2));
    vecinosD.append(Vecino(C.nombre, 1));
    vecinosD.append(Vecino(E.nombre, 2));

    vecinosE.append(Vecino(D.nombre, 2));
    vecinosE.append(Vecino(C.nombre, 4));

    adyacentes[A.nombre] = vecinosA;
    adyacentes[B.nombre] = vecinosB;
    adyacentes[C.nombre] = vecinosC;
    adyacentes[D.nombre] = vecinosD;
    adyacentes[E.nombre] = vecinosE;
    generarDistancias();
    adyacentes.print();
}

void Grafo::print(){
    adyacentes.print();
}

void Grafo::generarDistancias(){
    double dx;
    double dy;
    double distancia;
    NodoDatos actual;
    ListaEnlazada<Vecino> vecinos;

    for(auto nodo : adyacentes){
        actual = nodos[nodo.key];
        vecinos = nodo.value;
        for(auto& vecino : vecinos){
            NodoDatos nodoVecino = nodos[vecino.nombre];
            dx = actual.x - nodoVecino.x;
            dy = actual.y - nodoVecino.y;
            distancia = sqrt(dx*dx + dy*dy);
            vecino.dist = distancia;
        }
    }
}

ListaEnlazada<Vecino> Grafo::getVecinos(string nodo){
    return adyacentes[nodo];
}

NodoDatos Grafo::getNodo(string nodo){
    return nodos[nodo];
}

HashMap<string, NodoDatos> Grafo::getNodos(){
    return nodos;
}

HashMap<string, DijkstraPath> Grafo::dijkstra(){
    string A = start;
    PriorityQueue<Vecino> queue;
    HashMap<string, DijkstraPath> known;
    for(auto& nodo : nodos){
        string nombre = nodo.key;
        if(nombre == A){
            known[nombre] = DijkstraPath(0,"");
        }
        else{
            known[nombre] = DijkstraPath(std::numeric_limits<double>::max(),"");
        }
    }
    queue.enqueue(Vecino(A,0));
    while(!queue.isEmpty()){
        Vecino a = queue.dequeue();
        for(auto ady : getVecinos(a.nombre)){
            double newdist = known[a.nombre].dist + ady.dist;
            if(known[ady.nombre].dist > newdist){
                known[ady.nombre].dist = newdist;
                known[ady.nombre].from = a.nombre;
                queue.enqueue(Vecino(ady.nombre, known[ady.nombre].dist));
            }
        }
    }
    HashMap<string, DijkstraPath> path;
    DijkstraPath current = known[end];
    path[end] = current;
    while(current.from != ""){
        path[current.from] = known[current.from];
        current = known[current.from];
    }
    path.print();
    return path;
}