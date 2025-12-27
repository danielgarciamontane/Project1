#pragma once

#include <string>
#include "DTOs/DTOUsuari.hxx"

class CtrlTancaSessio {
	public:
		bool tancarSessio(const std::string& username);

};
