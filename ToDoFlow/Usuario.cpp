#include "Usuario.h"
#include <iostream>

Usuario::Usuario(int id, const std::string& nombre, const std::string& email)
    : id(id), nombre(nombre), email(email) {
}

int Usuario::getId() const { return id; }
const std::string& Usuario::getNombre() const { return nombre; }
const std::string& Usuario::getEmail() const { return email; }

void Usuario::setNombre(const std::string& nuevoNombre) { nombre = nuevoNombre; }
void Usuario::setEmail(const std::string& nuevoEmail) { email = nuevoEmail; }

void Usuario::imprimir() const {
    std::cout << "[" << id << "] " << nombre << " <" << email << ">\n";
}