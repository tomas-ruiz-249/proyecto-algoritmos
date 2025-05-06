#pragma once
#include "grafo.h"

class Renderer{
public:
    Renderer();
    void init(Grafo g);
    void renderProcess(Grafo& g);
private:
    void drawGraph(Grafo& g);
    void drawNode(NodoDatos nodo, bool start, bool end);
    void drawEdge(NodoDatos n1, NodoDatos n2, double dist);
    void nodeToScreenCoords(NodoDatos& nodo);
    void setHover(NodoDatos& n);
    int windowWidth;
    int windowHeight;
    double xOffset = 0;
    double yOffset = 0;
    double xMax = -1;
    double yMax = -1;
    int radius;
};