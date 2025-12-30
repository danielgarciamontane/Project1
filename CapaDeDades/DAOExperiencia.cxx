
#include "DAOExperiencia.hxx"
#include "connexioBD.hxx"
#include "../CapaDeDomini/Model/Experiencia-odb.hxx"
#include "../CapaDeDomini/Model/Escapada-odb.hxx"
#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/query.hxx>

using namespace std;

shared_ptr<Experiencia> DAOExperiencia::obte(const string& nom) {
    using namespace odb::core;
    using query = odb::query<Experiencia>;

    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    transaction t(db->begin());

    cout << "DAOExperiencia: Obtenint experiencia amb nom: " << nom << endl;

    shared_ptr<Experiencia> experiencia = db->find<Experiencia>(nom);
    if (experiencia == nullptr) {
		throw runtime_error("No s'ha trobat cap experiencia amb aquest nom");
	}
    cout << "DAOExperiencia: Experiencia obtinguda: "
        << (experiencia ? experiencia->get_nom() : "nullptr") << endl;

    t.commit();
    return experiencia;
}
vector<shared_ptr<Experiencia>> DAOExperiencia::obteExperienciesPerCiutat(const string& ciutat) {
    using namespace odb::core;
    using query = odb::query<Experiencia>;
    using result = odb::result<Experiencia>;
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    transaction t(db->begin());
    result r(db->query<Experiencia>(query::ciutat == ciutat));
    vector<shared_ptr<Experiencia>> experiencies;
    for (result::iterator i(r.begin()); i != r.end(); ++i) {
        experiencies.push_back(i.load());
    }
    t.commit();
    return experiencies;
}
