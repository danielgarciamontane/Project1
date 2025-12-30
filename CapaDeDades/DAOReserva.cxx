#include "DAOReserva.hxx"
#include "connexioBD.hxx"
#include "../CapaDeDomini/Model/Reserva-odb.hxx"
#include "../CapaDeDomini/Model/Usuari-odb.hxx"
#include "../CapaDeDomini/Model/Reserva.hxx"

#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/core.hxx>
#include <odb/query.hxx>
#include <vector>
using namespace std;

int DAOReserva::comptarReservesUsuari(const string& sobrenom)
{
    using namespace odb::core;
    using query = odb::query<Reserva>;

    shared_ptr<database> db = connexioBD::getInstance().getDB();
    transaction t(db->begin());

    // Consulta todas las reservas del usuario
    auto r = db->query<Reserva>(
        query::usuari->username == sobrenom
    );

    int count = static_cast<int>(r.size());

    t.commit();
    return count;
}
void DAOReserva::inserta(shared_ptr<Reserva> r) {
    shared_ptr<odb::database> db = connexioBD::getInstance().getDB();
    odb::transaction t(db->begin());
    db->persist(r);
    t.commit();
}

std::vector<shared_ptr<Reserva>> DAOReserva::obteReservesUsuari(shared_ptr<usuari> u) {
    using namespace odb::core;
    shared_ptr<database> db = connexioBD::getInstance().getDB();
    transaction t(db->begin());
    
    //Creamos los alias del tipo
    typedef odb::query<Reserva> query;
    typedef odb::result<Reserva> result;

    result res(db->query<Reserva>(query::usuari == u->get_username()));
    vector<shared_ptr<Reserva>> reservesUsuari;

    for (result::iterator i(res.begin()); i != res.end(); ++i) {
        reservesUsuari.push_back(i.load());
    }

    t.commit();
    return reservesUsuari;
}
