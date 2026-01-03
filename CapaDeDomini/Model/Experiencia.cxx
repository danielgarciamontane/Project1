#include "Experiencia.hxx"
#include "../DTOs/DTOExperiencia.hxx"
#include "PlanGo.hxx"
#include "Escapada.hxx"

Experiencia::Experiencia() : _nom(""), _descripcio(""), _ciutat(""), _maxPlaces(1), _preu(0.0f),
_dataAlta(boost::gregorian::day_clock::local_day()), _numReserves(0) {
}

Experiencia::Experiencia(const string& nom, const string& descripcio, const string& ciutat,
    int maxPlaces, float preu)
    : _nom(nom), _descripcio(descripcio), _ciutat(ciutat), _maxPlaces(maxPlaces), _preu(preu),
    _dataAlta(boost::gregorian::day_clock::local_day()), _numReserves(0)
{
    if (maxPlaces <= 0) {
        throw invalid_argument("El nombre maxim de places ha de ser superior a 0");
    }
    if (preu < 0.0f) {
        throw invalid_argument("El preu no pot ser negatiu");
    }
}

void Experiencia::print_info(std::ostream& os) const
{
    os << "Nom: " << _nom << "\n";
    os << "Preu: " << _preu << "\n";
    os << "Tipus: " << get_tipus() << "\n";
    print_info_detalls(os);
}

DTOExperiencia Experiencia::obteInfoExperiencia() const {
    DTOExperiencia dto;
    dto.nom = _nom;
    dto.descripcio = _descripcio;
    dto.ciutat = _ciutat;
    dto.maxPlaces = _maxPlaces;
    dto.preu = _preu;
    dto.dataAlta = _dataAlta;
    dto.numReserves = _numReserves;
    return dto;
}

float Experiencia::calculaPreu(int numP, bool primRes) const {
    if (numP <= 0) {
        throw invalid_argument("El nombre de persones ha de ser superior a 0");
    }
    float preuTotal = calculaPreu(numP);

    if (primRes) {
        float descompte = PlanGo::getInstance().getDescompte();
        preuTotal = preuTotal * (1.0f - descompte);
    }

    return preuTotal;
}

string Experiencia::get_nom() const {
    return _nom;
}
string Experiencia::get_descripcio() const {
    return _descripcio;
}
string Experiencia::get_ciutat() const {
    return _ciutat;
}
float Experiencia::get_preu() const {
    return _preu;
}
boost::gregorian::date Experiencia::get_dataAlta() const {
    return _dataAlta;
}
int Experiencia::get_numReserves() const {
    return _numReserves;
}

int Experiencia::get_maxPlaces() const {
    return _maxPlaces;
}
void Experiencia::sumaReserva() {
    _numReserves++;
}