#include "program.h"
#include "raylib.h"

Program::Program(){
    renderer.init(grafo);
}

void Program::mainLoop(){
    while(!WindowShouldClose()){
        renderer.renderProcess(grafo);
    }
}