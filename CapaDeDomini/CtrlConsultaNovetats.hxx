#pragma once
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "../CapaDeDomini/DTOs/DTOExperiencia.hxx"
using namespace std;

class CtrlConsultaNovetats {
	public:
		vector<DTOExperiencia> consultarNovetats(int lim);
};
