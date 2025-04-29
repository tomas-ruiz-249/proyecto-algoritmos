#pragma once
#include "renderer.h"
#include "grafo.h"

class Program{
public:
    Program();
    void mainLoop();
private:
    Renderer renderer;
    Grafo grafo;
};