//CapaDePresentacio.hxx
#pragma once
#include <iostream>
#include <string>
using namespace std;
class CapaDePresentacio
{
public:

	static CapaDePresentacio& getInstance();
	void executar();

private:
	
	CapaDePresentacio();

	void iniciarSessio();
	void tancarSessio();
	void registrarUsuari();
	void consultarUsuari();
	void modificaUsuari();
	void esborraUsuari();
	// M�todes auxiliars
	void mostrarMenuPrincipal();
	void mostrarMenuSessioIniciada();
	void mostrarMenuGestioUsuari();
	void mostrarMenuGestioReserves();
	void mostrarMenuConsultes();
	void executarConsultes();
	string _usuariActual;
	static CapaDePresentacio* _instancia;
};