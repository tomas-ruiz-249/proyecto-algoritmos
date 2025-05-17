#pragma once
#include <string>
#include <iostream>

using std::string;

/**
 * @brief Representa un nodo con posición y nombre.
 */
struct NodoDatos{
    double x;        ///< Coordenada x (puede representar latitud/longitud u otro valor numérico).
    double y;        ///< Coordenada y (puede representar latitud/longitud u otro valor numérico).
    string nombre;   ///< Nombre identificador del nodo.
    bool mouseHover = false; ///< Indica si el mouse está sobre este nodo (usado en la interfaz gráfica).

    /**
     * @brief Constructor por defecto.
     */
    NodoDatos() = default;

    /**
     * @brief Constructor con parámetros.
     * @param x Coordenada x.
     * @param y Coordenada y.
     * @param nombre Nombre del nodo.
     */
    NodoDatos(double x, double y, string nombre);

    /**
     * @brief Operador de desigualdad.
     * @param n Otro NodoDatos a comparar.
     * @return true si los nodos son diferentes.
     */
    bool operator!=(const NodoDatos& n);

    /**
     * @brief Operador de impresión en flujo de salida.
     * @param os Flujo de salida.
     * @param n NodoDatos a imprimir.
     * @return Referencia al flujo de salida.
     */
    friend std::ostream& operator<<(std::ostream& os, const NodoDatos& n);

    /**
     * @brief Convierte el nodo a string.
     * @return Representación en string del nodo.
     */
    string to_string() const;
};

/**
 * @brief Representa un vecino de un nodo en el grafo, con nombre y distancia (peso de la arista).
 */
struct Vecino{
    string nombre;   ///< Nombre del nodo vecino.
    double dist;     ///< Distancia o peso hacia el vecino.

    /**
     * @brief Constructor por defecto.
     */
    Vecino() = default;

    /**
     * @brief Constructor con nombre y peso.
     * @param nombre Nombre del nodo vecino.
     * @param peso Peso de la arista (distancia).
     */
    Vecino(string nombre, int peso);

    /**
     * @brief Operador de desigualdad.
     * @param v Otro vecino.
     * @return true si son diferentes.
     */
    bool operator!=(const Vecino& v);

    /**
     * @brief Convierte el vecino a string.
     * @return Representación en string.
     */
    string to_string() const;

    /**
     * @brief Operador de impresión en flujo de salida.
     * @param os Flujo de salida.
     * @param v Vecino a imprimir.
     * @return Referencia al flujo de salida.
     */
    friend std::ostream& operator<<(std::ostream& os, const Vecino& v);

    /**
     * @brief Operador menor que (para comparación de vecinos).
     * @param v Otro vecino.
     * @return true si el actual es menor que el otro (según el criterio implementado).
     */
    bool operator<(const Vecino& v);

    /**
     * @brief Operador mayor que (para comparación de vecinos).
     * @param v Otro vecino.
     * @return true si el actual es mayor que el otro (según el criterio implementado).
     */
    bool operator>(const Vecino& v);

    /**
     * @brief Operador de igualdad.
     * @param v Otro vecino.
     * @return true si ambos vecinos son iguales.
     */
    bool operator==(const Vecino& v);
};