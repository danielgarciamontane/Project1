#pragma once
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "../CapaDeDomini/DTOs/DTOLlistaReserves.hxx"
using namespace std;

class CtrlConsultarReserves {
	public:
	DTOLlistaReserves consultarReservesUsuari(const string& sobrenom);
};
