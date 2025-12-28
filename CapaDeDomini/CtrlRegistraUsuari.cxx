
#include "CtrlRegistraUsuari.hxx"
#include "../CapaDeDades/DAOUsuari.hxx"
#include "../CapaDeDomini/Model/Usuari-odb.hxx"

#include <algorithm>
#include <cctype>
#include <stdexcept>


static bool esCorreuValid(const std::string& e) {
    // Validación mínima: contiene '@' y un punto después (opcional; la BD es la autoridad final)
    auto at = e.find('@');
    auto dot = e.find('.', at == std::string::npos ? 0 : at);
    return at != std::string::npos && dot != std::string::npos && at > 0 && dot > at + 1 && dot < e.size() - 1;
}


void CtrlRegistraUsuari::registrarUsuari(const std::string& nomU,
    const std::string& sobrenomU,
    const std::string& contrasenyaU,
    const std::string& correuElectronicU,
    int edatU) {


    DAOUsuari dao;

    if (edatU < 18) {
        throw runtime_error("No es pot registrar un menor.");
    }
    if (sobrenomU.empty()) {
        throw std::runtime_error("El sobrenom no pot ser buit.");
    }
    if (contrasenyaU.empty()) {
        throw std::runtime_error("La contrasenya no pot ser buida.");
    }
    if (!esCorreuValid(correuElectronicU)) {
        throw std::runtime_error("El correu electronic no te un format valid.");
    }

    if (dao.existeixSobrenom(sobrenomU)) {
        throw runtime_error("Ja existeix un usuari amb aquest sobrenom.");
    }
    if (dao.existeixCorreu(correuElectronicU)) {
        throw runtime_error("Ja existeix un usuari amb aquest correu electronic.");
    }

	shared_ptr<usuari> u(new usuari(sobrenomU, nomU, correuElectronicU, contrasenyaU, edatU));
    dao.crearUsuari(u);
}