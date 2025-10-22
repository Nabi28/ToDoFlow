#include "Usuario.h"
#include <iostream>
using namespace std;
Usuario::Usuario(int id, const string& nombre, const string& email)
	: id(id), nombre(nombre), email(email) {
}
int Usuario::getId() const { return id; }
const string& Usuario::getNombre() const { return nombre; }
const string& Usuario::getEmail() const { return email; }
void Usuario::setNombre(const string& nuevoNombre) { nombre = nuevoNombre; }
void Usuario::setEmail(const string& nuevoEmail) { email = nuevoEmail; }
void Usuario::imprimir() const {
	std::cout << "[" << id << "] " << nombre << " <" << email << ">\n";
}