#include <limits>
#include "include/grafo.h"
#include "priority_queue.h"

//Grafo
Grafo::Grafo(){
    NodoDatos A(50,  90, string("A"));  // Punto más alto (12h)
    NodoDatos B(72,  84, string("B"));  // Cuadrante superior derecho
    NodoDatos C(86,  67, string("C"));  // Derecha medio-alto
    NodoDatos D(90,  44, string("D"));  // Punto más a la derecha (3h)
    NodoDatos E(80,  24, string("E"));  // Cuadrante inferior derecho
    NodoDatos F(61,  12, string("F"));  // Punto más bajo (6h)
    NodoDatos G(39,  12, string("G"));  // Punto más bajo (6h) - simétrico
    NodoDatos H(20,  24, string("H"));  // Cuadrante inferior izquierdo
    NodoDatos I(10,  44, string("I"));  // Punto más a la izquierda (9h)
    NodoDatos J(14,  67, string("J"));  // Izquierda medio-alto
    NodoDatos K(28,  84, string("K"));  // Cuadrante superior izquierdo
    
    nodos[A.nombre] = A;
    nodos[B.nombre] = B;
    nodos[C.nombre] = C;
    nodos[D.nombre] = D;
    nodos[E.nombre] = E;
    nodos[F.nombre] = F;
    nodos[G.nombre] = G;
    nodos[H.nombre] = H;
    nodos[I.nombre] = I;
    nodos[J.nombre] = J;
    nodos[K.nombre] = K;

    ListaEnlazada<Vecino> vecinosA;
    ListaEnlazada<Vecino> vecinosB;
    ListaEnlazada<Vecino> vecinosC;
    ListaEnlazada<Vecino> vecinosD;
    ListaEnlazada<Vecino> vecinosE;
    ListaEnlazada<Vecino> vecinosF;
    ListaEnlazada<Vecino> vecinosG;
    ListaEnlazada<Vecino> vecinosH;
    ListaEnlazada<Vecino> vecinosI;
    ListaEnlazada<Vecino> vecinosJ;
    ListaEnlazada<Vecino> vecinosK;

    // A
    vecinosA.append(Vecino(B.nombre, 1));
    vecinosA.append(Vecino(K.nombre, 1));

    // B
    vecinosB.append(Vecino(A.nombre, 1));
    vecinosB.append(Vecino(C.nombre, 1));

    // C
    vecinosC.append(Vecino(B.nombre, 1));
    vecinosC.append(Vecino(D.nombre, 1));

    // D
    vecinosD.append(Vecino(C.nombre, 1));
    vecinosD.append(Vecino(E.nombre, 1));

    // E
    vecinosE.append(Vecino(D.nombre, 1));
    vecinosE.append(Vecino(F.nombre, 1));

    // F
    vecinosF.append(Vecino(E.nombre, 1));
    vecinosF.append(Vecino(G.nombre, 1));

    // G
    vecinosG.append(Vecino(F.nombre, 1));
    vecinosG.append(Vecino(H.nombre, 1));

    // H
    vecinosH.append(Vecino(G.nombre, 1));
    vecinosH.append(Vecino(I.nombre, 1));

    // I
    vecinosI.append(Vecino(H.nombre, 1));
    vecinosI.append(Vecino(J.nombre, 1));

    // J
    vecinosJ.append(Vecino(I.nombre, 1));
    vecinosJ.append(Vecino(K.nombre, 1));

    // K
    vecinosK.append(Vecino(J.nombre, 1));
    vecinosK.append(Vecino(A.nombre, 1));


    adyacentes[A.nombre] = vecinosA;
    adyacentes[B.nombre] = vecinosB;
    adyacentes[C.nombre] = vecinosC;
    adyacentes[D.nombre] = vecinosD;
    adyacentes[E.nombre] = vecinosE;
    adyacentes[F.nombre] = vecinosF;
    adyacentes[G.nombre] = vecinosG;
    adyacentes[H.nombre] = vecinosH;
    adyacentes[I.nombre] = vecinosI;
    adyacentes[J.nombre] = vecinosJ;
    adyacentes[K.nombre] = vecinosK;
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