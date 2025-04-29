#include "include/grafo.h"

//Grafo
Grafo::Grafo(){
    NodoDatos A(0,0, string("A"));
    NodoDatos B(0,0, string("B"));
    NodoDatos C(0,0, string("C"));
    NodoDatos D(0,0, string("D"));
    NodoDatos E(0,0, string("E"));
    
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
    ListaEnlazada<Vecino> vecinosF;

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
    adyacentes.print();
}

void Grafo::print(){
    adyacentes.print();
}