#pragma once

#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
#include <ostream>
#include <odb/core.hxx>
#include "Usuari.hxx"

class usuari;

#pragma db object
class Reserva {
public:
    Reserva() = default;

    Reserva(const int& idReserva,
        const boost::gregorian::date& dataReserva,
        const int& numPlaces,
        const float& preuPagat);

    // Getters
    const int& get_idReserva() const;
    const boost::gregorian::date& get_dataReserva() const;
    const int& get_numPlaces() const;
    const float& get_preuPagat() const;

    // Setters
    void set_idReserva(const int& idReserva);
    void set_dataReserva(const boost::gregorian::date& dataReserva);
    void set_numPlaces(const int& numPlaces);
    void set_preuPagat(const float& preuPagat);

private:
    friend class odb::access;

#pragma db id
    int _idReserva;

    boost::gregorian::date _dataReserva;
    int _numPlaces;
    float _preuPagat;

    #pragma db not_null
    std::shared_ptr<usuari> _usuari;
};
