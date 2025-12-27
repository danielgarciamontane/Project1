#pragma once
#include <string>
#include <vector>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "DTOUsuari.hxx"

// Fachada de la capa de dominio (Singleton)
class CapaDeDomini {
public:
    static CapaDeDomini& getInstance() {
        static CapaDeDomini instance;
        return instance;
    }

    void registrarUsuari(const std::string& username,
        const std::string& nomcomplet,
        const boost::gregorian::date& data_naixement);

    void esborrarUsuari(const std::string& username);

    void modificarUsuari(const std::string& username,
        const std::string& nou_nom,
        const boost::gregorian::date& nova_data);

    DTOUsuari consultarUsuari(const std::string& username);

    // Opcional: para tu opción de menú 2 (listar)
    std::vector<DTOUsuari> llistarUsuaris();

private:
    CapaDeDomini() = default;
    CapaDeDomini(const CapaDeDomini&) = delete;
    CapaDeDomini& operator=(const CapaDeDomini&) = delete;
};
