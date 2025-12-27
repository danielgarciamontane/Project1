#pragma once
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

	// Mètodes auxiliars
	void mostrarMenuPrincipal();

	string _usuariActual;
	static CapaDePresentacio* _instancia;
};