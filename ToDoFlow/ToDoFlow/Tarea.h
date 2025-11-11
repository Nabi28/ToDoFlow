// Guard para evitar inclusión múltiple
#ifndef TAREA_H
#define TAREA_H

#include "Librerias.h"

// Clase que representa una tarea individual
class Tarea {
private:
    // Atributos privados de la tarea
    string TituloTarea;        // Título de la tarea
    string Descripcion;        // Descripción detallada
    string FechaVencimiento;   // Fecha límite de la tarea
    bool Estado;               // Estado: true = completada, false = pendiente

public:
    // Constructor: inicializa una tarea con título, descripción y fecha
    Tarea(string titulo, string descripcion, string fecha) {
        this->TituloTarea = titulo;
        this->Descripcion = descripcion;
        this->FechaVencimiento = fecha;
        this->Estado = false;  // Por defecto, la tarea está pendiente
    }

    // Método para confirmar la creación de una tarea
    void CrearTarea() {
        cout << "Tarea creada: " << TituloTarea << endl;
    }

    // Método para actualizar los datos de una tarea existente
    void ActualizarTarea(string titulo, string descripcion, string fecha) {
        this->TituloTarea = titulo;
        this->Descripcion = descripcion;
        this->FechaVencimiento = fecha;
        cout << "Tarea actualizada exitosamente" << endl;
    }

    // Método para notificar la eliminación de una tarea
    void BorrarTarea() {
        cout << "Tarea '" << TituloTarea << "' eliminada" << endl;
    }

    // Getter: obtiene el estado de la tarea
    bool getEstado() {
        return Estado;
    }

    // Setter: cambia el estado de la tarea (completada/pendiente)
    void setEstado(bool estado) {
        this->Estado = estado;
    }

    // Método para buscar una tarea (simulación)
    void BuscarTarea() {
        cout << "Buscando tarea: " << TituloTarea << endl;
    }

    // Getter: obtiene el título de la tarea
    string getTitulo() {
        return TituloTarea;
    }

    // Getter: obtiene la descripción de la tarea
    string getDescripcion() {
        return Descripcion;
    }

    // Getter: obtiene la fecha de vencimiento
    string getFechaVencimiento() {
        return FechaVencimiento;
    }

    // Método para mostrar toda la información de la tarea
    void mostrarInfo() {
        cout << "Titulo: " << TituloTarea << endl;
        cout << "Descripcion: " << Descripcion << endl;
        cout << "Fecha de Vencimiento: " << FechaVencimiento << endl;
        // Operador ternario: si Estado es true, muestra "Completada", sino "Pendiente"
        cout << "Estado: " << (Estado ? "Completada" : "Pendiente") << endl;
    }

    // Método estático para crear una tarea mediante menú interactivo
    // Retorna un puntero a la nueva tarea creada
    static Tarea* menuCrearTarea() {
        string titulo, descripcion, fecha;

        cout << "\n--- CREAR NUEVA TAREA ---" << endl;
        cin.ignore();  // Limpiar el buffer de entrada

        // Solicitar datos al usuario
        cout << "Titulo de la tarea: ";
        getline(cin, titulo);

        cout << "Descripcion: ";
        getline(cin, descripcion);

        cout << "Fecha de vencimiento (YYYY-MM-DD): ";
        getline(cin, fecha);

        // Crear y retornar un puntero a la nueva tarea
        return new Tarea(titulo, descripcion, fecha);
    }

    // Método para convertir la tarea a formato JSON
    json toJson() {
        json j;
        j["titulo"] = TituloTarea;
        j["descripcion"] = Descripcion;
        j["fecha_vencimiento"] = FechaVencimiento;
        j["estado"] = Estado;
        return j;
    }

    // Método estático para crear una tarea desde JSON
    static Tarea* fromJson(const json& j) {
        Tarea* tarea = new Tarea(
            j["titulo"].get<string>(),
            j["descripcion"].get<string>(),
            j["fecha_vencimiento"].get<string>()
        );
        tarea->setEstado(j["estado"].get<bool>());
        return tarea;
    }
};

#endif
