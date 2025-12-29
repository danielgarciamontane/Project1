
#include "DAOExperiencia.hxx"
#include "connexioBD.hxx"
#include "../CapaDeDomini/Model/Experiencia-odb.hxx"
#include <odb/database.hxx>
#include <odb/transaction.hxx>
using namespace std;

shared_ptr<Experiencia> DAOExperiencia::obte(const string& nom) {

    using namespace odb::core;
    // Alias de la clase de consulta generada por ODB para Usuari.
    using query = odb::query<Experiencia>;
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());

    shared_ptr<Experiencia> experiencia = db->find<Experiencia>(nom);

    t.commit();
    return experiencia;
}