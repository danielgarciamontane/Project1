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

	// Mètodes auxiliars
	void mostrarMenuPrincipal();
	void mostrarMenuSessioIniciada();

	string _usuariActual;
	static CapaDePresentacio* _instancia;
};