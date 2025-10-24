#pragma once
#ifndef USUARIO_H
#define USUARIO_H
// hola
#include <string>

class Usuario {
private:
    int id;
    std::string nombre;
    std::string email;

public:
    Usuario(int id, const std::string& nombre, const std::string& email);

    int getId() const;
    const std::string& getNombre() const;
    const std::string& getEmail() const;

    void setNombre(const std::string& nuevoNombre);
    void setEmail(const std::string& nuevoEmail);

    void imprimir() const;
};

#endif