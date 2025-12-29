#pragma once

#include <string>
#include "../CapaDeDomini/DTOs/DTOExperiencia.hxx"
class DAOEscapada {
	public:
	DTOExperiencia obtenirEscapada(const std::string& idEscapada);
};