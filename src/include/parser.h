#pragma once

#include "nodo_datos.h"
#include <string>
#include "hashmap.h"
#include "lista_enlazada.h"
#include <vector>

using std::string;

class Parser{
public:
    Parser(const std::string& path);
    Parser() = default;
    void leer();
    HashMap<string, NodoDatos>& getNodos();
    HashMap<string, ListaEnlazada<Vecino>>& getAdyacentes();

private:
    string pathToGraphData;
    HashMap<string, NodoDatos> nodos;
    HashMap<string, ListaEnlazada<Vecino>> adyacentes;
};