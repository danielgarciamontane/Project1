#pragma once
#include "Experiencia.hxx"

#pragma db object polymorphic
#pragma db table("Escapada")
class Escapada : public Experiencia {
public:
    Escapada();

    Escapada(const string& nom, const string& descripcio, const string& ciutat,
        int maxPlaces, float preu, const string& hotel, int numNits);

    string get_hotel() const;
    int get_numNits() const;

    void set_hotel(const string& hotel);
    void set_numNits(int numNits);

    void print_info_detalls(std::ostream& os) const override;

    float calculaPreu(int numP) const override;

    void atributsEscapada(DTOExperiencia& dto);

private:
    friend class odb::access;
    string _hotel;
    int _numNits;
};
