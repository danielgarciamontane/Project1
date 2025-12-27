#include "CtrlIniciSessio.hxx"
#include "../CapaDeDades/DAOUsuari.hxx"
#include "Model/Usuari.hxx"
#include <stdexcept>

DTOUsuari CtrlIniciSessio::obtenirInfoUsuari(const string& sobrenomU, const string& contrasenya) {
	
	if (sobrenomU.empty() || contrasenya.empty()) {
		throw runtime_error("El sobrenom i la contrasenya no poden estar buits.");
	}
	
	DAOUsuari daoUsuari;
	shared_ptr<usuari> u = daoUsuari.obte(sobrenomU);
	
	if (u == nullptr) throw runtime_error("Usuari inexistent.");
	if (contrasenya != u->obteContrasenya()) {
		throw runtime_error("Contrasenya incorrecta.");
	}

	DTOUsuari dto;
	dto = u->obteInfoUsuari();

	return dto;
}

