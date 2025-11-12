// Guard para evitar inclusión múltiple
#ifndef TAREA_H
#define TAREA_H

#include "Librerias.h"
// colores para la consola
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

    // Método auxiliar para validar formato y que la fecha no sea pasada
    static bool validarFecha(const string& fecha) {
        // Verifica formato básico YYYY-MM-DD (longitud 10)
        if (fecha.length() != 10 || fecha[4] != '-' || fecha[7] != '-') {
            return false;
        }

        // Extrae año, mes y día
        int ano, mes, dia;
        try {
            ano = stoi(fecha.substr(0, 4));
            mes = stoi(fecha.substr(5, 2));
            dia = stoi(fecha.substr(8, 2));
        }
        catch (...) {
            return false;
        }

        // Valida rangos básicos
        if (ano < 1900 || ano > 9999 || mes < 1 || mes > 12 || dia < 1 || dia > 31) {
            return false;
        }

        // Obtiene la fecha actual del sistema (versión segura)
        time_t ahora = time(0);
        tm fechaActual;
        localtime_s(&fechaActual, &ahora);

        int anoActual = fechaActual.tm_year + 1900;
        int mesActual = fechaActual.tm_mon + 1;
        int diaActual = fechaActual.tm_mday;

        // Compara con la fecha actual
        if (ano < anoActual) {
            return false;  // Año pasado
        }
        else if (ano == anoActual) {
            if (mes < mesActual) {
                return false;  // Mes pasado
            }
            else if (mes == mesActual) {
                if (dia < diaActual) {
                    return false;  // Día pasado
                }
            }
        }

        return true;
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
        bool fechaValida = false;

        cout << BRIGHT_MAGENTA << "\n--- CREAR NUEVA TAREA ---" << RESET << endl;

        // Obtener ID de usuario con validación (muestra usuarios disponibles)
        idUsuario = obtenerIdUsuarioValido(contenedor);
        cin.ignore();  // Limpiar el buffer de entrada

        // Solicitar título
        cout << "Titulo de la tarea: ";
        getline(cin, titulo);

        // Solicitar descripción
        cout << "Descripcion: ";
        getline(cin, descripcion);

        // Validación de la fecha de vencimiento
        while (!fechaValida) {
            cout << "Fecha de vencimiento (YYYY-MM-DD): ";
            getline(cin, fecha);

            if (!validarFecha(fecha)) {
                cout << BRIGHT_RED << "\nError: Formato de fecha invalido o la fecha es anterior a hoy" << RESET << endl;
                cout << BRIGHT_CYAN << "Use el formato YYYY-MM-DD y asegurese de ingresar la fecha de hoy o una fecha futura" << RESET << endl;
                cout << BRIGHT_CYAN << "Presione Enter para intentar de nuevo..." << RESET;
                cin.get();
                cout << endl;
                continue;
            }

            fechaValida = true;
        }

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