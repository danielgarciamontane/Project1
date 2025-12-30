#pragma once

#include <string>
#include <memory>
#include "../CapaDeDomini/Model/Experiencia.hxx"
#include "../CapaDeDomini/Model/Escapada.hxx"
#include <vector>
using namespace std;
class DAOExperiencia {
	public:
	shared_ptr<Experiencia> obte(const std::string& nomExp);
	vector<shared_ptr<Experiencia>> obteExperienciesPerCiutat(const string& ciutat);
	static vector<shared_ptr<Experiencia>> obteUltimesExperiencies(int n);
	static vector<shared_ptr<Escapada>> obteMesReservades(int n);
};