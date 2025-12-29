#include "Experiencia.hxx"
#include "../DTOs/DTOExperiencia.hxx"
#include "PlanGo.hxx"
#include "Escapada.hxx"

Experiencia::Experiencia(const std::string& nom, float preu)
    : _nom(nom), _preu(preu)
{
}

void Experiencia::print_info(std::ostream& os) const
{
    os << "Nom: " << _nom << "\n";
    os << "Preu: " << _preu << "\n";
    os << "Tipus: " << get_tipus() << "\n";
    print_info_detalls(os);
}

DTOExperiencia Experiencia::obteInfoExperiencia() const{
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
    Escapada esc;
    float preuTotal =esc.calculaPreuEscapada(numP);

    if (primRes) {
        float descompte = PlanGo::getInstance().getDescompte();
        preuTotal = preuTotal * (1.0f - descompte);
    }

    return preuTotal;
}

int Experiencia::get_maxPlaces() const {
	return _maxPlaces;
}
void Experiencia::sumaReserva() {
    _numReserves++;
}
