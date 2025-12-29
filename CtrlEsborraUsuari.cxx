#include "CtrlEsborraUsuari.hxx"
#include "CapaDeDades/DAOUsuari.hxx"
#include "CapaDeDomini/Model/Usuari.hxx"

#include <memory>
#include <stdexcept>

using namespace std;

CtrlEsborrarUsuari::CtrlEsborrarUsuari(const std::string& sobrenomU)
    : _sobrenomUsuari(sobrenomU)
{
}

void CtrlEsborrarUsuari::esborraUsuari(const std::string& contrasenya)
{
    DAOUsuari dao;

    // Obtenir usuari loguejat
    shared_ptr<usuari> u = dao.obte(_sobrenomUsuari);

    if (!u)
        throw runtime_error("L'usuari no existeix");

    // Comprovacio de contrasenya
    if (u->obteContrasenya() != contrasenya)
        throw runtime_error("Contrasenya incorrecta");

    // Esborrat
    dao.esborra(_sobrenomUsuari);
}
