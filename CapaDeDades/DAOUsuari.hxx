#include <string>
#include <vector>
#include <memory>
#include "../CapaDeDomini/Model/Usuari.hxx"

class DAOUsuari {
public:
	// Operacions sobre usuari
	bool existeix(const std::string& username);
	shared_ptr<usuari> obte(const std::string& username);
	std::vector<usuari> tots();
	void inserta(const usuari& u);
	void modifica(const usuari& u);
	void esborra(const std::string& username);
};