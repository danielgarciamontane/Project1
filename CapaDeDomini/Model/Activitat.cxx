#include "Activitat.hxx"

Activitat::Activitat(const std::string& nom,
    double preu,
    int durada)
    : Experiencia(nom, preu),
    durada(durada)
{
}

std::string Activitat::get_tipus() const
{
    return "ACTIVITAT";
}

void Activitat::print_info_detalls(std::ostream& os) const
{
    os << "Durada (hores): " << durada << "\n";
}
