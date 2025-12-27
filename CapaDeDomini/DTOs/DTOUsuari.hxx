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
        const boost::gregorian::date& dataNaixement)
        : sobrenomU(sobrenomU),
        nomComplet(nomComplet),
        email(email),
        data_naixement(dataNaixement)
    {
    }

    // Campos públicos (como ya tienes)
    std::string sobrenomU;
    std::string nomComplet;
    std::string email;
    boost::gregorian::date data_naixement{
        boost::gregorian::date(boost::date_time::not_a_date_time)
    };
};