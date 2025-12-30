#include "CtrlReservaEscapada.hxx"
#include "../CapaDeDades/DAOEscapada.hxx"
#include "../CapaDeDades/DAOUsuari.hxx"
#include "../CapaDeDades/DAOExperiencia.hxx"
#include <stdexcept>

DTOExperiencia CtrlReservaEscapada::consultarEscapada(const std::string& nomExp){
	DAOExperiencia dao;
	shared_ptr<Experiencia> esc = dao.obte(nomExp);
	return esc->obteInfoExperiencia();
}

float CtrlReservaEscapada::reservarEscapada(const std::string& sobrenom, std::string& nomEsc){
	DAOUsuari dao;
	DAOExperiencia daoExp;
	shared_ptr<usuari> u = dao.obte(sobrenom);
	if (u == nullptr) {
		throw runtime_error("L'usuari no existeix");
	}
	shared_ptr<Experiencia> esc = daoExp.obte(nomEsc);
	float preu = u->afegirReserva(esc);
	return preu;
}