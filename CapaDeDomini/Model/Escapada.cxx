#include "Escapada.hxx"

Escapada::Escapada() : Experiencia(), _hotel(""), _numNits(1) {
}

Escapada::Escapada(const string& nom, const string& descripcio, const string& ciutat,
    int maxPlaces, float preu, const string& hotel, int numNits)
    : Experiencia(nom, descripcio, ciutat, maxPlaces, preu), _hotel(hotel), _numNits(numNits) 
{
    if (numNits <= 0) {
        throw invalid_argument("El numero de nits ha de ser superior a 0");
	}
}
//Getters
string Escapada::get_hotel() const {
    return _hotel;
}
int Escapada::get_numNits() const {
    return _numNits;
}

//Setters
void Escapada::set_hotel(const string& hotel) {
    _hotel = hotel;
}
void Escapada::set_numNits(int numNits) {
    if (numNits <= 0) {
        throw invalid_argument("El numero de nits ha de ser superior a 0");
    }
    _numNits = numNits;
}


void Escapada::print_info_detalls(std::ostream& os) const {
    os << "Hotel: " << _hotel << "\n";
    os << "Nits: " << _numNits << "\n";
}

float Escapada::calculaPreu(int nPersones) const {
    return Experiencia::obteInfoExperiencia().preu;
}

void Escapada::atributsEscapada(DTOExperiencia& dto) {
    dto.tipusExp = "Escapada";
    dto.hotel = _hotel;
    dto.numNits = _numNits;
}