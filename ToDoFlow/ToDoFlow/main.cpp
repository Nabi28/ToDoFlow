#include "Librerias.h"
#include "Usuario.h"
#include "ContenedorUsuario.h"
#include "Tarea.h"
#include "Tablero.h"


#define BRIGHT_RED     "\033[91m"
#define BRIGHT_GREEN   "\033[92m"
#define BRIGHT_BLUE    "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN    "\033[96m"
#define RESET "\033[0m"


//  CLASE PARA GESTIONAR LOS TABLEROS CON JSON
class GestorTableros {
private:
    vector<Tablero*> tableros;  // Vector de tableros
    string archivoJson;         // Archivo para persistencia

    // Carga tableros desde JSON
    void cargarDesdeJson() {
        ifstream archivo(archivoJson);

        if (!archivo.is_open()) {
            return;
        }

        try {
            json datos;
            archivo >> datos;
            archivo.close();

            // Verifica que existan tableros en el JSON
            if (datos.contains("tableros")) {
                for (const auto& tableroJson : datos["tableros"]) {
                    Tablero* tablero = Tablero::fromJson(tableroJson);
                    tableros.push_back(tablero);
                }
                cout << "Tableros cargados desde " << archivoJson << endl;
            }
        }
        catch (json::parse_error& e) {
            cout << "Error al cargar tableros: " << e.what() << endl;
        }
    }

    // Guarda tableros en JSON
    void guardarEnJson() {
        json datos;
        datos["sistema"] = "Gestion de Tareas";
        datos["version"] = "1.0";

        // Convierte todos los tableros a JSON
        json tablerosJson = json::array();
        for (auto tablero : tableros) {
            tablerosJson.push_back(tablero->toJson());
        }
        datos["tableros"] = tablerosJson;

        // Escribe en el archivo
        ofstream archivo(archivoJson);
        if (archivo.is_open()) {
            archivo << datos.dump(4);
            archivo.close();
        }
    }

public:
    // Constructor: carga tableros existentes
    GestorTableros(string archivo = "tableros.json") : archivoJson(archivo) {
        cargarDesdeJson();
    }

    // Destructor: guarda y limpia memoria
    ~GestorTableros() {
        guardarEnJson();
        for (auto tablero : tableros) {
            delete tablero;
        }
        tableros.clear();
    }

    // Obtiene el vector de tableros
    vector<Tablero*>& getTableros() {
        return tableros;
    }

    // Agrega un tablero
    void agregarTablero(Tablero* tablero) {
        tableros.push_back(tablero);
        guardarEnJson();  // Guarda automáticamente
    }

    // Elimina un tablero por índice
    void eliminarTablero(int index) {
        if (index >= 0 && index < tableros.size()) {
            delete tableros[index];
            tableros.erase(tableros.begin() + index);
            guardarEnJson();  // Guarda automáticamente
        }
    }

    // Guarda manualmente (para actualizaciones)
    void guardar() {
        guardarEnJson();
    }

    // Exporta tableros a archivo específico
    void exportarJson(string nombreArchivo) {
        json datos;
        datos["sistema"] = "Gestion de Tareas";
        datos["version"] = "1.0";

        json tablerosJson = json::array();
        for (auto tablero : tableros) {
            tablerosJson.push_back(tablero->toJson());
        }
        datos["tableros"] = tablerosJson;

        ofstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            archivo << datos.dump(4);
            archivo.close();
            cout << "Tableros exportados a " << nombreArchivo << endl;
        }
    }

    // Importa tableros desde archivo específico
    void importarJson(string nombreArchivo) {
        ifstream archivo(nombreArchivo);

        if (!archivo.is_open()) {
            cout << "No se pudo abrir " << nombreArchivo << endl;
            return;
        }

        try {
            json datos;
            archivo >> datos;
            archivo.close();

            if (datos.contains("tableros")) {
                char opcion;
                cout << "Reemplazar tableros existentes? (s/n): ";
                cin >> opcion;

                if (opcion == 's' || opcion == 'S') {
                    for (auto tablero : tableros) {
                        delete tablero;
                    }
                    tableros.clear();
                }

                for (const auto& tableroJson : datos["tableros"]) {
                    Tablero* tablero = Tablero::fromJson(tableroJson);
                    tableros.push_back(tablero);
                }

                cout << "Tableros importados desde " << nombreArchivo << endl;
                guardarEnJson();
            }
        }
        catch (json::parse_error& e) {
            cout << BRIGHT_RED << "Error al importar: " << e.what() << RESET << endl;
        }
    }

    // Elimina el archivo JSON
    void eliminarArchivoJson() {
        if (remove(archivoJson.c_str()) == 0) {
            cout << BRIGHT_GREEN << "Archivo eliminado exitosamente" << RESET << endl;
            for (auto tablero : tableros) {
                delete tablero;
            }
            tableros.clear();
        }
    }
};


