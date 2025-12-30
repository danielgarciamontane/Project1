
#include "DAOActivitat.hxx"
#include "../CapaDeDomini/Model/Experiencia.hxx"
#include "../CapaDeDomini/Model/Experiencia-odb.hxx"
#include "../CapaDeDades/connexioBD.hxx"
#include "../CapaDeDomini/Model/Activitat-odb.hxx"
#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/query.hxx>

DTOExperiencia DAOActivitat::obtenirActivitat(const std::string& nomExp) {
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
vector<shared_ptr<Activitat>> DAOActivitat::obteMesReservades(int n) {

	auto db = connexioBD::getInstance().getDB();
	using query = odb::query<Activitat>;
	using result = odb::result<Activitat>;

	odb::transaction t(db->begin());

	// ORDER BY numReserves DESC y limitamos a n (sin usar true_expr).

	result res = db->query<Activitat>(
		" ORDER BY " + query::numReserves + " DESC LIMIT " + query::_ref(n)
	);


	vector<shared_ptr<Activitat>> activitats;
	activitats.reserve(static_cast<size_t>(n));

	for (result::iterator i(res.begin()); i != res.end(); ++i) {
		activitats.push_back(i.load());
	}
	t.commit();
	return activitats;
}