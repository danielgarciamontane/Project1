#pragma once
#include <string>
#include "../CapaDeDomini/Model/Activitat.hxx"
#include "../CapaDeDomini/DTOs/DTOExperiencia.hxx"

class DAOActivitat {
	public:
		DTOExperiencia obtenirActivitat(const std::string& nomExp);
		vector<shared_ptr<Activitat>> obteMesReservades(int n);
};
