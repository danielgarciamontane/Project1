// usuari.hxx
#pragma once

#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <odb/core.hxx>
#include "../DTOs/DTOUsuari.hxx"
#include "Reserva.hxx"
#include <vector>
#include <memory>
#include "Escapada.hxx"
using namespace std;

class Reserva;

// Indica que és un objecte perquè el reconeixi el compilador de ODB
#pragma db object
class usuari {
public:
    // Constructor por defecto (OBLIGATORIO para ODB)
    usuari() = default;

    // Constructor de conveniencia
    usuari(string username,
        string nomcomplet,
        string correuElectronic,
        string contrasenya,
        int edat)
        : _username(move(username)),
        _nomcomplet(move(nomcomplet)),
		_correuElectronic(move(correuElectronic)),
		_contrasenya(move(contrasenya)),
        _edat(edat) {
    }

    // Getters (const, no modifican el objeto)
    const std::string& get_username() const;
    const std::string& get_nomcomplet() const;
	const std::string& get_correuElectronic() const;
    const int& get_edat() const;
	const std::string& obteContrasenya() const; 
	DTOUsuari obteInfoUsuari() const;

    // Setters
    void set_username(const std::string& v);
    void set_nomcomplet(const std::string& v);
	void set_correuElectronic(const std::string& v);
    void set_edat(const int& d);

    float afegirReserva(shared_ptr<Experiencia>& escapada);

private:
    // Permet a ODB accedir als membres privats de la classe per fer la persistència
    friend class odb::access;

    // Clave primaria
    #pragma db id
    string _username;
    string _nomcomplet;
	string _correuElectronic;
	string _contrasenya;
    int _edat;
    #pragma db inverse(_usuari)
    vector<shared_ptr<Reserva>> _reserves;
};