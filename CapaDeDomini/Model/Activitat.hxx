#pragma once
#include "Experiencia.hxx"

#pragma db object
class Activitat : public Experiencia {
public:
    Activitat() = default;

    Activitat(const std::string& nom,
        double preu,
        int durada);

    std::string get_tipus() const override;
    void print_info_detalls(std::ostream& os) const override;

private:
    friend class odb::access;   
    int durada; 
};
