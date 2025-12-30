#include <iostream>
#include "CtrlEsborraUsuari.hxx"
#include "../CapaDeDades/DAOUsuari.hxx"
#include <stdexcept>

void CtrlEsborraUsuari::esborraUsuari(const std::string& sobrenomU, const std::string& contra) {
	DAOUsuari dao;
	shared_ptr<usuari> usuariPtr = dao.obte(sobrenomU);
	if (!usuariPtr) {
		throw std::runtime_error("L'usuari amb sobrenom '" + sobrenomU + "' no existeix.");
	}

	dao.esbUsu(sobrenomU);
}