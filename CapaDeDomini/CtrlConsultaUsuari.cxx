#include "CtrlConsultaUsuari.hxx"
#include "../CapaDeDades/DAOUsuari.hxx"
#include "../CapaDeDomini/Model/Usuari.hxx"

#include <stdexcept>
#include <memory>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace std;
using namespace boost::gregorian;

DTOUsuari CtrlConsultaUsuari::consultarUsuari(const std::string& sobrenomU)
{
    DAOUsuari dao;

    // Obtenemos el usuario desde la BD
    shared_ptr<usuari> u = dao.obte(sobrenomU);

    // Si no existe, lanzamos excepción
    if (!u) {
        throw runtime_error("L'usuari no existeix");
    }

    // ---- Número de reservas ----
    // TODO: cuando tengas DAOReserva
    int numReserves = 0;

    // ---- Construimos el DTO ----
    DTOUsuari dto(
        u->get_username(),
        u->get_nomcomplet(),
        u->get_correuElectronic(),
        u->get_edat(),
        numReserves
    );

    return dto;
}
