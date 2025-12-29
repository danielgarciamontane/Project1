#pragma once

#include <string>
#include <memory>
#include "../CapaDeDomini/Model/Experiencia.hxx"
class DAOExperiencia {
	public:
	shared_ptr<Experiencia> obte(const std::string& nomExp);
};