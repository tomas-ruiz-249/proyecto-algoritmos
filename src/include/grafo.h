#include <string>
#include "hashmap.h"
#include "lista_enlazada.h"

using std::string;

struct NodoDatos{
    double x;
    double y;
    string name;
    NodoDatos() = default;
    NodoDatos(double x, double y, string name);
    bool operator!=(const NodoDatos& n);
};

struct Vecino{
    NodoDatos nodo;
    int peso;
    Vecino() = default;
    Vecino(NodoDatos nodo, int peso);
    bool operator!=(const Vecino& v);
    string to_string() const;
    friend std::ostream& operator<<(std::ostream& os, const Vecino& v);
};

class Grafo{
public:
    Grafo();
    Grafo(Vector<NodoDatos> nodos);
    void print();
private:
    HashMap<string, ListaEnlazada<Vecino>> adyacentes;
};