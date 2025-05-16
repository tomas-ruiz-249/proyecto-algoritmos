#include "program.h"
#include "raylib.h"

Program::Program()
    : grafo("ruta_al_archivo.txt") 
{
    renderer.init(grafo);
}

void Program::mainLoop(){
    while(!WindowShouldClose()){
        renderer.renderProcess(grafo);
    }
}