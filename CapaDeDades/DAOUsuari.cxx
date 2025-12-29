//DAOUsuari.cxx
#include "DAOUsuari.hxx"
#include "connexioBD.hxx"
#include "../CapaDeDomini/Model/Usuari-odb.hxx"
#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/query.hxx>
using namespace std;

shared_ptr<usuari> DAOUsuari::obte(const string& sobrenom) {
   
   
    using namespace odb::core;
    // Alias de la clase de consulta generada por ODB para Usuari.
    using query = odb::query<usuari>;
    
	// Obtenemos la conexión a la base de datos desde el singleton
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();

    //Abrimos transacción (lectura)
    transaction t(db->begin());

    // Consultamos una fila por el campo único sobrenom
    // Si no hay coincidencias, devolvemos nullptr.
    shared_ptr<usuari> u = db->query_one<usuari>(query::username == sobrenom);

    // Cerramos la transacción
    t.commit();

    // Devolvemos el puntero
    return u;
}


bool DAOUsuari::existeixSobrenom(const string& sobrenom) const {
    using namespace odb::core;
    using query = odb::query<usuari>;
    shared_ptr<database> db = connexioBD::getInstance().getDB();
    transaction t(db->begin());
    auto u = db->query_one<usuari>(query::username == sobrenom);
    t.commit();
    return static_cast<bool>(u);
}

bool DAOUsuari::existeixCorreu(const string& correuElectronic) const {
    using namespace odb::core;
    using query = odb::query<usuari>;
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    transaction t(db->begin());
    auto u = db->query_one<usuari>(query::correuElectronic == correuElectronic);
    t.commit();
    return static_cast<bool>(u);
}


void DAOUsuari::crearUsuari(shared_ptr<usuari> u) {
    using namespace odb::core;
    // Obtenemos la conexión a la base de datos desde el singleton
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    // Abrimos transacción (escritura)
    transaction t(db->begin());

    // Persistimos el objeto en la base de datos
    db->persist(u);
    t.commit();
}

void DAOUsuari::modUsu(shared_ptr<usuari> u) {
    using namespace odb::core;
    // Obtenemos la conexión a la base de datos desde el singleton
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    // Abrimos transacción (escritura)
    transaction t(db->begin());
    // Actualizamos el objeto en la base de datos
    db->update(u);
    t.commit();
}
