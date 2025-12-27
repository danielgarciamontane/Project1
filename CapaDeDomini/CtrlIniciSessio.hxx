#pragma once
#include <string>
#include "DTOs/DTOUsuari.hxx"
using namespace std;

class CtrlIniciSessio {
public:
	// Mètode per obtenir la informació de l'usuari després d'un inici de sessió correcte
	static DTOUsuari obtenirInfoUsuari(const string& username, const string& contrasenya);
};