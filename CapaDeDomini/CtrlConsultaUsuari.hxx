#pragma once
#include <string>
#include "DTOs/DTOUsuari.hxx"
class CtrlConsultaUsuari {
	public:
	static DTOUsuari consultarUsuari(const std::string& sobrenomU);
};
