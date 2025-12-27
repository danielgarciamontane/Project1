#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../CapaDeDomini/Model/Usuari.hxx"

class DAOUsuari {
public:

	// Obtiene un usuario por sobrenom
	shared_ptr<usuari> obte(const std::string& username);

	// Tanca la sessió (pre: hi ha usuari actiu)
	void tancaSessio();

	// Consulta si hi ha sessio activa
	bool existeixSessioActiva() const;

	// Obtine el usuari activo (nullptr si no hay)
	std::shared_ptr<usuari> getUsuariLoggejat() const;



	std::vector<usuari> tots();
	void inserta(const usuari& u);
	void modifica(const usuari& u);
	void esborra(const std::string& username);

private:
	static std::shared_ptr<usuari> s_usuariActiu;
};