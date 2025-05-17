#pragma once
#include "nodo_datos.h"
#include "parser.h"

using std::string;

/**
 * @struct DijkstraPath
 * @brief Estructura que representa la información de un camino en el algoritmo de Dijkstra.
 *
 * Contiene la distancia desde el nodo origen y el nodo previo en el camino más corto.
 */
struct DijkstraPath{
    double dist;    /**< Distancia acumulada desde el nodo origen. */
    string from;    /**< Nodo previo en el camino más corto. */

    /**
     * @brief Constructor por defecto. Inicializa dist en -1 y from como cadena vacía.
     */
    DijkstraPath(){
        this->dist = -1;
        this->from = "";
    }

    /**
     * @brief Constructor que inicializa los valores de distancia y nodo previo.
     * @param dist Distancia acumulada.
     * @param from Nodo previo en el camino.
     */
    DijkstraPath(double dist, string from){
        this->dist = dist;
        this->from = from;
    }

    /**
     * @brief Operador para impresión de la estructura DijkstraPath.
     * @param os Flujo de salida.
     * @param e Estructura a imprimir.
     * @return Referencia al flujo de salida.
     */
    friend std::ostream& operator<< (std::ostream& os, DijkstraPath& e){
        os << "(" << e.dist << ", " << e.from << ")";
        return os;
    }

    /**
     * @brief Operador de desigualdad para comparar dos caminos.
     * @param d Otro objeto DijkstraPath.
     * @return true si los objetos son distintos, false en caso contrario.
     */
    bool operator !=(DijkstraPath& d){
        return this->dist != d.dist && this->from != d.from;
    }
};

/**
 * @class Grafo
 * @brief Clase principal para la representación y manejo de grafos.
 *
 * Permite la carga de nodos y enlaces desde archivo, cálculo de distancias,
 * acceso a nodos, vecinos y ejecución del algoritmo de Dijkstra.
 */
class Grafo{
public:
    /**
     * @brief Constructor que inicializa el grafo leyendo desde un archivo.
     * @param path Ruta del archivo de datos del grafo.
     */
    Grafo(const std::string& path);

    /**
     * @brief Imprime la información del grafo (nodos y adyacencias).
     */
    void print();

    /**
     * @brief Calcula y asigna las distancias entre los nodos conectados.
     */
    void generarDistancias();

    /**
     * @brief Obtiene la lista de vecinos (adyacentes) de un nodo.
     * @param nodo Nombre del nodo.
     * @return Lista enlazada de vecinos del nodo.
     */
    ListaEnlazada<Vecino> getVecinos(string nodo);

    /**
     * @brief Obtiene la información de un nodo.
     * @param nodo Nombre del nodo.
     * @return Estructura NodoDatos del nodo solicitado.
     */
    NodoDatos getNodo(string nodo);

    /**
     * @brief Obtiene todos los nodos del grafo.
     * @return HashMap con los nodos.
     */
    HashMap<string, NodoDatos> getNodos();

    /**
     * @brief Ejecuta el algoritmo de Dijkstra para hallar caminos mínimos.
     * @return HashMap con los caminos más cortos desde el nodo origen.
     */
    HashMap<string, DijkstraPath> dijkstra();

    string start;   /**< Nodo de inicio para algoritmos de caminos. */
    string end;     /**< Nodo destino para algoritmos de caminos. */
private:
    HashMap<string, ListaEnlazada<Vecino>> adyacentes;   /**< Lista de adyacencias (vecinos) para cada nodo. */
    HashMap<string, NodoDatos> nodos;                    /**< Información de todos los nodos del grafo. */
    Parser parser;                                       /**< Parser para lectura y procesamiento de archivos de entrada. */
};
