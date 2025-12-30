#pragma once
#include "Experiencia.hxx"

#pragma db table("Escapada")
#pragma db object
class Escapada : public Experiencia {
public:
    Escapada();

    Escapada(const string& nom, const string& descipcio, const string& ciutat,
        int maxPlaces, float preu, const string& hotel, int numNits);

    //Getters
	string get_hotel() const;
	int get_numNits() const;

	//Setters
	void set_hotel(const string& hotel);
	void set_numNits(int numNits);
    
    void print_info_detalls(std::ostream& os) const override;

    //Getters

	float calculaPreu(int numP) const override;

    void atributsEscapada(DTOExperiencia& dto);

private:
    friend class odb::access;  
    string _hotel;
    int _numNits;
};
