// Guard para evitar inclusión múltiple
#ifndef CONTENEDORUSUARIO_H
#define CONTENEDORUSUARIO_H

// Colores para la consola
#define BRIGHT_RED     "\033[91m"
#define BRIGHT_GREEN   "\033[92m"
#define BRIGHT_BLUE    "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN    "\033[96m"
#define RESET "\033[0m"

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
                cout << BRIGHT_BLUE << "Datos cargados desde " << archivoJson << RESET << endl;
            }
        }
        catch (json::parse_error& e) {
            // Si hay error al parsear, ignora y continúa
            cout << BRIGHT_RED << "Error al cargar datos: " << e.what() << RESET << endl;
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
            cout << BRIGHT_RED << "Error al guardar datos" << RESET << endl;
        }
    }

    // ===== MÉTODOS DE VALIDACIÓN =====

    // Valida que una cadena no esté vacía y no contenga símbolos
    bool validarTexto(const string& texto) {
        // Verifica que no esté vacío
        if (texto.empty() || texto.find_first_not_of(' ') == string::npos) {
            return false;
        }

        // Verifica que solo contenga letras, números y espacios
        for (char c : texto) {
            if (!isalnum(c) && c != ' ') {
                return false;
            }
        }
        return true;
    }

    // Valida formato de correo
    bool validarCorreo(const string& correo) {
        // Verifica que no esté vacío
        if (correo.empty()) {
            return false;
        }

        // Verifica que contenga @ y tenga contenido antes y después
        size_t posArroba = correo.find('@');
        if (posArroba == string::npos || posArroba == 0 || posArroba == correo.length() - 1) {
            return false;
        }

        // Verifica que tenga un punto después del @
        size_t posPunto = correo.find('.', posArroba);
        if (posPunto == string::npos || posPunto == correo.length() - 1) {
            return false;
        }

        return true;
    }

    // Verifica si un ID ya existe en el sistema
    bool idExiste(int id) {
        for (auto usuario : usuarios) {
            if (usuario->getId() == id) {
                return true;
            }
        }
        return false;
    }

    // Valida y obtiene un ID correcto del usuario
    int obtenerIdValido(string mensaje, bool validarExistencia = true) {
        int id;
        bool idValido = false;

        while (!idValido) {
            cout << mensaje;

            // Verifica que la entrada sea un número
            if (!(cin >> id)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << BRIGHT_RED << "\nError:" << RESET << " Debe ingresar un numero entero" << endl;
                cout << BRIGHT_CYAN << "Presione Enter para intentar de nuevo..." << RESET;
                cin.get();
                cout << endl;
                continue;
            }

            // Verifica que no sea negativo
            if (id < 0) {
                cout << BRIGHT_RED << "\nError:"<< RESET <<"El ID no puede ser negativo" << endl;
                cout << "Presione Enter para intentar de nuevo...";
                cin.ignore();
                cin.get();
                cout << endl;
                continue;
            }

            // Verifica si el ID debe existir o no existir
            if (validarExistencia) {
                if (!idExiste(id)) {
                    cout << "\nError: El ID " << id << " no existe" << endl;
                    cout << "Presione Enter para intentar de nuevo...";
                    cin.ignore();
                    cin.get();
                    cout << endl;
                    continue;
                }
            }
            else {
                if (idExiste(id)) {
                    cout << "\nError: El ID " << id << " ya esta en uso" << endl;
                    cout << "Presione Enter para intentar de nuevo...";
                    cin.ignore();
                    cin.get();
                    cout << endl;
                    continue;
                }
            }

            idValido = true;
        }

        return id;
    }

    // Obtiene un nombre válido
    string obtenerNombreValido() {
        string nombre;
        bool nombreValido = false;

        while (!nombreValido) {
            cout << "Nombre: ";
            getline(cin, nombre);

            if (!validarTexto(nombre)) {
                cout << "\nError: El nombre no puede estar vacio ni contener simbolos especiales" << endl;
                cout << "Presione Enter para intentar de nuevo...";
                cin.get();
                cout << endl;
                continue;
            }

            nombreValido = true;
        }

        return nombre;
    }

    // Obtiene un correo válido
    string obtenerCorreoValido() {
        string correo;
        bool correoValido = false;

        while (!correoValido) {
            cout << "Correo: ";
            getline(cin, correo);

            if (correo.empty()) {
                cout << "\nError: El correo no puede estar vacio" << endl;
                cout << "Presione Enter para intentar de nuevo...";
                cin.get();
                cout << endl;
                continue;
            }

            if (!validarCorreo(correo)) {
                cout << "\nError: Formato de correo invalido (debe contener @ y un dominio)" << endl;
                cout << "Presione Enter para intentar de nuevo...";
                cin.get();
                cout << endl;
                continue;
            }

            correoValido = true;
        }

        return correo;
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

    // Getter: obtiene el vector de usuarios
    vector<Usuario*>& getUsuarios() {
        return usuarios;
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
                    int id;
                    string nombre, correo;

                    cout << "\n--- CREAR NUEVO USUARIO ---" << endl;

                    // Obtener ID válido (no existente)
                    id = obtenerIdValido("ID del usuario: ", false);
                    cin.ignore();

                    // Obtener nombre válido
                    nombre = obtenerNombreValido();

                    // Obtener correo válido
                    correo = obtenerCorreoValido();

                    // Crear usuario con datos validados
                    Usuario* nuevoUsuario = new Usuario(id, nombre, correo);
                    AnadirUsuario(nuevoUsuario);
                    cout << "\nPresione Enter para continuar...";
                    cin.get();
                    break;
                }
            case 2:  // Eliminar usuario
                system("cls"); {
                    if (usuarios.empty()) {
                        cout << "No hay usuarios para eliminar" << endl;
                        cout << "\nPresione Enter para continuar...";
                        cin.ignore();
                        cin.get();
                        break;
                    }
                    MostrarDatos();
                    cout << endl;
                    int id = obtenerIdValido("ID del usuario a eliminar: ", true);
                    EliminarUsuario(id);
                    cout << "\nPresione Enter para volver al menu de usuarios...";
                    cin.ignore();
                    cin.get();
                    break;
                }
            case 3:  // Actualizar usuario
                system("cls"); {
                    if (usuarios.empty()) {
                        cout << "No hay usuarios para actualizar" << endl;
                        cout << "\nPresione Enter para continuar...";
                        cin.ignore();
                        cin.get();
                        break;
                    }
                    MostrarDatos();
                    cout << endl;

                    int id = obtenerIdValido("ID del usuario a actualizar: ", true);
                    cin.ignore();

                    string nombre, correo;

                    // Obtener nombre válido
                    nombre = obtenerNombreValido();

                    // Obtener correo válido
                    correo = obtenerCorreoValido();

                    ActualizarUsuario(id, nombre, correo);
                    cout << "\nPresione Enter para continuar...";
                    cin.get();
                    break;
                }
            case 4:  // Mostrar usuarios
                system("cls");
                MostrarDatos();
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
};

#endif