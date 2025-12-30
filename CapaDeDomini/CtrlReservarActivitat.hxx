#pragma once
#include <string>
#include "DTOs/DTOExperiencia.hxx"
class CtrlReservarActivitat {
	public:
		DTOExperiencia consultarActivitat(const std::string& nomExp);
		float reservarActivitat(const std::string& sobrenom, std::string& nomAct);
};