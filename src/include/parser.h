#pragma once

#include "nodo_datos.h"
#include <string>
#include "hashmap.h"
#include "lista_enlazada.h"

class Parser{
public:
    Parser(string path);
    Parser() = default;
private:
    string pathToGraphData;
    HashMap<string, ListaEnlazada<Vecino>> adyacentes;
};