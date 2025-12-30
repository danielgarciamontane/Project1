#include "Reserva.hxx"


// Constructor per defecte
Reserva::Reserva() : _idReserva(0), _dataReserva(day_clock::local_day()), _numPlaces(1), _preuPagat(0.0f) {}

// Constructor privat
Reserva::Reserva(shared_ptr<usuari> u, shared_ptr<Experiencia> e,
    int numP, float preu)
    : _idReserva(0), _dataReserva(day_clock::local_day()), _numPlaces(numP),
    _preuPagat(preu), _usuari(u), _experiencia(e) {
    if (numP <= 0) {
        throw invalid_argument("El nombre de places ha de ser superior a 0");
    }
    if (preu <= 0.0f) {
        throw invalid_argument("El preu pagat ha de ser superior a 0.0");
    }
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

shared_ptr<usuari> Reserva::get_usuari() const {
    return _usuari;
}
shared_ptr<Experiencia> Reserva::get_Experiencia() const {
    return _experiencia;
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

shared_ptr<Reserva> Reserva::creaReserva(shared_ptr<usuari> u, shared_ptr<Experiencia> e,
    int numP, bool primRes) {
    if (u == nullptr) {
        throw invalid_argument("L'usuari no pot ser nul");
    }
    if (e == nullptr) {
        throw invalid_argument("L'experiència no pot ser nul·la");
    }
    if (numP <= 0) {
        throw invalid_argument("El nombre de places ha de ser superior a 0");
    }

    float preu = e->calculaPreu(numP, primRes);
    shared_ptr<Reserva> reserva(new Reserva(u, e, numP, preu));
    e->sumaReserva();

    return reserva;
}

DTOReserva Reserva::obteInfoRes() const {
    DTOReserva dto;
	dto.idReserva = _idReserva;
	dto.numPersones = _numPlaces;
	dto.preuTotal = _preuPagat;
	dto.dataReserva = _dataReserva;
    if (_experiencia != nullptr) {
        dto.experienciaReservada = _experiencia->obteInfoExperiencia();
	}
    return dto;
}