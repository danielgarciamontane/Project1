#include "CtrlConsultaMesReservades.hxx"
#include "../CapaDeDades/DAOExperiencia.hxx"
#include "../CapaDeDomini/DTOs/DTOExperiencia.hxx"
#include "../CapaDeDomini/Model/Escapada.hxx"
#include "../CapaDeDomini/Model/Activitat.hxx"
#include "../CapaDeDades/DAOEscapada.hxx"
#include "../CapaDeDades/DAOActivitat.hxx"
#include <stdexcept>
#include <vector>
using namespace std;

vector<DTOExperiencia> CtrlConsultaMesReservades::consEscMesReservades(int n) {
	vector<DTOExperiencia> mesReservades;
	DAOEscapada daoEsc;
	vector<shared_ptr<Escapada>> escapades = daoEsc.obteMesReservades(n);
	
	for (const auto& esc : escapades) {
		mesReservades.push_back(esc->obteInfoExperiencia());
	}
	
	return mesReservades;
}
vector<DTOExperiencia> CtrlConsultaMesReservades::consActMesReservades(int n) {
	vector<DTOExperiencia> mesReservades;

	DAOActivitat daoAct;
	vector<shared_ptr<Activitat>> acts = daoAct.obteMesReservades(n);

	for (const auto& act : acts) {
			mesReservades.push_back(act->obteInfoExperiencia());
		}
	return mesReservades;
}

