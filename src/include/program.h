#pragma once
#include "renderer.h"
#include "grafo.h"

/**
 * @brief Clase principal que controla la ejecución del programa, la inicialización y el ciclo principal.
 */
class Program{
public:
    /**
     * @brief Constructor de la clase Program. Inicializa los componentes principales.
     */
    Program();

    /**
     * @brief Ejecuta el ciclo principal del programa. Controla el renderizado y la interacción del usuario.
     */
    void mainLoop();
private:
    /**
     * @brief Objeto encargado del renderizado gráfico.
     */
    Renderer renderer;

    /**
     * @brief Grafo utilizado por el programa para representar la estructura de datos principal.
     */
    Grafo grafo;
};
