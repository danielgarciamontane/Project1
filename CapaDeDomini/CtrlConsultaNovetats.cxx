#include "CtrlConsultaNovetats.hxx"
#include "../CapaDeDades/DAOExperiencia.hxx"
#include "../CapaDeDomini/DTOs/DTOExperiencia.hxx"
#include <stdexcept>
#include <vector>
using namespace std;

vector<DTOExperiencia> CtrlConsultaNovetats::consultarNovetats(int lim) {
	vector<DTOExperiencia> novetats;
	vector<shared_ptr<Experiencia>> experiencies = DAOExperiencia::obteUltimesExperiencies(lim);
	for (const auto& exp : experiencies) {
		DTOExperiencia dto = exp->obteInfoExperiencia();
		novetats.push_back(dto);
	}
	return novetats;
}