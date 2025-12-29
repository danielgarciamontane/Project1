#pragma once
#include <string>
#include "CapaDeDomini/DTOs/DTOUsuari.hxx"

class CtrlModificaUsuari {
public:
    // Constructor: recibe el usuario logueado
    CtrlModificaUsuari(const std::string& sobrenomU);

    // Operació demanada a l'enunciat
    DTOUsuari consultaUsuari();

    void modificaUsuari(const std::string& nouNom,
        const std::string& nouEmail,
        int novaEdat);

private:
    std::string _sobrenomUsuari;
};
