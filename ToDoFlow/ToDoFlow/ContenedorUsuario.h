// Guard para evitar inclusión múltiple
#ifndef CONTENEDORUSUARIO_H
#define CONTENEDORUSUARIO_H

#include "Librerias.h"
#include "Usuario.h"

// Clase que gestiona una colección de usuarios
class ContenedorUsuario {
private:
    vector<Usuario*> usuarios;  // Vector que almacena punteros a usuarios
    string archivoJson;         // Nombre del archivo JSON para persistencia

    // ===== MÉTODOS PRIVADOS JSON =====

    // Carga usuarios desde archivo JSON
    void cargarDesdeJson() {
        ifstream archivo(archivoJson);

        // Si el archivo no existe o está vacío, no hace nada
        if (!archivo.is_open()) {
            return;
        }

        try {
            json datos;
            archivo >> datos;  // Lee el contenido JSON
            archivo.close();

            // Verifica que exista el campo "usuarios"
            if (datos.contains("usuarios")) {
                // Recorre cada usuario en el JSON
                for (const auto& usuarioJson : datos["usuarios"]) {
                    Usuario* usuario = Usuario::fromJson(usuarioJson);
                    usuarios.push_back(usuario);
                }
                cout << "Datos cargados desde " << archivoJson << endl;
            }
        }
        catch (json::parse_error& e) {
            // Si hay error al parsear, ignora y continúa
            cout << "Error al cargar datos: " << e.what() << endl;
        }
    }

    // Guarda usuarios en archivo JSON
    void guardarEnJson() {
        json datos;
        datos["sistema"] = "Gestion de Tareas";
        datos["version"] = "1.0";

        // Convierte todos los usuarios a JSON
        json usuariosJson = json::array();
        for (auto usuario : usuarios) {
            usuariosJson.push_back(usuario->toJson());
        }
        datos["usuarios"] = usuariosJson;

        // Escribe en el archivo
        ofstream archivo(archivoJson);
        if (archivo.is_open()) {
            archivo << datos.dump(4);  // dump(4) = formato legible con indentación
            archivo.close();
        }
        else {
            cout << "Error al guardar datos" << endl;
        }
    }

public:
    // Constructor: inicializa el contenedor y carga datos si existen
    ContenedorUsuario(string archivo = "usuarios.json") : archivoJson(archivo) {
        cout << "Contenedor de usuarios creado" << endl;
        cargarDesdeJson();  // Intenta cargar datos existentes
    }

    // Destructor: libera memoria de todos los usuarios y guarda antes de salir
    ~ContenedorUsuario() {
        guardarEnJson();  // Guarda antes de destruir

        // Libera memoria de cada usuario
        for (auto usuario : usuarios) {
            delete usuario;
        }
        usuarios.clear();
    }

    // Agrega un usuario al contenedor
    void AnadirUsuario(Usuario* usuario) {
        usuarios.push_back(usuario);
        cout << "Usuario anadido exitosamente" << endl;
        guardarEnJson();  // Guarda automáticamente
    }

    // Elimina un usuario por su ID
    void EliminarUsuario(int id) {
        // Recorre el vector buscando el usuario
        for (int i = 0; i < usuarios.size(); i++) {
            if (usuarios[i]->getId() == id) {
                delete usuarios[i];  // Libera memoria
                usuarios.erase(usuarios.begin() + i);  // Elimina del vector
                cout << "Usuario eliminado exitosamente" << endl;
                guardarEnJson();  // Guarda automáticamente
                return;
            }
        }
        cout << "Usuario no encontrado" << endl;
    }

    // Actualiza los datos de un usuario existente
    void ActualizarUsuario(int id, string nombre, string correo) {
        // Busca el usuario por ID
        for (auto usuario : usuarios) {
            if (usuario->getId() == id) {
                usuario->setNombre(nombre);
                usuario->setCorreo(correo);
                cout << "Usuario actualizado exitosamente" << endl;
                guardarEnJson();  // Guarda automáticamente
                return;
            }
        }
        cout << "Usuario no encontrado" << endl;
    }

    // Muestra todos los usuarios registrados
    void MostrarDatos() {
        cout << "\n=== Lista de Usuarios ===" << endl;
        if (usuarios.empty()) {
            cout << "No hay usuarios registrados" << endl;
            return;
        }
        // Muestra cada usuario con su número
        for (int i = 0; i < usuarios.size(); i++) {
            cout << "\nUsuario " << (i + 1) << ":" << endl;
            usuarios[i]->mostrarInfo();
        }
    }

