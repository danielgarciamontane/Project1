#include "DAOEscapada.hxx"
#include "../CapaDeDomini/Model/Experiencia.hxx"
#include "../CapaDeDomini/Model/Experiencia-odb.hxx"
#include "../CapaDeDomini/Model/Escapada-odb.hxx"
#include "../CapaDeDades/connexioBD.hxx"
#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/query.hxx>
#include <stdexcept>


DTOExperiencia DAOEscapada::obtenirEscapada(const std::string& nomExp) {
	using namespace odb::core;
	// Alias de la clase de consulta generada por ODB para Usuari.
	using query = odb::query<Experiencia>;

	shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
	odb::transaction t(db->begin());
	shared_ptr<Experiencia> u = db->query_one<Experiencia>(query::nom == nomExp);
	t.commit();

	if (!u) {
		throw std::runtime_error("Escapada no trobada amb l'ID proporcionat.");
	}
	return u->obteInfoExperiencia();
}


