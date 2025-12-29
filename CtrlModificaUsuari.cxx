#include "CtrlModificaUsuari.hxx"
#include "CapaDeDades/DAOUsuari.hxx"
#include "CapaDeDomini/Model/Usuari.hxx"

#include <memory>
#include <stdexcept>

using namespace std;

CtrlModificaUsuari::CtrlModificaUsuari(const std::string& sobrenomU)
    : _sobrenomUsuari(sobrenomU)
{
}

DTOUsuari CtrlModificaUsuari::consultaUsuari()
{
    DAOUsuari dao;

    // Obtenir usuari loguejat
    shared_ptr<usuari> u = dao.obte(_sobrenomUsuari);

    if (!u) {
        throw runtime_error("L'usuari loguejat no existeix");
    }

    // TODO: quan existeixi DAOReserva
    int numReserves = 0;

    // Construir DTO
    DTOUsuari dto(
        u->get_nomcomplet(),
        u->get_username(),
        u->get_correuElectronic(),
        u->get_edat(),
        numReserves
    );

    return dto;
}

void CtrlModificaUsuari::modificaUsuari(const std::string& nouNom,
    const std::string& nouEmail,
    int novaEdat)
{
    DAOUsuari dao;
    shared_ptr<usuari> u = dao.obte(_sobrenomUsuari);

    if (!u)
        throw runtime_error("L'usuari no existeix");

    // Validacions
    if (novaEdat != -1 && novaEdat < 18)
        throw runtime_error("L'usuari és menor d'edat");

    if (!nouEmail.empty() &&
        nouEmail != u->get_correuElectronic() &&
        dao.existeixCorreu(nouEmail))
    {
        throw runtime_error("El correu electronic ja existeix");
    }

    // Escenari principal
    if (!nouNom.empty())
        u->set_nomcomplet(nouNom);

    if (!nouEmail.empty())
        u->set_correuElectronic(nouEmail);

    if (novaEdat >= 18)
        u->set_edat(novaEdat);

    // Persistència
    dao.modifica(*u);
}