    // Busca un usuario por ID y lo retorna (o nullptr si no existe)
    Usuario* buscarUsuario(int id) {
        for (auto usuario : usuarios) {
            if (usuario->getId() == id) {
                return usuario;
            }
        }
        return nullptr;  // Retorna puntero nulo si no lo encuentra
    }

    // Exporta datos a un archivo JSON específico
    void exportarJson(string nombreArchivo) {
        json datos;
        datos["sistema"] = "Gestion de Tareas";
        datos["version"] = "1.0";
        datos["fecha_exportacion"] = __DATE__;  // Fecha de compilación

        json usuariosJson = json::array();
        for (auto usuario : usuarios) {
            usuariosJson.push_back(usuario->toJson());
        }
        datos["usuarios"] = usuariosJson;

        ofstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            archivo << datos.dump(4);
            archivo.close();
            cout << "Datos exportados a " << nombreArchivo << endl;
        }
        else {
            cout << "Error al exportar datos" << endl;
        }
    }

    // Importa datos desde un archivo JSON específico
    void importarJson(string nombreArchivo) {
        ifstream archivo(nombreArchivo);

        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
            return;
        }

        try {
            json datos;
            archivo >> datos;
            archivo.close();

            if (datos.contains("usuarios")) {
                // Pregunta si quiere reemplazar o agregar
                char opcion;
                cout << "Reemplazar usuarios existentes? (s/n): ";
                cin >> opcion;

                if (opcion == 's' || opcion == 'S') {
                    // Limpia usuarios actuales
                    for (auto usuario : usuarios) {
                        delete usuario;
                    }
                    usuarios.clear();
                }

                // Carga usuarios del archivo
                for (const auto& usuarioJson : datos["usuarios"]) {
                    Usuario* usuario = Usuario::fromJson(usuarioJson);
                    usuarios.push_back(usuario);
                }

                cout << "Datos importados desde " << nombreArchivo << endl;
                guardarEnJson();  // Guarda en el archivo principal
            }
        }
        catch (json::parse_error& e) {
            cout << "Error al importar: " << e.what() << endl;
        }
    }

    // Elimina el archivo JSON (resetea datos)
    void eliminarArchivoJson() {
        if (remove(archivoJson.c_str()) == 0) {
            cout << "Archivo " << archivoJson << " eliminado exitosamente" << endl;

            // Limpia usuarios en memoria
            for (auto usuario : usuarios) {
                delete usuario;
            }
            usuarios.clear();
        }
        else {
            cout << "No se pudo eliminar el archivo" << endl;
        }
    }

    // Menú interactivo para gestionar usuarios
    void menuUsuarios() {
        int opcion;

        do {
            system("cls");
            cout << "\n--- MENU USUARIOS ---" << endl;
            cout << "1. Agregar Usuario" << endl;
            cout << "2. Eliminar Usuario" << endl;
            cout << "3. Actualizar Usuario" << endl;
            cout << "4. Mostrar Usuarios" << endl;
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
            case 1:  // Agregar usuario
                system("cls"); {
                    Usuario* nuevoUsuario = Usuario::menuCrearUsuario();
                    AnadirUsuario(nuevoUsuario);
                    break;
                }
            case 2:  // Eliminar usuario
                system("cls"); {
                    int id;
                    cout << "ID del usuario a eliminar: ";
                    cin >> id;
                    EliminarUsuario(id);
                    break;
                }
            case 3:  // Actualizar usuario
                system("cls"); {
                    int id;
                    string nombre, correo;

                    cout << "ID del usuario a actualizar: ";
                    cin >> id;
                    cin.ignore();

                    cout << "Nuevo nombre: ";
                    getline(cin, nombre);

                    cout << "Nuevo correo: ";
                    getline(cin, correo);

                    ActualizarUsuario(id, nombre, correo);
                    break;
                }
            case 4:  // Mostrar usuarios
                system("cls");
                MostrarDatos();
                break;
            case 0:  // Volver
                system("cls");
                break;
            default:
                cout << "Opcion invalida" << endl;
            }
        } while (opcion != 0);
    }
};

#endif
