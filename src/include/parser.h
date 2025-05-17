#pragma once

#include "nodo_datos.h"
#include <string>
#include "hashmap.h"
#include "lista_enlazada.h"
#include <vector>

using std::string;

/**
 * @class Parser
 * @brief Clase encargada de leer y procesar archivos de datos para construir la estructura de nodos y adyacencias de un grafo.
 */
class Parser{
public:
    /**
     * @brief Constructor que inicializa el parser con la ruta del archivo de datos.
     * @param path Ruta del archivo de datos del grafo.
     */
    Parser(const std::string& path);

    /**
     * @brief Constructor por defecto.
     */
    Parser() = default;

    /**
     * @brief Lee el archivo de datos especificado y llena las estructuras de nodos y adyacencias.
     */
    void leer();

    /**
     * @brief Obtiene el HashMap de nodos cargados.
     * @return Referencia al HashMap con los nodos.
     */
    HashMap<string, NodoDatos>& getNodos();

    /**
     * @brief Obtiene el HashMap de listas enlazadas de adyacentes (vecinos).
     * @return Referencia al HashMap de listas enlazadas de vecinos.
     */
    HashMap<string, ListaEnlazada<Vecino>>& getAdyacentes();

private:
    /**
     * @brief Ruta del archivo de datos del grafo.
     */
    string pathToGraphData;

    /**
     * @brief HashMap que almacena los nodos leídos.
     */
    HashMap<string, NodoDatos> nodos;

    /**
     * @brief HashMap que almacena las listas enlazadas de vecinos (adyacencias) para cada nodo.
     */
    HashMap<string, ListaEnlazada<Vecino>> adyacentes;
};
