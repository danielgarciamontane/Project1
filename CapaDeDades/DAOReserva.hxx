#pragma once

#include <string>
#include <memory>
using std::shared_ptr;
#include "../CapaDeDomini/Model/Reserva.hxx"

class DAOReserva {
public:

    // Devuelve el número de reservas de un usuario
    static int comptarReservesUsuari(const std::string& sobrenomU);
    void inserta(shared_ptr<Reserva> r);

	static std::vector<shared_ptr<Reserva>> obteReservesUsuari(shared_ptr<usuari> u);
};
