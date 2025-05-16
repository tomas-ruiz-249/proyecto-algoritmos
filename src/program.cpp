#include "program.h"
#include "raylib.h"

Program::Program() : grafo("data.txt") {
    renderer.init(grafo);
}

void Program::mainLoop(){
    while(!WindowShouldClose()){
        renderer.renderProcess(grafo);
    }
}