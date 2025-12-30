#include "CtrlConsultarExperiencies.hxx"
#include "../CapaDeDades/DAOExperiencia.hxx"
#include <stdexcept>
#include "../CapaDeDomini/Model/Experiencia.hxx"
#include <memory>
using namespace std;

vector<DTOExperiencia> CtrlConsultarExperiencies::consultarExperienciesPerCiutat(const string& ciutat, int numPlaces){
	DAOExperiencia dao;
	vector<shared_ptr<Experiencia>> experiencies = dao.obteExperienciesPerCiutat(ciutat);
	vector<DTOExperiencia> llistaDTOs;
	for(const auto& experiencia : experiencies) {
		if (experiencia->get_maxPlaces() - experiencia->get_numReserves() >= numPlaces) {
			DTOExperiencia dto = experiencia->obteInfoExperiencia();
			llistaDTOs.push_back(dto);
		}
	}
	return llistaDTOs;
}