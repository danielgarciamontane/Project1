#pragma once
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::gregorian;

class DTOUsuari {
public:
    // Constructora por defecto
    DTOUsuari() = default;

    // Constructora a partir de parámetros
    DTOUsuari(const std::string& sobrenomU,
        const std::string& nomComplet,
        const std::string& email,
        const int& edat,
        const int& numReserves)
        : sobrenomU(sobrenomU),
        nomComplet(nomComplet),
        email(email),
        edat(edat),
		numReserves(numReserves)
    {
    }

    // Campos públicos
    std::string sobrenomU;
    std::string nomComplet;
    std::string email;
    int edat;
	int numReserves;
};