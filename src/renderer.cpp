#include "raylib.h"
#include "renderer.h"

Renderer::Renderer(){
    windowWidth = 800;
    windowHeight = 400;
}

void Renderer::init(){
    InitWindow(windowWidth, windowHeight, "Djikstra");
}

void Renderer::renderProcess(){
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("test", 30, 30, 20, RED);
    EndDrawing();
}