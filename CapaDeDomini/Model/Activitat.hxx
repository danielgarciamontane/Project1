#pragma once
#include "Experiencia.hxx"

#pragma db object polymorphic
class Activitat : public Experiencia {
public:
    Activitat() = default;

    Activitat(const string& nom, const string& descripcio, const string& ciutat,
        int maxPlaces, float preu, int durada);

    int get_durada() const;

    std::string get_tipus() const override;
    void print_info_detalls(std::ostream& os) const override;

    void atributsActivitat(DTOExperiencia& dto);

private:
    friend class odb::access;
    int _durada;
};
