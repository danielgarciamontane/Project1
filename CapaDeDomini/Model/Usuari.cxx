// usuari.cxx
#include "usuari.hxx"
#include <utility> // std::move


// Getters
const string& usuari::get_username() const {
    return _username;
}

const string& usuari::get_nomcomplet() const {
    return _nomcomplet;
}

const boost::gregorian::date& usuari::get_data_naixement() const {
    return _data_naixement;
}
const std::string& usuari::obteContrasenya() const {
    return _contrasenya;
}
DTOUsuari usuari::obteInfoUsuari() const {
	DTOUsuari dto;
	dto.sobrenomU = _username;
	dto.nomComplet = _nomcomplet;
	dto.email = _correuElectronic;
	dto.data_naixement = _data_naixement;

    return dto;
}


// Setters 
void usuari::set_username(const std::string& v) {
    _username = v;
}

void usuari::set_nomcomplet(const std::string& v) {
    _nomcomplet = v;
}

void usuari::set_data_naixement(const boost::gregorian::date& d) {
    _data_naixement = d;
}
