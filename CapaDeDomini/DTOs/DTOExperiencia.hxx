#pragma once
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace std;

class DTOExperiencia {
	public:
	
	string tipusExp;
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

	DTOExperiencia();
	DTOExperiencia(const string& nom, const string& descipcio, const string& ciutat,
		const string& tipusExp, int maxPlaces, int numReserves,
		float preu, boost::gregorian::date& data);
	
};
