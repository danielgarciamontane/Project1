#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../CapaDeDomini/Model/Usuari.hxx"

class DAOUsuari {
public:

	// Obtiene un usuario por sobrenom
	shared_ptr<usuari> obte(const std::string& username);

    bool existeixSobrenom(const string& sobrenom) const;
	bool existeixCorreu(const string& correuElectronic) const;
	void crearUsuari(shared_ptr<usuari> u);

	std::vector<usuari> tots();
	void inserta(const usuari& u);
	static void modUsu(shared_ptr<usuari> u);
	void esbUsu(const std::string& username);
};