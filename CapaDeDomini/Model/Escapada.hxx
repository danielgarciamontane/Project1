#pragma once
#include "Experiencia.hxx"

#pragma db object
class Escapada : public Experiencia {
public:
    Escapada() = default;

    Escapada(const std::string& nom,
        double preu,
        int dies);

    std::string get_tipus() const override;
    void print_info_detalls(std::ostream& os) const override;

private:
    friend class odb::access;   
    int dies;
};
