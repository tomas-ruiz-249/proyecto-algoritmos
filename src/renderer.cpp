#include "raylib.h"
#include "renderer.h"
#include <cmath>
#include <algorithm>

Renderer::Renderer(){
    windowWidth = 1200;
    windowHeight = 600;
    radius = windowHeight/30;

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

void Renderer::drawNode(NodoDatos nodo, bool start, bool end){
    nodeToScreenCoords(nodo);
    Color color;
    if(start){
        color = GREEN;
    }
    else if(end){
        color = RED;
    }
    else{
        color = BLUE;
    }
    if(nodo.mouseHover){
        auto hsv = ColorToHSV(color);
        color = ColorFromHSV(hsv.x, hsv.y * 0.5, hsv.z);
    }
    DrawCircle(nodo.x, nodo.y, radius, color);
    DrawText(nodo.nombre.c_str(), nodo.x - radius * 0.5, nodo.y - radius * 0.5, radius, BLACK);
}

double roundDec(double num, int places){
    double multiplier = pow(10, places);
    return ceil(num * multiplier) / multiplier;
}

void Renderer::drawEdge(NodoDatos n1, NodoDatos n2, double dist, bool path){
    Color color = BLACK;
    if(path){
        color = ORANGE;
    }
    nodeToScreenCoords(n1);
    nodeToScreenCoords(n2);
    int xMid = (n1.x + n2.x)/2;
    int yMid = (n1.y + n2.y)/2;

    int font = windowHeight/30;
    int fontWidth = font / 2;
    string text = std::to_string(roundDec(dist, 4));
    text.resize(5);
    int ox = text.length()/2 * fontWidth;
    int oy = font / 2;
    DrawText(text.c_str(), xMid - ox, yMid - oy, font, color);
    DrawLine(n1.x, n1.y, n2.x, n2.y, color);
}

void Renderer::nodeToScreenCoords(NodoDatos& nodo){
    int min = std::min(windowWidth, windowHeight);
    nodo.x *= min / xMax;
    nodo.x += (windowWidth - min)/2;
    nodo.y *= min / yMax;
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

void setBeginningOrEnd(NodoDatos n, Grafo& g){
    if(n.mouseHover){
        if(IsMouseButtonPressed(0)){
            cout << n.nombre + " is beginning\n";
            g.start = n.nombre;
        }
        else if(IsMouseButtonPressed(1)){
            cout << n.nombre + " is end\n";
            g.end = n.nombre;
        }
    }
}

void Renderer::drawGraph(Grafo& g){
    HashMap<string, DijkstraPath> path;
    if(!g.start.empty()){
        path = g.dijkstra();
    }
    for(auto nodo : g.getNodos()){
        string nodoNombre = nodo.value.nombre;
        for(auto vecino : g.getVecinos(nodo.key)){
            NodoDatos nodoVecino = g.getNodo(vecino.nombre);
            if(path[nodoNombre].from == nodoVecino.nombre || path[nodoVecino.nombre].from == nodoNombre){
                drawEdge(nodo.value, nodoVecino, vecino.dist, true);
            }
            else{
                drawEdge(nodo.value, nodoVecino, vecino.dist, false);
            }
        }
    }
    for(auto nodo : g.getNodos()){
        setHover(nodo.value);
        setBeginningOrEnd(nodo.value, g);
        bool start = g.start == nodo.value.nombre;
        bool end = g.end == nodo.value.nombre;
        drawNode(nodo.value, start, end);
    }
}

        
void Renderer::renderProcess(Grafo& g){
    BeginDrawing();
        ClearBackground(RAYWHITE);
        drawGraph(g);
    EndDrawing();
}