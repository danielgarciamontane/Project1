#pragma once
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace std;

class DTOExperiencia {
	public:

	string nom;
	string descripcio;
	string ciutat;
	int maxPlaces;
	float preu;
	boost::gregorian::date dataAlta;
	int numReserves;


	//Hereda
	string hotel;
	int numNits;
	int durada;
	unsigned long id;

	DTOExperiencia() = default;
	DTOExperiencia(const string& n, const string& desc, const string& c,
		const string& tipus, int maxPlaces, int numRes,
		float pr, boost::gregorian::date& data);
	
};
