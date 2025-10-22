#define USUARIO_H
#define USUARIO_H
#include <string>
using namespace std;
class Usuario {
private:
	int id;
	string nombre;
	string email;
public:
	Usuario(int id, const string& nombre, const string& email);
	int getId() const;
	const string& getNombre() const;
	const string& getEmail() const;
	void setNombre(const string& nuevoNombre);
	void setEmail(const string& nuevoEmail);
	void imprimir() const;
};