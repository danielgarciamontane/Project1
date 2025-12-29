#pragma once
#include <string>
#include <ostream>
#include <odb/core.hxx>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "../DTOs/DTOExperiencia.hxx"
using namespace std;

#pragma db object polymorphic
class Experiencia {
public:
    Experiencia() = default;
    Experiencia(const std::string& nom, float preu);

    // Getters
	DTOExperiencia obteInfoExperiencia() const;
    int get_maxPlaces() const;


    float calculaPreu(int numP, bool primRes) const;
	void sumaReserva();
    virtual ~Experiencia() = default;

    // Métodos polimórficos
    virtual std::string get_tipus() const = 0;
    virtual void print_info_detalls(std::ostream& os) const = 0;
    void print_info(std::ostream& os) const;

private:
    friend class odb::access;   

    #pragma db id auto
    string _nom;
    string _descripcio;
	string _ciutat;
	int _maxPlaces;
    float _preu;
	boost::gregorian::date _dataAlta;
	int _numReserves;
};
