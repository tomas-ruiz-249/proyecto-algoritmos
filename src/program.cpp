#include "program.h"
#include "raylib.h"

Program::Program(){
    grafo = Grafo();
    renderer = Renderer();
    renderer.init(grafo);
}

void Program::mainLoop(){
    while(!WindowShouldClose()){
        renderer.renderProcess(grafo);
    }
}
