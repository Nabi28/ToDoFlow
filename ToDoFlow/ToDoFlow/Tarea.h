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
    int IdUsuarioAsignado;     // ID del usuario asignado a la tarea
    string TituloTarea;        // Título de la tarea
    string Descripcion;        // Descripción detallada
    string FechaVencimiento;   // Fecha límite de la tarea
    bool Estado;               // Estado: true = completada, false = pendiente

public:
    // Constructor: inicializa una tarea con ID de usuario, título, descripción y fecha
    Tarea(int idUsuario, string titulo, string descripcion, string fecha) {
        this->IdUsuarioAsignado = idUsuario;
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
        cout << "Buscando tarea: " << TituloTarea << endl;
    }

    // Getter: obtiene el ID del usuario asignado
    int getIdUsuarioAsignado() {
        return IdUsuarioAsignado;
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
        cout << "ID Usuario Asignado: " << IdUsuarioAsignado << endl;
        cout << "Titulo: " << TituloTarea << endl;
        cout << "Descripcion: " << Descripcion << endl;
        cout << "Fecha de Vencimiento: " << FechaVencimiento << endl;
        // Operador ternario: si Estado es true, muestra "Completada", sino "Pendiente"
        cout << "Estado: " << (Estado ? "Completada" : "Pendiente") << endl;
    }

    // Método estático para validar y obtener un ID de usuario válido
    // Recibe un puntero a ContenedorUsuario para verificar existencia
    template<typename ContenedorUsuario>
    static int obtenerIdUsuarioValido(ContenedorUsuario* contenedor) {
        int idUsuario;
        bool idValido = false;

        // Primero muestra los usuarios disponibles
        cout << BRIGHT_MAGENTA << "\n=== Usuarios Disponibles ===" << RESET << endl;
        contenedor->MostrarDatos();
        cout << endl;

        while (!idValido) {
            cout << "ID del usuario asignado: ";

            // Verifica que la entrada sea un número entero
            if (!(cin >> idUsuario)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << BRIGHT_RED << "\nError: Debe ingresar un numero entero" << RESET << endl;
                cout << BRIGHT_CYAN << "Presione Enter para intentar de nuevo..." << RESET;
                cin.get();
                cout << endl;
                continue;
            }

            // Verifica que no sea negativo
            if (idUsuario < 0) {
                cout << BRIGHT_RED << "\nError: El ID no puede ser negativo" << RESET << endl;
                cout << BRIGHT_CYAN << "Presione Enter para intentar de nuevo..." << RESET;
                cin.ignore();
                cin.get();
                cout << endl;
                continue;
            }

            // Verifica que el usuario exista en el contenedor
            if (contenedor->buscarUsuario(idUsuario) == nullptr) {
                cout << BRIGHT_RED << "\nError: El usuario con ID " << idUsuario << " no existe" << RESET << endl;
                cout << BRIGHT_CYAN << "Presione Enter para intentar de nuevo..." << RESET;
                cin.ignore();
                cin.get();
                cout << endl;
                continue;
            }

            idValido = true;
        }

        return idUsuario;
    }

    // Método estático para crear una tarea mediante menú interactivo
    // Retorna un puntero a la nueva tarea creada
    // Recibe un puntero a ContenedorUsuario para validar que el usuario exista
    template<typename ContenedorUsuario>
    static Tarea* menuCrearTarea(ContenedorUsuario* contenedor) {
        int idUsuario;
        string titulo, descripcion, fecha;

        cout << BRIGHT_MAGENTA << "\n--- CREAR NUEVA TAREA ---" << RESET << endl;

        // Obtener ID de usuario con validación (muestra usuarios disponibles)
        idUsuario = obtenerIdUsuarioValido(contenedor);
        cin.ignore();  // Limpiar el buffer de entrada

        // Solicitar datos al usuario
        cout << "Titulo de la tarea: ";
        getline(cin, titulo);

        cout << "Descripcion: ";
        getline(cin, descripcion);

        cout << "Fecha de vencimiento (YYYY-MM-DD): ";
        getline(cin, fecha);

        // Crear y retornar un puntero a la nueva tarea
        return new Tarea(idUsuario, titulo, descripcion, fecha);
    }

    // Método para convertir la tarea a formato JSON
    json toJson() {
        json j;
        j["id_usuario"] = IdUsuarioAsignado;
        j["titulo"] = TituloTarea;
        j["descripcion"] = Descripcion;
        j["fecha_vencimiento"] = FechaVencimiento;
        j["estado"] = Estado;
        return j;
    }

    // Método estático para crear una tarea desde JSON
    static Tarea* fromJson(const json& j) {
        Tarea* tarea = new Tarea(
            j["id_usuario"].get<int>(),
            j["titulo"].get<string>(),
            j["descripcion"].get<string>(),
            j["fecha_vencimiento"].get<string>()
        );
        tarea->setEstado(j["estado"].get<bool>());
        return tarea;
    }
};

#endif