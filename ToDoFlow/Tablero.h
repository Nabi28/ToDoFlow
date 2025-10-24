#pragma once
#ifndef TABLERO_H
#define TABLERO_H

#include "Tarea.h"
#include "Usuario.h"
#include <vector>
#include <string>

class Tablero {
private:
    std::vector<Tarea> tareas;
    std::vector<Usuario> usuarios;
    int nextTareaId = 1;
    int nextUsuarioId = 1;

    Tarea* encontrarTareaPorId(int id);
    Usuario* encontrarUsuarioPorId(int id);

public:
    int crearUsuario(const std::string& nombre, const std::string& email);
    int crearTarea(const std::string& titulo, const std::string& descripcion,
        int prioridad = -1, const std::string& fecha = "");

    void listarUsuarios() const;
    void listarTareas(bool detallado = false) const;

    bool asignarTarea(int idTarea, int idUsuario);
    bool cambiarEstado(int idTarea, EstadoTarea nuevo);

    bool eliminarTarea(int idTarea);
    bool eliminarUsuario(int idUsuario);

    void listarTareasPorEstado(EstadoTarea estado) const;
    void listarTareasPorUsuario(int idUsuario) const;
};

#endif
