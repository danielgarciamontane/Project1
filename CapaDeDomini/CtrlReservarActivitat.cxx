
#include "CtrlReservarActivitat.hxx"
#include "../CapaDeDades/DAOExperiencia.hxx"
#include "../CapaDeDades/DAOUsuari.hxx"

DTOExperiencia CtrlReservarActivitat::consultarActivitat(const std::string& nomExp){
	DAOExperiencia dao;
	shared_ptr<Experiencia> act = dao.obte(nomExp);
	return act->obteInfoExperiencia();
}

float CtrlReservarActivitat::reservarActivitat(const std::string& sobrenom, std::string& nomAct){
	DAOUsuari dao;
	DAOExperiencia daoExp;
	shared_ptr<usuari> u = dao.obte(sobrenom);
	if (u == nullptr) {
		throw runtime_error("L'usuari no existeix");
	}
	shared_ptr<Experiencia> act = daoExp.obte(nomAct);
	float preu = u->afegirReserva(act);
	return preu;
}