#include "CtrlConsultarReserves.hxx"
#include "../CapaDeDades/DAOUsuari.hxx"
#include "../CapaDeDomini/DTOs/DTOLlistaReserves.hxx"
#include "../CapaDeDades/DAOReserva.hxx"
#include <stdexcept>

DTOLlistaReserves CtrlConsultarReserves::consultarReservesUsuari(const string& sobrenom){
	DAOUsuari dao;
	shared_ptr<usuari> u = dao.obte(sobrenom);
	if (u == nullptr) {
		throw runtime_error("L'usuari no existeix");
	}
	vector<shared_ptr<Reserva>> reservesUsuari = DAOReserva::obteReservesUsuari(u);
	DTOLlistaReserves llistaReserves;
	
	for(const auto& reserva : reservesUsuari) {
		DTOReserva dto = reserva->obteInfoRes();
		llistaReserves.llistaReserves.push_back(dto);
		llistaReserves.totalPagat += reserva->get_preuPagat();
	}
	return llistaReserves;
}