int main() {
    // Crea el contenedor de usuarios (carga automáticamente desde usuarios.json)
    ContenedorUsuario* contenedorUsuarios = new ContenedorUsuario();

    // Crea el gestor de tableros (carga automáticamente desde tableros.json)
    GestorTableros* gestorTableros = new GestorTableros();

    // Referencia al vector de tableros para facilitar acceso
    vector<Tablero*>& tableros = gestorTableros->getTableros();

    int opcion;  // Variable para almacenar la opción del menú


    do {
        //  El menú principal
        cout << BRIGHT_BLUE << "\n========================================" << RESET << endl;
        cout << BRIGHT_MAGENTA << "  SISTEMA DE GESTION DE TAREAS" << RESET << endl;
        cout << BRIGHT_BLUE << "========================================" << RESET << endl;
        cout << "1. Gestionar Usuarios" << endl;
        cout << "2. Gestionar Tableros" << endl;
        cout << "3. Mostrar Todo" << endl;
        cout << "4. Exportar Datos" << endl;
        cout << "5. Importar Datos" << endl;
        cout << "6. Eliminar Archivos JSON" << endl;
        cout << "0. Salir" << endl;
        cout << BRIGHT_BLUE << "========================================" << RESET << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        // Validación: si la entrada no es un número
        if (cin.fail()) {
            cin.clear();  // Limpia el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Limpia buffer
            cout << BRIGHT_RED << "Opcion invalida. Intente nuevamente." << endl;
            continue;  // Vuelve al inicio del bucle
        }

        switch (opcion) {
        case 1:  // Gestionar Usuarios
            system("cls");
            contenedorUsuarios->menuUsuarios();
            break;

        case 2:  // Gestionar Tableros
            system("cls"); {
                int opcionTablero;

                // Submenú de tableros
                do {
                    cout << BRIGHT_MAGENTA << "\n--- MENU TABLEROS ---" << RESET << endl;
                    cout << "1. Crear Tablero" << endl;
                    cout << "2. Eliminar Tablero" << endl;
                    cout << "3. Modificar Tablero" << endl;
                    cout << "4. Mostrar Tableros" << endl;
                    cout << "5. Cambiar Prioridad" << endl;
                    cout << "6. Gestionar Tareas de un Tablero" << endl;
                    cout << "0. Volver" << endl;
                    cout << "Opcion: ";
                    cin >> opcionTablero;

                    // Validación de entrada
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << BRIGHT_RED << "Opcion invalida" << RESET << endl;
                        continue;
                    }

                    switch (opcionTablero) {
                    case 1:  // Crear tablero
                        system("cls"); {
                            Tablero* nuevoTablero = Tablero::menuCrearTablero();
                            gestorTableros->agregarTablero(nuevoTablero);
                            nuevoTablero->CrearTablero();
                            break;
                        }
                    case 2:  // Eliminar tablero
                        system("cls"); {
                            int id;
                            cout << BRIGHT_RED << "ID del tablero a eliminar: " << RESET;
                            cin >> id;

                            // Busca el tablero por ID
                            for (int i = 0; i < tableros.size(); i++) {
                                if (tableros[i]->getIdTablero() == id) {
                                    gestorTableros->eliminarTablero(i);
                                    cout << BRIGHT_GREEN << "Tablero eliminado exitosamente" << RESET << endl;
                                    break;
                                }
                            }
                            break;
                        }
                    case 3:  // Modificar tablero
                        system("cls"); {
                            int id;
                            string nuevoNombre;
                            cout << BRIGHT_GREEN << "ID del tablero a modificar: " RESET;
                            cin >> id;
                            cin.ignore();

                            // Busca y modifica el tablero
                            for (auto tablero : tableros) {
                                if (tablero->getIdTablero() == id) {
                                    cout << "Nuevo nombre: ";
                                    getline(cin, nuevoNombre);
                                    tablero->ModificarTablero(nuevoNombre);
                                    gestorTableros->guardar();  // Guarda automáticamente
                                    break;
                                }
                            }
                            break;
                        }
                    case 4:  // Mostrar tableros
                        system("cls"); {
                            cout << BRIGHT_MAGENTA << "\n=== Lista de Tableros ===" << RESET << endl;
                            if (tableros.empty()) {
                                cout << BRIGHT_RED << "No hay tableros creados" << RESET << endl;
                            }
                            else {
                                // Muestra cada tablero
                                for (int i = 0; i < tableros.size(); i++) {
                                    cout << "\nTablero " << (i + 1) << ":" << endl;
                                    tableros[i]->mostrarInfo();
                                }
                            }
                            break;
                        }
                    case 5:  // Cambiar prioridad
                        system("cls"); {
                            int id;
                            char opcionPrioridad;
                            cout << "ID del tablero: ";
                            cin >> id;

                            // Busca y cambia prioridad
                            for (auto tablero : tableros) {
                                if (tablero->getIdTablero() == id) {
                                    cout << "Establecer prioridad? (s/n): ";
                                    cin >> opcionPrioridad;
                                    tablero->setPrioridad(opcionPrioridad == 's' || opcionPrioridad == 'S');
                                    cout << "Prioridad actualizada" << endl;
                                    gestorTableros->guardar();  // Guarda automáticamente
                                    break;
                                }
                            }
                            break;
                        }
                    case 6:  // Gestionar tareas de un tablero
                        system("cls"); {
                            int id;
                            cout << "ID del tablero: ";
                            cin >> id;

                            // Busca el tablero y abre su menú de tareas
                            for (auto tablero : tableros) {
                                if (tablero->getIdTablero() == id) {
                                    tablero->menuTareas();
                                    gestorTableros->guardar();  // Guarda automáticamente después
                                    break;
                                }
                            }
                            break;
                        }
                    case 0:  // Volver
                        break;
                    default:
                        cout << BRIGHT_RED << "Opcion invalida" << RESET << endl;
                    }
                } while (opcionTablero != 0);
                break;
            }

        case 3:  // Mostrar todo
            system("cls");
            // Muestra usuarios
            contenedorUsuarios->MostrarDatos();

            // Muestra tableros
            cout << BRIGHT_MAGENTA << "\n=== Lista de Tableros ===" << RESET << endl;
            if (tableros.empty()) {
                cout << BRIGHT_RED << "No hay tableros creados" << RESET << endl;
            }
            else {
                for (int i = 0; i < tableros.size(); i++) {
                    cout << "\nTablero " << (i + 1) << ":" << endl;
                    tableros[i]->mostrarInfo();
                }
            }

            // Pausa para que el usuario pueda leer
            cout << BRIGHT_CYAN << "\nPresione Enter para volver al menu..." << RESET;
            cin.ignore();
            cin.get();
            system("cls");
            break;

        case 4:  // Exportar datos
            system("cls"); {
                int tipoExportar;
                string nombreArchivo;

                cout << BRIGHT_MAGENTA << "\n--- EXPORTAR DATOS ---" << RESET << endl;
                cout << "1. Exportar Usuarios" << endl;
                cout << "2. Exportar Tableros" << endl;
                cout << "3. Exportar Todo" << endl;
                cout << "0. Volver" << endl;
                cout << "Opcion: ";
                cin >> tipoExportar;
                cin.ignore();

                switch (tipoExportar) {
                case 1:  // Exportar usuarios
                    cout << "Nombre del archivo: ";
                    getline(cin, nombreArchivo);
                    contenedorUsuarios->exportarJson(nombreArchivo);
                    cout <<  BRIGHT_CYAN << "\nPresione Enter para continuar..." << RESET;
                    cin.get();
                    break;
                case 2:  // Exportar tableros
                    cout << "Nombre del archivo: ";
                    getline(cin, nombreArchivo);
                    gestorTableros->exportarJson(nombreArchivo);
                    cout << BRIGHT_CYAN << "\nPresione Enter para continuar..." RESET;
                    cin.get();
                    break;
                case 3:  // Exportar todo
                    cout << "Nombre base para archivos: ";
                    getline(cin, nombreArchivo);
                    contenedorUsuarios->exportarJson(nombreArchivo + "_usuarios.json");
                    gestorTableros->exportarJson(nombreArchivo + "_tableros.json");
                    cout << "Datos exportados exitosamente" << endl;
                    cout << BRIGHT_CYAN << "\nPresione Enter para continuar..." RESET;
                    cin.get();
                    break;
                case 0:  // Volver
                    break;
                default:
                    cout << BRIGHT_RED << "Opcion invalida" << RESET << endl;
                }

                system("cls");
                break;
            }

        case 5:  // Importar datos
            system("cls"); {
                int tipoImportar;
                string nombreArchivo;

                cout << BRIGHT_MAGENTA <<"\n--- IMPORTAR DATOS ---" << RESET << endl;
                cout << "1. Importar Usuarios" << endl;
                cout << "2. Importar Tableros" << endl;
                cout << "0. Volver" << endl;
                cout << "Opcion: ";
                cin >> tipoImportar;
                cin.ignore();

                switch (tipoImportar) {
                case 1:  // Importar usuarios
                    cout << "Nombre del archivo: ";
                    getline(cin, nombreArchivo);
                    contenedorUsuarios->importarJson(nombreArchivo);
                    cout << BRIGHT_CYAN << "\nPresione Enter para continuar..." << RESET;
                    cin.get();
                    break;
                case 2:  // Importar tableros
                    cout << "Nombre del archivo: ";
                    getline(cin, nombreArchivo);
                    gestorTableros->importarJson(nombreArchivo);
                    cout << BRIGHT_CYAN << "\nPresione Enter para continuar..." << RESET;
                    cin.get();
                    break;
                case 0:  // Volver
                    break;
                default:
                    cout << BRIGHT_RED << "Opcion invalida" << RESET << endl;
                }

                system("cls");
                break;
            }

        case 6:  // Eliminar archivos JSON
            system("cls"); {
                char confirmacion;
                cout << BRIGHT_RED << "ADVERTENCIA:" << RESET << "Se eliminaran TODOS los archivos JSON" << endl;
                cout << "Esta seguro? (s/n): ";
                cin >> confirmacion;

                if (confirmacion == 's' || confirmacion == 'S') {
                    contenedorUsuarios->eliminarArchivoJson();
                    gestorTableros->eliminarArchivoJson();
                    cout << BRIGHT_RED << "Archivos eliminados" << RESET << endl;
                }

                // Pausa para que el usuario pueda leer el resultado
                cout << BRIGHT_CYAN << "\nPresione Enter para volver al menu..."<< RESET;
                cin.ignore();
                cin.get();
                system("cls");
                break;
            }

        case 0:  // Salir
            cout <<  "\nSaliendo del sistema..." << endl;
            break;

        default:
            cout << BRIGHT_RED << "Opcion invalida" << RESET <<  endl;
        }
    } while (opcion != 0);  // Continúa hasta que el usuario elija salir

    // Limpieza de memoria antes de terminar el programa
    delete gestorTableros;  // Guarda automáticamente en el destructor
    delete contenedorUsuarios;  // Guarda automáticamente en el destructor

    return 0;  // Termina el programa exitosamente
}