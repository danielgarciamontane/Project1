#pragma once

#include <string>
#include "../CapaDeDomini/DTOs/DTOExperiencia.hxx"
#include "../CapaDeDomini/Model/Escapada.hxx"

class DAOEscapada {
	public:
	DTOExperiencia obtenirEscapada(const std::string& idEscapada);
	vector<shared_ptr<Escapada>> obteMesReservades(int n);
};