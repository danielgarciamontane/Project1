#pragma once
#include "Experiencia.hxx"

#pragma db object
class Activitat : public Experiencia {
public:
    Activitat() = default;

    Activitat(const string& nom, const string& descipcio, const string& ciutat,
        int maxPlaces, float preu, int durada);

    //Getters
    int get_durada() const;

    std::string get_tipus() const override;
    void print_info_detalls(std::ostream& os) const override;

    void atributsActivitat(DTOExperiencia& dto);

private:
    friend class odb::access;   
    int _durada; 
};
