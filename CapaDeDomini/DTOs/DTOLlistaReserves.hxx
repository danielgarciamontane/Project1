#pragma once
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <vector>
#include "DTOReserva.hxx"
using namespace std;

class DTOLlistaReserves {
public:

	float totalPagat;
	vector<DTOReserva> llistaReserves;

	DTOLlistaReserves() = default;
	DTOLlistaReserves(float total, const vector<DTOReserva>& llista);
};
