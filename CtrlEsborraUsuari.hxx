#pragma once
#include <string>

class CtrlEsborrarUsuari {
public:
    // Constructor: recibe el usuario logueado
    CtrlEsborrarUsuari(const std::string& sobrenomU);

    // Esborra l'usuari si la contrasenya es correcta
    void esborraUsuari(const std::string& contrasenya);

private:
    std::string _sobrenomUsuari;
};
