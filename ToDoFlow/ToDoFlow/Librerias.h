// Guard para evitar múltiples inclusiones del archivo
#ifndef LIBRERIAS_H
#define LIBRERIAS_H

// Bibliotecas estándar de C++
#include <iostream>     // Para entrada/salida (cout, cin)
#include <string>       // Para manejo de cadenas de texto
#include <vector>       // Para usar vectores (arrays dinámicos)
#include <algorithm>    // Para algoritmos como sort, find, etc.
#include <limits>       // Para límites numéricos
#include <fstream>      // Para manejo de archivos
#include <iomanip>      // Para formato de salida

// Biblioteca para manejo de JSON
#include <nlohmann/json.hpp>

// Espacio de nombres estándar (evita escribir std:: cada vez)
using namespace std;

// Alias para facilitar el uso de JSON
using json = nlohmann::json;

#endif
