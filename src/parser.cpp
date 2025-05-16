#include "parser.h"
#include "nodo_datos.h"
#include "hashmap.h"
#include "lista_enlazada.h"
#include "vector.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cmath>
#include <iostream>
#include <filesystem>

using std::string;
using std::cout;
using std::endl;

std::string getWorkingDir() {
    return std::filesystem::current_path().string();
}

Parser::Parser(const std::string& archivoNombre)
{
    std::string workingDir = getWorkingDir();
    #ifdef _MSC_VER
    pathToGraphData = workingDir + "\\..\\..\\assets\\" + archivoNombre;
    #endif
    #ifdef __GNUC__
    pathToGraphData = workingDir + "/../assets/" + archivoNombre;
    #endif
}

void Parser::leer() {
    std::cout << "[DEBUG] Intentando abrir: " << pathToGraphData << std::endl;
    std::ifstream file(pathToGraphData);
    if (!file.is_open()) {
        std::cout << "[ERROR] No se pudo abrir el archivo: " << pathToGraphData << std::endl;
        throw std::runtime_error("No se pudo abrir el archivo: " + pathToGraphData);
    } else {
        std::cout << "[INFO] Archivo abierto correctamente: " << pathToGraphData << std::endl;
    }

    Vector<string> enlacesLineas;

    string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        Vector<string> tokens;
        std::istringstream ss(line);
        string token;
        while (std::getline(ss, token, ',')) {
            tokens.push(token);
        }

        if (tokens.getSize() >= 4 && tokens[0] == "NODO") {
            double x, y;
            try {
                x = std::stod(tokens[1]);
                y = std::stod(tokens[2]);
            } catch (...) {
                continue;
            }
            string nombreNodo = tokens[3];
            nodos[nombreNodo] = NodoDatos(x, y, nombreNodo);
            adyacentes[nombreNodo] = ListaEnlazada<Vecino>();
        }
        else if (tokens.getSize() == 3 && tokens[0] == "ENLACE") {
            enlacesLineas.push(line);
        }
    }
    file.close();

    for (int i = 0; i < enlacesLineas.getSize(); ++i) {
        Vector<string> tokens;
        std::istringstream ss(enlacesLineas[i]);
        string token;
        while (std::getline(ss, token, ',')) tokens.push(token);
        if (tokens.getSize() != 3) continue;

        string origen = tokens[1];
        string destino = tokens[2];

        if(nodos.containsKey(origen) && nodos.containsKey(destino)) {
            NodoDatos& nodoOrigen = nodos[origen];
            NodoDatos& nodoDestino = nodos[destino];
            double dx = nodoOrigen.x - nodoDestino.x;
            double dy = nodoOrigen.y - nodoDestino.y;
            double distancia = std::sqrt(dx * dx + dy * dy);

            bool ya_esta = false;
            for (auto& v : adyacentes[origen]) {
                if (v.nombre == destino) { ya_esta = true; break; }
            }
            if (!ya_esta)
                adyacentes[origen].append(Vecino(destino, distancia));

            ya_esta = false;
            for (auto& v : adyacentes[destino]) {
                if (v.nombre == origen) { ya_esta = true; break; }
            }
            if (!ya_esta)
                adyacentes[destino].append(Vecino(origen, distancia));
        }
    }

    cout << "Archivo cargado correctamente y nodos/enlaces creados (con distancias bidireccionales)." << endl;
}

HashMap<string, NodoDatos>& Parser::getNodos() {
    return nodos;
}

HashMap<string, ListaEnlazada<Vecino>>& Parser::getAdyacentes() {
    return adyacentes;
}
