
#include "DAOExperiencia.hxx"
#include "connexioBD.hxx"
#include "../CapaDeDomini/Model/Experiencia-odb.hxx"
#include "../CapaDeDomini/Model/Escapada-odb.hxx"
#include "../CapaDeDomini/Model/Activitat-odb.hxx"
#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/query.hxx>
#include <odb/session.hxx>
#include <vector>


using namespace std;
shared_ptr<Experiencia> DAOExperiencia::obte(const string& nom)
{
    using namespace odb::core;

    auto db = connexioBD::getInstance().getDB();

    session s;                 
    transaction t(db->begin());

    shared_ptr<Experiencia> experiencia =
        db->find<Experiencia>(nom);

    if (!experiencia) {
        throw runtime_error("No s'ha trobat cap experiencia amb aquest nom");
    }

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
//vector amb ultimes 10 experiències. Si hi ha menys de 10 experiències, retorna totes.
vector<shared_ptr<Experiencia>> DAOExperiencia::obteUltimesExperiencies(int n) {

    auto db = connexioBD::getInstance().getDB();
    vector<shared_ptr<Experiencia>> res;
    res.reserve(static_cast<size_t>(n));

    using Q = odb::query<Experiencia>;
    odb::transaction t(db->begin());

    // Ordena por la columna de fecha de alta en DESC y limita a n
    // OJO: sustituye Q::dataAlta por el *nombre real del miembro* en tu clase.
    odb::result<Experiencia> rs =
        db->query<Experiencia>("ORDER BY" + Q::dataAlta + "DESC" + Q::_ref(n));

    // Si Experiencia es base polimórfica, i.load() reconstruye la subclase correcta
    for (odb::result<Experiencia>::iterator i(rs.begin()); i != rs.end(); ++i)
    {
        res.push_back(i.load());
    }

    t.commit();
    return res;
}
