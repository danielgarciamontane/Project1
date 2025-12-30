#pragma once

#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
#include <ostream>
#include <odb/core.hxx>
#include "Usuari.hxx"
#include <memory>
#include "Experiencia.hxx"
#include "../DTOs/DTOReserva.hxx"
using std::shared_ptr;

class usuari;

#pragma db object
class Reserva {
public:

    static shared_ptr<Reserva> creaReserva(shared_ptr<usuari> u, shared_ptr<Experiencia> e,
        int numP, bool primRes);

    // Getters
    const int& get_idReserva() const;
    const boost::gregorian::date& get_dataReserva() const;
    const int& get_numPlaces() const;
    const float& get_preuPagat() const;
	shared_ptr<usuari> get_usuari() const;
    shared_ptr<Experiencia> get_Experiencia() const;

    // Setters
    void set_idReserva(const int& idReserva);
    void set_dataReserva(const boost::gregorian::date& dataReserva);
    void set_numPlaces(const int& numPlaces);
    void set_preuPagat(const float& preuPagat);

	DTOReserva obteInfoRes() const;

private:
    friend class odb::access;

    Reserva();

    Reserva(shared_ptr<usuari> u, shared_ptr<Experiencia> e,
        int num, float preu);

    #pragma db id
    int _idReserva;

    boost::gregorian::date _dataReserva;
    int _numPlaces;
    float _preuPagat;

    #pragma db not_null on_delete(cascade)
    shared_ptr<usuari> _usuari;

    #pragma db not_null
    shared_ptr<Experiencia> _experiencia;
};