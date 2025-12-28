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

const string& usuari::get_correuElectronic() const {
    return _correuElectronic;
}

const int& usuari::get_edat() const {
    return _edat;
}
const std::string& usuari::obteContrasenya() const {
    return _contrasenya;
}
DTOUsuari usuari::obteInfoUsuari() const {
	DTOUsuari dto;
	dto.sobrenomU = _username;
	dto.nomComplet = _nomcomplet;
	dto.email = _correuElectronic;
	dto.edat = _edat;
	dto.numReserves = _reserves.size();

    return dto;
}


// Setters 
void usuari::set_username(const std::string& v) {
    _username = v;
}

void usuari::set_nomcomplet(const std::string& v) {
    _nomcomplet = v;
}

void usuari::set_edat(const int& d) {
    _edat = d;
}
