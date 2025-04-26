#include "program.h"
#include "raylib.h"

Program::Program(){
    renderer.init();
}

void Program::mainLoop(){
    while(!WindowShouldClose()){
        renderer.renderProcess();
    }
}