#include "raylib.h"
#include "renderer.h"
#include <cmath>

Renderer::Renderer(){
    windowWidth = 1200;
    windowHeight = 600;
    radius = windowWidth/30;

    xOffset = 0;
    yOffset = 0;
    xMax = -1;
    yMax = -1;
}

void Renderer::init(Grafo g){
    int numNodos = g.getNodos().getSize();
    for(auto nodo : g.getNodos()){
        xOffset += nodo.value.x;
        if(xMax < nodo.value.x){
            xMax = nodo.value.x;
        }

        yOffset += nodo.value.y;
        if(yMax < nodo.value.y){
            yMax = nodo.value.y;
        }
    }
    xOffset /= numNodos;
    yOffset /= numNodos;
    xMax += xOffset;
    yMax += yOffset;
    InitWindow(windowWidth, windowHeight, "Djikstra");
}

void Renderer::drawNode(NodoDatos nodo){
    nodeToScreenCoords(nodo);
    Color color;
    if(nodo.mouseHover){
        color = GREEN;
    }
    else{
        color = BLUE;
    }
    DrawCircle(nodo.x, nodo.y, radius, color);
    DrawText(nodo.nombre.c_str(), nodo.x - radius * 0.5, nodo.y - radius * 0.5, radius, BLACK);
}

double roundDec(double num, int places){
    double multiplier = pow(10, places);
    return ceil(num * multiplier) / multiplier;
}

void Renderer::drawEdge(NodoDatos n1, NodoDatos n2, double dist){
    nodeToScreenCoords(n1);
    nodeToScreenCoords(n2);
    int xMid = (n1.x + n2.x)/2;
    int yMid = (n1.y + n2.y)/2;

    int font = windowWidth/30;
    int fontWidth = font / 2;
    string text = std::to_string(roundDec(dist, 4));
    text.resize(5);
    int ox = text.length()/2 * fontWidth;
    int oy = font / 2;
    DrawText(text.c_str(), xMid - ox, yMid - oy, font, BLACK);
    DrawLine(n1.x, n1.y, n2.x, n2.y, BLACK);
}

void Renderer::nodeToScreenCoords(NodoDatos& nodo){
    nodo.x *= windowWidth / xMax;
    nodo.y *= windowHeight / yMax;
}

void Renderer::setHover(NodoDatos& n){
    NodoDatos temp = n;
    nodeToScreenCoords(temp);
    Vector2 pos = GetMousePosition();
    int dx = pos.x - temp.x;
    int dy = pos.y - temp.y;
    int dist = dx * dx + dy * dy;
    if(dist < radius * radius){
        n.mouseHover = true;
    }
    else{
        n.mouseHover = false;
    }
}

void Renderer::drawGraph(Grafo g){
    for(auto nodo : g.getNodos()){
        setHover(nodo.value);
        for(auto vecino : g.getVecinos(nodo.key)){
            NodoDatos nodoVecino = g.getNodo(vecino.nombre);
            setHover(nodoVecino);
            drawEdge(nodo.value, nodoVecino, vecino.dist);
            drawNode(nodoVecino);
        }
        drawNode(nodo.value);
    }
}

void Renderer::renderProcess(Grafo g){
    BeginDrawing();
        ClearBackground(RAYWHITE);
        drawGraph(g);
    EndDrawing();
}