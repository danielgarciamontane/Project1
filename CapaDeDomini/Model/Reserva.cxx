#include "Reserva.hxx"

// Constructor
Reserva::Reserva(const int& idReserva,
    const boost::gregorian::date& dataReserva,
    const int& numPlaces,
    const float& preuPagat)
    : _idReserva(idReserva),
    _dataReserva(dataReserva),
    _numPlaces(numPlaces),
    _preuPagat(preuPagat)
{
}

// Getters
const int& Reserva::get_idReserva() const {
    return _idReserva;
}

const boost::gregorian::date& Reserva::get_dataReserva() const {
    return _dataReserva;
}

const int& Reserva::get_numPlaces() const {
    return _numPlaces;
}

const float& Reserva::get_preuPagat() const {
    return _preuPagat;
}

// Setters
void Reserva::set_idReserva(const int& idReserva) {
    _idReserva = idReserva;
}

void Reserva::set_dataReserva(const boost::gregorian::date& dataReserva) {
    _dataReserva = dataReserva;
}

void Reserva::set_numPlaces(const int& numPlaces) {
    _numPlaces = numPlaces;
}

void Reserva::set_preuPagat(const float& preuPagat) {
    _preuPagat = preuPagat;
}

