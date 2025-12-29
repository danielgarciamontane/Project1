#pragma once
#include <string>
#include <memory>
#include "../CapaDeDomini/DTOs/DTOExperiencia.hxx"
#include "../CapaDeDomini/Model/Escapada.hxx"


class CtrlReservaEscapada {
	public:

		static DTOExperiencia consultarEscapada(const std::string& nomExp);
		float reservarEscapada(const std::string& sobrenom, std::string& nomExp);
};
