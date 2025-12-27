//DAOUsuari.cxx
#include "DAOUsuari.hxx"
#include "connexioBD.hxx"
#include <odb/transaction.hxx>
using namespace std;
void DAOUsuari::inserta(const usuari& u)
{
	odb::transaction t(db->begin());
	shared_ptr<usuari> ptr(new usuari(u));
	db->persist(ptr);
	t.commit();
}
void DAOUsuari::esborra(const string& username)
{
	odb::transaction t(db->begin());
	db->erase<usuari>(username);
	t.commit();
}
DAOUsuari::DAOUsuari()
{
	// Obtenim la connexió a la base de dades des de la classe singleton connexio
	db = connexioBD::getInstance().getDB();
}

//MÉS OPERACIONS...