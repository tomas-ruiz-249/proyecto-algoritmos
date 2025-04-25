#include <string>
#include "hashmap.h"
#include "lista_enlazada.h"

using std::string;

struct NodoDatos{
    double x;
    double y;
    string name;
    NodoDatos() = default;
    NodoDatos(double x, double y, string name){
        this->x = x;
        this->y = y;
        this->name = name;
    }
    bool operator!=(const NodoDatos& n){
        return name != n.name;
    }
};

struct Vecino{
    NodoDatos nodo;
    int peso;
    Vecino() = default;
    Vecino(NodoDatos nodo, int peso){
        this->nodo = nodo;
        this->peso = peso;
    }
    bool operator!=(const Vecino& v){
        return nodo != v.nodo and peso != v.peso;
    }
    string to_string() const{
        return "[" + nodo.name + ", " + "dist: " + std::to_string(peso)+ "]";
    }
    friend std::ostream& operator<<(std::ostream& os, const Vecino& v){
        os << v.to_string();
        return os;
    }
};

class Grafo{
public:
    Grafo(){
        Vector<NodoDatos> nodos;
        NodoDatos A(0,0, "A");
        NodoDatos B(0,0, "B");
        NodoDatos C(0,0, "C");
        NodoDatos D(0,0, "D");
        NodoDatos E(0,0, "E");

        ListaEnlazada<Vecino> vecinosA;
        ListaEnlazada<Vecino> vecinosB;
        ListaEnlazada<Vecino> vecinosC;
        ListaEnlazada<Vecino> vecinosD;
        ListaEnlazada<Vecino> vecinosE;
        ListaEnlazada<Vecino> vecinosF;

        vecinosA.append(Vecino(B,3));
        vecinosA.append(Vecino(C,2));

        vecinosB.append(Vecino(A,3));
        vecinosB.append(Vecino(D,2));

        vecinosC.append(Vecino(A,2));
        vecinosC.append(Vecino(D,1));
        vecinosC.append(Vecino(E,4));

        vecinosD.append(Vecino(B,2));
        vecinosD.append(Vecino(C,1));
        vecinosD.append(Vecino(E,2));

        vecinosE.append(Vecino(D,2));
        vecinosE.append(Vecino(C,4));

        adyacentes.insert(A.name, vecinosA);
        adyacentes.insert(B.name, vecinosB);
        adyacentes.insert(C.name, vecinosC);
        adyacentes.insert(D.name, vecinosD);
        adyacentes.insert(E.name, vecinosE);
    };

    Grafo(Vector<NodoDatos> nodos){
        for(auto& nodo : nodos){
            int c = 1;
            ListaEnlazada<Vecino> vecinos;
            for(auto& otro : nodos){
                if(otro != nodo){
                    Vecino v(otro, c * 3);
                    vecinos.append(v);
                    c++;
                }
            }
            adyacentes.insert(nodo.name, vecinos);
        }
    }
    void print(){
        adyacentes.print();
    }
private:
    HashMap<string, ListaEnlazada<Vecino>> adyacentes;
};