#pragma once
#include "grafo.h"

/**
 * @brief Clase encargada de gestionar todo el renderizado del grafo y la interfaz gráfica.
 */
class Renderer{
public:
    /**
     * @brief Constructor por defecto de Renderer.
     */
    Renderer();

    /**
     * @brief Inicializa el renderizador con un grafo dado.
     * @param g Grafo a utilizar en el renderizado.
     */
    void init(Grafo g);

    /**
     * @brief Procesa y ejecuta el renderizado del grafo en cada frame.
     * @param g Referencia al grafo a renderizar.
     */
    void renderProcess(Grafo& g);
private:
    /**
     * @brief Dibuja el grafo completo, incluyendo nodos y aristas.
     * @param g Referencia al grafo a dibujar.
     */
    void drawGraph(Grafo& g);

    /**
     * @brief Dibuja un nodo en pantalla.
     * @param nodo Nodo a dibujar.
     * @param start Indica si es el nodo de inicio.
     * @param end Indica si es el nodo de fin.
     */
    void drawNode(NodoDatos nodo, bool start, bool end);

    /**
     * @brief Dibuja una arista (enlace) entre dos nodos.
     * @param n1 Nodo de origen.
     * @param n2 Nodo de destino.
     * @param dist Distancia o peso de la arista.
     * @param path Indica si la arista pertenece a un camino resaltado.
     */
    void drawEdge(NodoDatos n1, NodoDatos n2, double dist, bool path);

    /**
     * @brief Convierte las coordenadas del nodo a coordenadas de pantalla.
     * @param nodo Nodo cuyas coordenadas serán convertidas.
     */
    void nodeToScreenCoords(NodoDatos& nodo);

    /**
     * @brief Establece el estado hover sobre un nodo según la posición del mouse.
     * @param n Nodo sobre el que verificar el hover.
     */
    void setHover(NodoDatos& n);

    /**
     * @brief Ancho de la ventana de renderizado.
     */
    int windowWidth;

    /**
     * @brief Alto de la ventana de renderizado.
     */
    int windowHeight;

    /**
     * @brief Offset horizontal para la visualización.
     */
    double xOffset = 0;

    /**
     * @brief Offset vertical para la visualización.
     */
    double yOffset = 0;

    /**
     * @brief Valor máximo en X entre los nodos del grafo.
     */
    double xMax = -1;

    /**
     * @brief Valor máximo en Y entre los nodos del grafo.
     */
    double yMax = -1;

    /**
     * @brief Radio utilizado para el dibujo de los nodos.
     */
    int radius;

    /**
     * @brief Opcion para mostrar los costos de cada arista entre nodos.
     */
    bool mostrarCostos;
};
