#include "Escapada.hxx"

Escapada::Escapada(const std::string& nom,
    double preu,
    int dies)
    : Experiencia(nom, preu),
    dies(dies)
{
}


std::string Escapada::get_tipus() const
{
    return "ESCAPADA";
}

void Escapada::print_info_detalls(std::ostream& os) const
{
    os << "Dies: " << dies << "\n";
}

float Escapada::calculaPreuEscapada(int nPersones) const {
    return _preu;
}