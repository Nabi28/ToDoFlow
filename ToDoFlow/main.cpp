#include "Tablero.h"
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <clocale>

using namespace std;

static string pedirLinea(const string& prompt) {
    cout << prompt;
    string s; getline(cin, s);
    return s;
}

static int pedirEntero(const string& prompt, int minv, int maxv) {
    while (true) {
        cout << prompt;
        string line; getline(cin, line);
        try {
            int v = stoi(line);
            if (v < minv || v > maxv) throw out_of_range("rango");
            return v;
        }
        catch (...) {
            cout << "Valor inválido. Intenta de nuevo.\n";
        }
    }
}

static void imprimirMenu() {
    cout
        << "\n========== ToDoFlow ==========\n"
        << "1) Crear usuario\n"
        << "2) Crear tarea\n"
        << "3) Listar usuarios\n"
        << "4) Listar tareas (resumen)\n"
        << "5) Listar tareas (detallado)\n"
        << "6) Asignar tarea a usuario\n"
        << "7) Cambiar estado de tarea\n"
        << "8) Listar tareas por estado\n"
        << "9) Listar tareas por usuario\n"
        << "10) Eliminar tarea\n"
        << "11) Eliminar usuario\n"
        << "0) Salir\n";
}

int main() {
    setlocale(LC_ALL, "");
    system("chcp 65001 > nul");
    Tablero tablero;

    // Utilidad para limpiar espacios
    auto trim = [](string s) {
        size_t a = s.find_first_not_of(" \t\r\n");
        if (a == string::npos) return string{};
        size_t b = s.find_last_not_of(" \t\r\n");
        return s.substr(a, b - a + 1);
        };

    while (true) {
        imprimirMenu();
        int op = pedirEntero("Selecciona una opción: ", 0, 11);
        if (op == 0) break;

        switch (op) {
        case 1: {
            string n = pedirLinea("Nombre: ");
            string e = pedirLinea("Email: ");
            int id = tablero.crearUsuario(n, e);
            cout << "Usuario creado con ID " << id << ".\n";
            break;
        }
        case 2: {
            string t = pedirLinea("Título: ");
            string d = pedirLinea("Descripción: ");
            string p = pedirLinea("Prioridad (1-5) o vacío: ");
            int pr = -1;
            if (!trim(p).empty()) {
                try {
                    int pv = stoi(p);
                    if (pv >= 1 && pv <= 5) pr = pv;
                    else cout << "Prioridad fuera de rango. Se omite.\n";
                }
                catch (...) {
                    cout << "Prioridad inválida. Se omite.\n";
                }
            }
            string f = pedirLinea("Fecha vencimiento (YYYY-MM-DD) o vacío: ");
            f = trim(f); // si el usuario mete espacios, queda ""
            int id = tablero.crearTarea(t, d, pr, f);
            cout << "Tarea creada con ID " << id << ".\n";
            break;
        }
        case 3:
            tablero.listarUsuarios();
            break;
        case 4:
            tablero.listarTareas(false);
            break;
        case 5:
            tablero.listarTareas(true);
            break;
        case 6: {
            int idT = pedirEntero("ID de tarea: ", 1, 1'000'000);
            int idU = pedirEntero("ID de usuario: ", 1, 1'000'000);
            if (tablero.asignarTarea(idT, idU)) cout << "Tarea asignada.\n";
            else cout << "Error: IDs inválidos.\n";
            break;
        }
        case 7: {
            int idT = pedirEntero("ID de tarea: ", 1, 1'000'000);
            int e = pedirEntero("Estado (0=PorHacer,1=EnProgreso,2=Hecha): ", 0, 2);
            if (tablero.cambiarEstado(idT, static_cast<EstadoTarea>(e)))
                cout << "Estado actualizado.\n";
            else
                cout << "No se pudo actualizar.\n";
            break;
        }
        case 8: {
            int e = pedirEntero("Estado (0=PorHacer,1=EnProgreso,2=Hecha): ", 0, 2);
            tablero.listarTareasPorEstado(static_cast<EstadoTarea>(e));
            break;
        }
        case 9: {
            int idU = pedirEntero("ID de usuario: ", 1, 1'000'000);
            tablero.listarTareasPorUsuario(idU);
            break;
        }
        case 10: {
            int id = pedirEntero("ID de tarea a eliminar: ", 1, 1'000'000);
            if (tablero.eliminarTarea(id)) cout << "Tarea eliminada.\n";
            else cout << "No se encontró la tarea.\n";
            break;
        }
        case 11: {
            int id = pedirEntero("ID de usuario a eliminar: ", 1, 1'000'000);
            if (tablero.eliminarUsuario(id)) cout << "Usuario eliminado.\n";
            else cout << "No se encontró el usuario.\n";
            break;
        }
        }
    }

    cout << "Saliendo...\n";
    return 0;
}