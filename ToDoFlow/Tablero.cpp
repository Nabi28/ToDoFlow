#include "Tablero.h"
#include <iostream>
#include <algorithm>

using namespace std;

Tarea* Tablero::encontrarTareaPorId(int id) {
    for (auto& t : tareas) if (t.getId() == id) return &t;
    return nullptr;
}

Usuario* Tablero::encontrarUsuarioPorId(int id) {
    for (auto& u : usuarios) if (u.getId() == id) return &u;
    return nullptr;
}

int Tablero::crearUsuario(const string& nombre, const string& email) {
    usuarios.emplace_back(nextUsuarioId, nombre, email);
    return nextUsuarioId++;
}

int Tablero::crearTarea(const string& titulo, const string& descripcion,
    int prioridad, const string& fecha) {
    tareas.emplace_back(nextTareaId, titulo, descripcion);
    if (prioridad != -1) tareas.back().setPrioridad(prioridad);
    if (!fecha.empty())  tareas.back().setFechaVencimiento(fecha);
    return nextTareaId++;
}

void Tablero::listarUsuarios() const {
    if (usuarios.empty()) { cout << "No hay usuarios.\n"; return; }
    for (const auto& u : usuarios) u.imprimir();
}

void Tablero::listarTareas(bool detallado) const {
    if (tareas.empty()) { cout << "No hay tareas.\n"; return; }
    for (const auto& t : tareas)
        detallado ? t.imprimirDetalle() : t.imprimirResumen();
}

bool Tablero::asignarTarea(int idTarea, int idUsuario) {
    Tarea* t = encontrarTareaPorId(idTarea);
    if (!t) return false;
    if (!encontrarUsuarioPorId(idUsuario)) return false;
    t->asignarA(idUsuario);
    return true;
}

bool Tablero::cambiarEstado(int idTarea, EstadoTarea nuevo) {
    Tarea* t = encontrarTareaPorId(idTarea);
    if (!t) return false;
    t->setEstado(nuevo);
    return true;
}

bool Tablero::eliminarTarea(int idTarea) {
    auto it = remove_if(tareas.begin(), tareas.end(),
        [&](const Tarea& t) { return t.getId() == idTarea; });
    if (it == tareas.end()) return false;
    tareas.erase(it, tareas.end());
    return true;
}

bool Tablero::eliminarUsuario(int idUsuario) {
    for (auto& t : tareas)
        if (t.getIdAsignadoA() == idUsuario)
            t.desasignar();

    auto it = remove_if(usuarios.begin(), usuarios.end(),
        [&](const Usuario& u) { return u.getId() == idUsuario; });
    if (it == usuarios.end()) return false;
    usuarios.erase(it, usuarios.end());
    return true;
}

void Tablero::listarTareasPorEstado(EstadoTarea estado) const {
    bool found = false;
    for (const auto& t : tareas)
        if (t.getEstado() == estado) { t.imprimirResumen(); found = true; }
    if (!found) cout << "No hay tareas con ese estado.\n";
}

void Tablero::listarTareasPorUsuario(int idUsuario) const {
    bool found = false;
    for (const auto& t : tareas)
        if (t.getIdAsignadoA() == idUsuario) { t.imprimirResumen(); found = true; }
    if (!found) cout << "Ese usuario no tiene tareas asignadas.\n";
}