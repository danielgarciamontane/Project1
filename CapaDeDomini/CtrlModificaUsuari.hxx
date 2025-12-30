#pragma once
#include "../CapaDeDomini/DTOs/DTOUsuari.hxx"
#include <string>
class CtrlModificaUsuari {
	public:
		DTOUsuari consultarUsuari(const std::string& sobrenomU);
		DTOUsuari modificaUsuari(const std::string& sobrenomU,
			const std::string& nouNomComplet,
			const std::string& nouEmail,
			const int& novaEdat);
};
