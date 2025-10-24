#pragma once
#define TAREA_H
#define TAREA_H

#include <string>

enum class EstadoTarea { PorHacer = 0, EnProgreso = 1, Hecha = 2 };

std::string estadoToString(EstadoTarea e);

class Tarea {
private:
    int id;
    std::string titulo;
    std::string descripcion;
    EstadoTarea estado;

    // Campos opcionales SIN std::optional
    std::string fechaVencimiento; // "" => sin fecha
    int prioridad;                // -1 => sin prioridad
    int idAsignadoA;              // -1 => no asignada

public:
    Tarea(int id, const std::string& titulo, const std::string& descripcion);

    // Getters
    int getId() const;
    const std::string& getTitulo() const;
    const std::string& getDescripcion() const;
    EstadoTarea getEstado() const;

    const std::string& getFechaVencimiento() const; // "" si no hay
    int  getPrioridad() const;                       // -1 si no hay
    int  getIdAsignadoA() const;                     // -1 si no hay

    bool tieneFecha() const;
    bool tienePrioridad() const;
    bool estaAsignada() const;

    // Setters
    void setTitulo(const std::string& t);
    void setDescripcion(const std::string& d);
    void setEstado(EstadoTarea e);

    void setFechaVencimiento(const std::string& f); // pasar "" para limpiar
    void limpiarFechaVencimiento();

    void setPrioridad(int p); // pasar -1 para limpiar
    void limpiarPrioridad();

    void asignarA(int usuarioId); // pasar -1 para desasignar
    void desasignar();

    // UI
    void imprimirResumen() const;
    void imprimirDetalle() const;
};
