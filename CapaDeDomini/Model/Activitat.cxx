#include "Activitat.hxx"

Activitat::Activitat(const std::string& nom, const std::string& descripcio, const std::string& ciutat,
    int maxPlaces, float preu, int durada)
    : Experiencia(nom, descripcio, ciutat, maxPlaces, preu), _durada(durada) 
{
    if (durada <= 0) {
        throw std::invalid_argument("La durada ha de ser superior a 0");
    }
}

int Activitat::get_durada() const{
    return _durada;
}

std::string Activitat::get_tipus() const
{
    return "ACTIVITAT";
}

void Activitat::print_info_detalls(std::ostream& os) const
{
    os << "Durada (hores): " << _durada << "\n";
}

void Activitat::atributsActivitat(DTOExperiencia& dto) {
    dto.tipusExp = "ACTIVITAT";
    dto.durada = _durada;
} 
