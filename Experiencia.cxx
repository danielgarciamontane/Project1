#include "Experiencia.hxx"

Experiencia::Experiencia(const std::string& nom, double preu)
    : nom(nom), preu(preu)
{
}

void Experiencia::print_info(std::ostream& os) const
{
    os << "Nom: " << nom << "\n";
    os << "Preu: " << preu << "\n";
    os << "Tipus: " << get_tipus() << "\n";
    print_info_detalls(os);
}
