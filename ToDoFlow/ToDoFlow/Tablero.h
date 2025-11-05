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

    // Método estático para crear un tablero mediante menú interactivo
    static Tablero* menuCrearTablero() {
        int id;
        string nombre, fecha;

        cout << "\n--- CREAR NUEVO TABLERO ---" << endl;
        cout << "ID del tablero: ";
        cin >> id;
        cin.ignore();

        cout << "Nombre del tablero: ";
        getline(cin, nombre);

        cout << "Fecha de creacion (YYYY-MM-DD): ";
        getline(cin, fecha);

        return new Tablero(id, nombre, fecha);
    }

    // Menú interactivo para gestionar las tareas del tablero
    void menuTareas() {
        int opcion;

        do {
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
                    Tarea* nuevaTarea = Tarea::menuCrearTarea();
                    agregarTarea(nuevaTarea);
                    nuevaTarea->CrearTarea();
                    break;
                }
            case 2:  // Eliminar tarea
                system("cls"); {
                    mostrarTareas();
                    if (!tareas.empty()) {
                        int indiceTarea;
                        cout << "\nNumero de tarea a eliminar: ";
                        cin >> indiceTarea;
                        eliminarTarea(indiceTarea - 1);  // -1 porque el índice empieza en 0
                    }
                    break;
                }
            case 3:  // Actualizar tarea (en desarrollo)
                system("cls"); {
                    mostrarTareas();
                    if (!tareas.empty()) {
                        int indiceTarea;
                        string titulo, descripcion, fecha;

                        cout << "\nNumero de tarea a actualizar: ";
                        cin >> indiceTarea;
                        cin.ignore();

                        if (indiceTarea > 0 && indiceTarea <= tareas.size()) {
                            cout << "Nuevo titulo: ";
                            getline(cin, titulo);
                            cout << "Nueva descripcion: ";
                            getline(cin, descripcion);
                            cout << "Nueva fecha (YYYY-MM-DD): ";
                            getline(cin, fecha);

                            tareas[indiceTarea - 1]->ActualizarTarea(titulo, descripcion, fecha);
                        }
                    }
                    break;
                }
            case 4:  // Cambiar estado de tarea
                system("cls"); {
                    mostrarTareas();
                    if (!tareas.empty()) {
                        int indiceTarea;
                        char estado;
                        cout << "\nNumero de tarea: ";
                        cin >> indiceTarea;
                        if (indiceTarea > 0 && indiceTarea <= tareas.size()) {
                            cout << "Marcar como completada? (s/n): ";
                            cin >> estado;
                            tareas[indiceTarea - 1]->setEstado(estado == 's' || estado == 'S');
                            cout << "Estado actualizado" << endl;
                        }
                    }
                    break;
                }
            case 5:  // Mostrar tareas
                system("cls");
                mostrarTareas();
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