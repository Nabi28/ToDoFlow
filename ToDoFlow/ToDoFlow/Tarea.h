// Guard para evitar inclusión múltiple
#ifndef TAREA_H
#define TAREA_H

#include "Librerias.h"

#define BRIGHT_RED     "\033[91m"
#define BRIGHT_GREEN   "\033[92m"
#define BRIGHT_BLUE    "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN    "\033[96m"
#define RESET "\033[0m"

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
        cout << BRIGHT_GREEN << "Tarea creada: " << TituloTarea << RESET << endl;
    }

    // Método para actualizar los datos de una tarea existente
    void ActualizarTarea(string titulo, string descripcion, string fecha) {
        this->TituloTarea = titulo;
        this->Descripcion = descripcion;
        this->FechaVencimiento = fecha;
        cout << BRIGHT_GREEN << "Tarea actualizada exitosamente" << RESET << endl;
    }

    // Método para notificar la eliminación de una tarea
    void BorrarTarea() {
        cout << BRIGHT_RED << "Tarea '" << TituloTarea << "' eliminada" << RESET << endl;
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
        cout << BRIGHT_BLUE << "Buscando tarea: " << TituloTarea << RESET << endl;
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
        cout << BRIGHT_CYAN << "Titulo: " << TituloTarea << RESET << endl;
        cout << BRIGHT_CYAN << "Descripcion: " << Descripcion << RESET << endl;
        cout << BRIGHT_CYAN << "Fecha de Vencimiento: " << FechaVencimiento << RESET << endl;
        // Operador ternario: si Estado es true, muestra "Completada", sino "Pendiente"
        cout << BRIGHT_CYAN << "Estado: " << RESET << (Estado ? "Completada" : "Pendiente") << endl;
    }

    // Método estático para crear una tarea mediante menú interactivo
    // Retorna un puntero a la nueva tarea creada
    static Tarea* menuCrearTarea() {
        string titulo, descripcion, fecha;

        cout << BRIGHT_MAGENTA << "\n--- CREAR NUEVA TAREA ---" << RESET << endl;
        cin.ignore();  // Limpiar el buffer de entrada

        // Solicitar datos al usuario
        cout << BRIGHT_CYAN << "Titulo de la tarea: ";
        getline(cin, titulo);

        cout << BRIGHT_CYAN << "Descripcion: ";
        getline(cin, descripcion);

        cout << BRIGHT_CYAN << "Fecha de vencimiento (YYYY-MM-DD): ";
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
