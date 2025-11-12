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

// Colores para la consola
#define BRIGHT_RED     "\033[91m"
#define BRIGHT_GREEN   "\033[92m"
#define BRIGHT_BLUE    "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN    "\033[96m"
#define RESET "\033[0m"

// Biblioteca para manejo de JSON
#include <nlohmann/json.hpp>

// Espacio de nombres estándar (evita escribir std:: cada vez)
using namespace std;

// Alias para facilitar el uso de JSON
using json = nlohmann::json;

#endif
