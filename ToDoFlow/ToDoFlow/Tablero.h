// Guard para evitar inclusión múltiple
#ifndef TABLERO_H
#define TABLERO_H

#include "Librerias.h"
#include "Tarea.h"

// Clase que representa un tablero de tareas
class Tablero {
private:
    // Atributos privados del tablero
    int IdTablero;              // ID único del tablero
    string NombreTablero;       // Nombre del tablero
    string FechaCreacion;       // Fecha en que se creó el tablero
    bool Prioridad;             // Indica si el tablero tiene prioridad
    vector<Tarea*> tareas;      // Vector que almacena punteros a las tareas del tablero

public:
    // Constructor: inicializa un tablero con id, nombre y fecha
    Tablero(int id, string nombre, string fecha) {
        this->IdTablero = id;
        this->NombreTablero = nombre;
        this->FechaCreacion = fecha;
        this->Prioridad = false;  // Por defecto, sin prioridad
    }

    // Destructor: libera la memoria de todas las tareas al eliminar el tablero
    ~Tablero() {
        // Recorre todas las tareas y las elimina
        for (auto tarea : tareas) {
            delete tarea;
        }
        // Limpia el vector
        tareas.clear();
    }

    // Método para confirmar la creación del tablero
    void CrearTablero() {
        cout << "Tablero creado: " << NombreTablero << endl;
    }

    // Método para modificar el nombre del tablero
    void ModificarTablero(string nuevoNombre) {
        this->NombreTablero = nuevoNombre;
        cout << "Tablero modificado exitosamente" << endl;
    }

    // Método para actualizar el tablero (placeholder)
    void ActualizarTablero() {
        cout << "Tablero actualizado" << endl;
    }

    // Método para mostrar si el tablero tiene prioridad
    void mostrarPrioridad() {
        cout << "Prioridad: " << (Prioridad ? "Si" : "No") << endl;
    }

    // Setter: establece la prioridad del tablero
    void setPrioridad(bool prioridad) {
        this->Prioridad = prioridad;
    }

    // Getter: obtiene el estado de prioridad
    bool getPrioridad() {
        return Prioridad;
    }

    // Método para notificar la eliminación del tablero
    void EliminarTablero() {
        cout << "Tablero '" << NombreTablero << "' eliminado" << endl;
    }

    // ===== GESTIÓN DE TAREAS =====

    // Agrega una tarea al tablero
    void agregarTarea(Tarea* tarea) {
        tareas.push_back(tarea);
        cout << "Tarea agregada al tablero" << endl;
    }

    // Elimina una tarea del tablero por su índice
    void eliminarTarea(int index) {
        // Verifica que el índice sea válido
        if (index >= 0 && index < tareas.size()) {
            delete tareas[index];  // Libera memoria
            tareas.erase(tareas.begin() + index);  // Elimina del vector
            cout << "Tarea eliminada del tablero" << endl;
        }
    }

    // Muestra todas las tareas del tablero
    void mostrarTareas() {
        cout << "\n=== Tareas del Tablero ===" << endl;
        if (tareas.empty()) {
            cout << "No hay tareas en este tablero" << endl;
            return;
        }
        // Recorre y muestra cada tarea
        for (int i = 0; i < tareas.size(); i++) {
            cout << "\nTarea " << (i + 1) << ":" << endl;
            tareas[i]->mostrarInfo();
        }
    }

    // ===== GETTERS =====

    int getIdTablero() {
        return IdTablero;
    }

    string getNombreTablero() {
        return NombreTablero;
    }

    string getFechaCreacion() {
        return FechaCreacion;
    }

