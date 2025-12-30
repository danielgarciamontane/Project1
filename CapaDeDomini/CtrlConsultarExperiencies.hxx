#pragma once
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "../CapaDeDomini/DTOs/DTOLlistaReserves.hxx"
#include "../CapaDeDomini/DTOs/DTOExperiencia.hxx"
using namespace std;

class CtrlConsultarExperiencies {
	public:
	//Un usuari, que hagi iniciat sessió o no, vol consultar la llista d'experiències que estàn disponibles a una ciutat.

	vector<DTOExperiencia> consultarExperienciesPerCiutat(const string& ciutat, int numPlaces);

};
