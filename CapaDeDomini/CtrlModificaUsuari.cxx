
#include "CtrlModificaUsuari.hxx"
#include "../CapaDeDades/DAOUsuari.hxx"
#include "../CapaDeDomini/Model/Usuari.hxx"
#include "CtrlConsultaUsuari.hxx"
#include <stdexcept>
#include <memory>
using namespace std;

DTOUsuari CtrlModificaUsuari::consultarUsuari(const std::string& sobrenomU) {
	CtrlConsultaUsuari ctrl;
	DTOUsuari dto = ctrl.consultarUsuari(sobrenomU);

	return dto;
}
DTOUsuari CtrlModificaUsuari::modificaUsuari(const std::string& sobrenomU,
	const std::string& nouNomComplet,
	const std::string& nouEmail,
	const int& novaEdat)
{
	DAOUsuari dao;
	// Obtenemos el usuario desde la BD
	shared_ptr<usuari> u = dao.obte(sobrenomU);
	// Si no existe, lanzamos excepción
	if (!u) {
		throw runtime_error("L'usuari no existeix");
	}
	if (!nouEmail.empty() && nouEmail != u->get_correuElectronic()) {
		if (dao.existeixCorreu(nouEmail)) {
			throw runtime_error("El nou correu electrònic ja existeix");
		}
		u->set_correuElectronic(nouEmail);
	}
	if (!nouNomComplet.empty() && nouNomComplet != u->get_nomcomplet()) {
		u->set_nomcomplet(nouNomComplet);
	}
	if (novaEdat != u->get_edat()) {
		if (novaEdat < 18) {
			throw runtime_error("No es poden registrar usuaris menors");
		}
		u->set_edat(novaEdat);
	} 

	DAOUsuari::modUsu(u);
	DTOUsuari dto;
	dto = u->obteInfoUsuari();
	return dto;
}
