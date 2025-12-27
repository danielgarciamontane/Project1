// usuari.hxx
#pragma once

#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <odb/core.hxx>
using namespace std;

// Indica que és un objecte perquè el reconeixi el compilador de ODB
#pragma db object
class usuari {
public:
    // Constructor por defecto (OBLIGATORIO para ODB)
    usuari() = default;

    // Constructor de conveniencia
    usuari(string username,
        string nomcomplet,
        boost::gregorian::date data_naixement)
        : _username(move(username)),
        _nomcomplet(move(nomcomplet)),
        _data_naixement(data_naixement) {
    }

    // Getters (const, no modifican el objeto)
    const std::string& get_username() const;
    const std::string& get_nomcomplet() const;
    const boost::gregorian::date& get_data_naixement() const;

    // Setters
    void set_username(const std::string& v);
    void set_nomcomplet(const std::string& v);
    void set_data_naixement(const boost::gregorian::date& d);

private:
    // Permet a ODB accedir als membres privats de la classe per fer la persistència
    friend class odb::access;

    // Clave primaria
    #pragma db id
    string _username;
    string _nomcomplet;
    #pragma db type("DATE")
    boost::gregorian::date _data_naixement;
};