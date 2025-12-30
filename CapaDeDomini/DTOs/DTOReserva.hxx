#pragma once
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "DTOExperiencia.hxx"
using namespace std;
class DTOReserva {
public:

	int idReserva;
	int numPersones;
	float preuTotal;
	boost::gregorian::date dataReserva;
	DTOExperiencia experienciaReservada;

	DTOReserva() = default;
	DTOReserva(int idRes, int numPers, float preuTot,
		boost::gregorian::date dataRes,
		const DTOExperiencia& expRes);
};
