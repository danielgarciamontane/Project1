#pragma once

#include <string>
#include <memory>

class DAOReserva {
public:

    // Devuelve el número de reservas de un usuario
    static int comptarReservesUsuari(const std::string& sobrenomU);
};
