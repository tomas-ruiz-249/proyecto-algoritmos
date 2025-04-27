#include "nodo_datos.h"
#include "parser.h"

using std::string;

class Grafo{
public:
    Grafo();
    void print();
private:
    HashMap<string, ListaEnlazada<Vecino>> adyacentes;
    Vector<NodoDatos> nodos;
    Parser parser;
};