    // Muestra información general del tablero
    void mostrarInfo() {
        cout << "ID Tablero: " << IdTablero << endl;
        cout << "Nombre: " << NombreTablero << endl;
        cout << "Fecha Creacion: " << FechaCreacion << endl;
        cout << "Prioridad: " << (Prioridad ? "Si" : "No") << endl;
        cout << "Numero de Tareas: " << tareas.size() << endl;
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

    // Método estático para crear un tablero mediante menú interactivo
    template<typename GestorTableros>
    static Tablero* menuCrearTablero(GestorTableros* gestor) {
        int id;
        string nombre, fecha;
        bool idValido = false;
        bool nombreValido = false;
        bool fechaValida = false;

        cout << "\n--- CREAR NUEVO TABLERO ---" << endl;

        // Validación del ID del tablero
        while (!idValido) {
            cout << "ID del tablero: ";

            // Verifica que la entrada sea un número entero
            if (!(cin >> id)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nError: El ID debe ser un numero entero, no puede contener letras" << endl;
                cout << "Presione Enter para intentar de nuevo...";
                cin.get();
                cout << endl;
                continue;
            }

            // Verifica que sea un número positivo (mayor a 0)
            if (id <= 0) {
                cout << "\nError: El ID debe ser un numero positivo (mayor a 0)" << endl;
                cout << "Presione Enter para intentar de nuevo...";
                cin.ignore();
                cin.get();
                cout << endl;
                continue;
            }

            // Verifica que el ID no esté repetido
            bool idRepetido = false;
            for (auto tablero : gestor->getTableros()) {
                if (tablero->getIdTablero() == id) {
                    idRepetido = true;
                    break;
                }
            }

            if (idRepetido) {
                cout << "\nError: El ID " << id << " ya esta en uso por otro tablero" << endl;
                cout << "Presione Enter para intentar de nuevo...";
                cin.ignore();
                cin.get();
                cout << endl;
                continue;
            }

            idValido = true;
        }

        cin.ignore();

        // Validación del nombre del tablero
        while (!nombreValido) {
            cout << "Nombre del tablero: ";
            getline(cin, nombre);

            // Verifica que no esté vacío o solo contenga espacios
            if (nombre.empty() || nombre.find_first_not_of(' ') == string::npos) {
                cout << "\nError: El nombre del tablero no puede estar vacio" << endl;
                cout << "Presione Enter para intentar de nuevo...";
                cin.get();
                cout << endl;
                continue;
            }

            nombreValido = true;
        }

        // Validación de la fecha
        while (!fechaValida) {
            cout << "Fecha de creacion (YYYY-MM-DD): ";
            getline(cin, fecha);

            if (!validarFecha(fecha)) {
                cout << "\nError: Formato de fecha invalido o la fecha es anterior a hoy" << endl;
                cout << "Use el formato YYYY-MM-DD y asegurese de ingresar la fecha de hoy o una fecha futura" << endl;
                cout << "Presione Enter para intentar de nuevo...";
                cin.get();
                cout << endl;
                continue;
            }

            fechaValida = true;
        }

        return new Tablero(id, nombre, fecha);
    }

    // Menú interactivo para gestionar las tareas del tablero
    template<typename ContenedorUsuario>
    void menuTareas(ContenedorUsuario* contenedorUsuarios) {
        int opcion;

        do {
            system("cls");
            cout << "\n--- MENU TAREAS DEL TABLERO: " << NombreTablero << " ---" << endl;
            cout << "1. Agregar Tarea" << endl;
            cout << "2. Eliminar Tarea" << endl;
            cout << "3. Actualizar Tarea" << endl;
            cout << "4. Cambiar Estado de Tarea" << endl;
            cout << "5. Mostrar Tareas" << endl;
            cout << "0. Volver" << endl;
            cout << "Opcion: ";
            cin >> opcion;
            system("cls");

            // Validación de entrada
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Opcion invalida" << endl;
                continue;
            }

            switch (opcion) {
            case 1:  // Agregar tarea
                system("cls"); {
                    // Verifica si hay usuarios registrados antes de crear una tarea
                    if (contenedorUsuarios->getUsuarios().empty()) {
                        cout << BRIGHT_RED << "Error: No hay usuarios registrados en el sistema" << RESET << endl;
                        cout << BRIGHT_RED << "Debe crear al menos un usuario antes de agregar tareas" << RESET << endl;
                        cout << BRIGHT_CYAN << "\nPresione Enter para continuar..." << RESET;
                        cin.ignore();
                        cin.get();
                        break;
                    }

                    Tarea* nuevaTarea = Tarea::menuCrearTarea(contenedorUsuarios);
                    agregarTarea(nuevaTarea);
                    nuevaTarea->CrearTarea();
                    cout << BRIGHT_CYAN << "\nPresione Enter para continuar..." << RESET;
                    cin.ignore();
                    cin.get();
                    break;
                }
            case 2:  // Eliminar tarea
                system("cls"); {
                    if (tareas.empty()) {
                        cout << BRIGHT_RED << "No hay tareas para eliminar" << RESET << endl;
                        cout << "\nPresione Enter para continuar...";
                        cin.ignore();
                        cin.get();
                        break;
                    }

                    mostrarTareas();
                    int indiceTarea;
                    cout << "\nNumero de tarea a eliminar: ";

                    // Validar que la entrada sea un número
                    if (!(cin >> indiceTarea)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << BRIGHT_RED << "\nError: Debe ingresar un numero valido" << RESET << endl;
                        cout << "\nPresione Enter para continuar...";
                        cin.get();
                        break;
                    }

                    // Validar que el índice esté en rango
                    if (indiceTarea < 1 || indiceTarea > tareas.size()) {
                        cout << BRIGHT_RED << "\nError: La tarea #" << indiceTarea << " no existe" << RESET << endl;
                        cout << BRIGHT_RED << "Debe ingresar un numero entre 1 y " << tareas.size() << RESET << endl;
                    }
                    else {
                        eliminarTarea(indiceTarea - 1);  // -1 porque el índice empieza en 0
                        cout << BRIGHT_GREEN << "Tarea eliminada exitosamente" << RESET << endl;
                    }

                    cout << "\nPresione Enter para continuar...";
                    cin.ignore();
                    cin.get();
                    break;
                }
            case 3:  // Actualizar tarea
                system("cls"); {
                    if (tareas.empty()) {
                        cout << BRIGHT_RED << "No hay tareas para actualizar" << RESET << endl;
                        cout << "\nPresione Enter para continuar...";
                        cin.ignore();
                        cin.get();
                        break;
                    }

                    mostrarTareas();
                    int indiceTarea;
                    string titulo, descripcion, fecha;

                    cout << "\nNumero de tarea a actualizar: ";

                    // Validar que la entrada sea un número
                    if (!(cin >> indiceTarea)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << BRIGHT_RED << "\nError: Debe ingresar un numero valido" << RESET << endl;
                        cout << "\nPresione Enter para continuar...";
                        cin.get();
                        break;
                    }

                    cin.ignore();

                    // Validar que el índice esté en rango
                    if (indiceTarea < 1 || indiceTarea > tareas.size()) {
                        cout << BRIGHT_RED << "\nError: La tarea #" << indiceTarea << " no existe" << RESET << endl;
                        cout << BRIGHT_RED << "Debe ingresar un numero entre 1 y " << tareas.size() << RESET << endl;
                        cout << "\nPresione Enter para continuar...";
                        cin.get();
                    }
                    else {
                        cout << "Nuevo titulo: ";
                        getline(cin, titulo);
                        cout << "Nueva descripcion: ";
                        getline(cin, descripcion);
                        cout << "Nueva fecha (YYYY-MM-DD): ";
                        getline(cin, fecha);

                        tareas[indiceTarea - 1]->ActualizarTarea(titulo, descripcion, fecha);
                        cout << "\nPresione Enter para continuar...";
                        cin.get();
                    }
                    break;
                }
            case 4:  // Cambiar estado de tarea
                system("cls"); {
                    if (tareas.empty()) {
                        cout << BRIGHT_RED << "No hay tareas para cambiar estado" << RESET << endl;
                        cout << "\nPresione Enter para continuar...";
                        cin.ignore();
                        cin.get();
                        break;
                    }

                    mostrarTareas();
                    int indiceTarea;
                    char estado;

                    cout << "\nNumero de tarea: ";

                    // Validar que la entrada sea un número
                    if (!(cin >> indiceTarea)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << BRIGHT_RED << "\nError: Debe ingresar un numero valido" << RESET << endl;
                        cout << "\nPresione Enter para continuar...";
                        cin.get();
                        break;
                    }

                    // Validar que el índice esté en rango
                    if (indiceTarea < 1 || indiceTarea > tareas.size()) {
                        cout << BRIGHT_RED << "\nError: La tarea #" << indiceTarea << " no existe" << RESET << endl;
                        cout << BRIGHT_RED << "Debe ingresar un numero entre 1 y " << tareas.size() << RESET << endl;
                        cout << "\nPresione Enter para continuar...";
                        cin.ignore();
                        cin.get();
                    }
                    else {
                        bool estadoValido = false;

                        while (!estadoValido) {
                            cout << "Marcar como completada? (s/n): ";
                            cin >> estado;

                            // Validar que solo sea 's', 'S', 'n' o 'N'
                            if (estado == 's' || estado == 'S' || estado == 'n' || estado == 'N') {
                                tareas[indiceTarea - 1]->setEstado(estado == 's' || estado == 'S');
                                cout << BRIGHT_GREEN << "Estado actualizado" << RESET << endl;
                                estadoValido = true;
                            }
                            else {
                                cout << BRIGHT_RED << "\nError: Debe ingresar 's' para Si o 'n' para No" << RESET << endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        }

                        cout << "\nPresione Enter para continuar...";
                        cin.ignore();
                        cin.get();
                    }
                    break;
                }
            case 5:  // Mostrar tareas
                system("cls");
                mostrarTareas();
                cout << "\nPresione Enter para continuar...";
                cin.ignore();
                cin.get();
                break;
            case 0:  // Volver
                system("cls");
                break;
            default:
                cout << "Opcion invalida" << endl;
            }
        } while (opcion != 0);
    }

    // ===== MÉTODOS JSON =====

    // Convierte el tablero a formato JSON
    json toJson() {
        json j;
        j["id"] = IdTablero;
        j["nombre"] = NombreTablero;
        j["fecha_creacion"] = FechaCreacion;
        j["prioridad"] = Prioridad;

        // Convierte todas las tareas a JSON
        json tareasJson = json::array();
        for (auto tarea : tareas) {
            tareasJson.push_back(tarea->toJson());
        }
        j["tareas"] = tareasJson;

        return j;
    }

    // Crea un tablero desde JSON
    static Tablero* fromJson(const json& j) {
        Tablero* tablero = new Tablero(
            j["id"].get<int>(),
            j["nombre"].get<string>(),
            j["fecha_creacion"].get<string>()
        );

        tablero->setPrioridad(j["prioridad"].get<bool>());

        // Carga todas las tareas
        if (j.contains("tareas")) {
            for (const auto& tareaJson : j["tareas"]) {
                Tarea* tarea = Tarea::fromJson(tareaJson);
                tablero->agregarTarea(tarea);
            }
        }

        return tablero;
    }
};

#endif