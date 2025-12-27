#pragma once
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "usuari.hxx"
using namespace std;
using namespace boost::gregorian;
class DTOUsuari
{
public:
	DTOUsuari() {}
	//constructora que rep un objecte usuari
	DTOUsuari(usuari& u);
	string get_username();
	string get_nomcomplet();
	date get_data_naixement();
private:
	string _username = "";
	string _nom = "";
	date _data_naixement;
};