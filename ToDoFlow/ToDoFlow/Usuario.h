// Guard para evitar inclusión múltiple
#ifndef USUARIO_H
#define USUARIO_H

#include "Librerias.h"

// colores para la consola
#define BRIGHT_RED     "\033[91m"
#define BRIGHT_GREEN   "\033[92m"
#define BRIGHT_BLUE    "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN    "\033[96m"
#define RESET "\033[0m"

// Clase que representa un usuario del sistema
class Usuario {
private:
    // Atributos privados del usuario
    int id;           // Identificador único del usuario
    string Nombre;    // Nombre completo del usuario
    string Correo;    // Correo electrónico del usuario

public:
    // Constructor: inicializa un usuario con id, nombre y correo
    Usuario(int id, string nombre, string correo) {
        this->id = id;
        this->Nombre = nombre;
        this->Correo = correo;
    }

    // Getter: obtiene el ID del usuario
    int getId() {
        return id;
    }

    // Getter: obtiene el nombre del usuario
    string getNombre() {
        return Nombre;
    }

    // Getter: obtiene el correo del usuario
    string getCorreo() {
        return Correo;
    }

    // Setter: modifica el ID del usuario
    void setId(int id) {
        this->id = id;
    }

    // Setter: modifica el nombre del usuario
    void setNombre(string nombre) {
        this->Nombre = nombre;
    }

    // Setter: modifica el correo del usuario
    void setCorreo(string correo) {
        this->Correo = correo;
    }

    // Método para mostrar la información del usuario
    void mostrarInfo() {
        cout << "ID: " << id << endl;
        cout << "Nombre: " << Nombre << endl;
        cout << "Correo: " << Correo << endl;
    }

    // Método estático para validar y obtener un ID válido
    static int obtenerIdValidoParaCreacion() {
        int id;
        bool idValido = false;

        while (!idValido) {
            cout << "ID del usuario: ";

            // Verifica que la entrada sea un número entero
            if (!(cin >> id)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << BRIGHT_RED <<  "\nError:"<< RESET << "Debe ingresar un numero entero" << endl;
                cout << BRIGHT_CYAN << "Presione Enter para intentar de nuevo..."<< RESET;
                cin.get();
                cout << endl;
                continue;
            }

            // Verifica que no sea negativo
            if (id < 0) {
                cout << BRIGHT_RED "\nError:" << RESET <<" El ID no puede ser negativo" << endl;
                cout << BRIGHT_CYAN << "Presione Enter para intentar de nuevo..." RESET;
                cin.ignore();
                cin.get();
                cout << endl;
                continue;
            }

            idValido = true;
        }

        return id;
    }

    // Método estático para crear un usuario mediante menú interactivo
    // Retorna un puntero al nuevo usuario creado
    static Usuario* menuCrearUsuario() {
        int id;
        string nombre, correo;

        cout << BRIGHT_MAGENTA << "\n--- CREAR NUEVO USUARIO ---" << RESET << endl;

        // Obtener ID con validación
        id = obtenerIdValidoParaCreacion();
        cin.ignore();  // Limpiar buffer

        cout << "Nombre: ";
        getline(cin, nombre);

        cout << "Correo: ";
        getline(cin, correo);

        // Crear y retornar puntero al nuevo usuario
        return new Usuario(id, nombre, correo);
    }

    // Método para convertir el usuario a formato JSON
    json toJson() {
        json j;
        j["id"] = id;
        j["nombre"] = Nombre;
        j["correo"] = Correo;
        return j;
    }

    // Método estático para crear un usuario desde JSON
    static Usuario* fromJson(const json& j) {
        return new Usuario(
            j["id"].get<int>(),
            j["nombre"].get<string>(),
            j["correo"].get<string>()
        );
    }
};

#endif