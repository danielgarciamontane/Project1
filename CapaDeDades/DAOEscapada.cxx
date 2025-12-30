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

vector<shared_ptr<Escapada>> DAOEscapada::obteMesReservades(int n) {
	auto db = connexioBD::getInstance().getDB();
	using query = odb::query<Escapada>;
	using result = odb::result<Escapada>;
	odb::transaction t(db->begin());
	result res = db->query<Escapada>(
		" ORDER BY " + query::numReserves + " DESC LIMIT " + query::_ref(n)
	);
	vector<shared_ptr<Escapada>> escapades;
	escapades.reserve(static_cast<size_t>(n));
	for (result::iterator i(res.begin()); i != res.end(); ++i) {
		escapades.push_back(i.load());
	}
	t.commit();
	return escapades;
}


