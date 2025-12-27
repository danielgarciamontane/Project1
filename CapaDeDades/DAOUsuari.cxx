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
