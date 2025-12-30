#pragma once
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "../CapaDeDomini/DTOs/DTOExperiencia.hxx"

class CtrlConsultaMesReservades {
	public:
		static vector<DTOExperiencia> consEscMesReservades(int n);
		static vector<DTOExperiencia> consActMesReservades(int n);
};
