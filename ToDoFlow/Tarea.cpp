#include "Tarea.h"
#include <iostream>

std::string estadoToString(EstadoTarea e) {
    switch (e) {
    case EstadoTarea::PorHacer:   return "Por hacer";
    case EstadoTarea::EnProgreso: return "En progreso";
    case EstadoTarea::Hecha:      return "Hecha";
    }
    return "Desconocido";
}

Tarea::Tarea(int id, const std::string& titulo, const std::string& descripcion)
    : id(id), titulo(titulo), descripcion(descripcion),
    estado(EstadoTarea::PorHacer), fechaVencimiento(""),
    prioridad(-1), idAsignadoA(-1) {
}

int Tarea::getId() const { return id; }
const std::string& Tarea::getTitulo() const { return titulo; }
const std::string& Tarea::getDescripcion() const { return descripcion; }
EstadoTarea Tarea::getEstado() const { return estado; }

const std::string& Tarea::getFechaVencimiento() const { return fechaVencimiento; }
int  Tarea::getPrioridad() const { return prioridad; }
int  Tarea::getIdAsignadoA() const { return idAsignadoA; }

bool Tarea::tieneFecha() const { return !fechaVencimiento.empty(); }
bool Tarea::tienePrioridad() const { return prioridad != -1; }
bool Tarea::estaAsignada() const { return idAsignadoA != -1; }

void Tarea::setTitulo(const std::string& t) { titulo = t; }
void Tarea::setDescripcion(const std::string& d) { descripcion = d; }
void Tarea::setEstado(EstadoTarea e) { estado = e; }

void Tarea::setFechaVencimiento(const std::string& f) { fechaVencimiento = f; }
void Tarea::limpiarFechaVencimiento() { fechaVencimiento.clear(); }

void Tarea::setPrioridad(int p) { prioridad = p; }
void Tarea::limpiarPrioridad() { prioridad = -1; }

void Tarea::asignarA(int usuarioId) { idAsignadoA = usuarioId; }
void Tarea::desasignar() { idAsignadoA = -1; }

void Tarea::imprimirResumen() const {
    std::cout << "[" << id << "] " << titulo
        << " | Estado: " << estadoToString(estado);
    if (tienePrioridad())    std::cout << " | Prioridad: " << prioridad;
    if (tieneFecha())        std::cout << " | Vence: " << fechaVencimiento;
    if (estaAsignada())      std::cout << " | UsuarioID: " << idAsignadoA;
    std::cout << "\n";
}

void Tarea::imprimirDetalle() const {
    std::cout << "----------------------------------------\n";
    std::cout << "Tarea #" << id << ": " << titulo << "\n";
    std::cout << "Descripción: " << descripcion << "\n";
    std::cout << "Estado: " << estadoToString(estado) << "\n";
    if (tienePrioridad())    std::cout << "Prioridad: " << prioridad << "\n";
    if (tieneFecha())        std::cout << "Fecha de vencimiento: " << fechaVencimiento << "\n";
    if (estaAsignada())      std::cout << "Asignada a (UsuarioID): " << idAsignadoA << "\n";
    std::cout << "----------------------------------------\n";
}