//CapaDePresentacio.cxx
#include "CapaDePresentacio.hxx"
#include <iostream>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "../CapaDeDomini/CtrlIniciSessio.hxx"

CapaDePresentacio* CapaDePresentacio::_instancia = nullptr;

CapaDePresentacio::CapaDePresentacio() : _usuariActual("") {
    locale::global(locale(""));
    wcout.imbue(locale());
    cout.imbue(locale());
}

CapaDePresentacio& CapaDePresentacio::getInstance() {
    if (_instancia == nullptr) {
        _instancia = new CapaDePresentacio();
    }
    return *_instancia;
}

void CapaDePresentacio::executar() {
    int opcio;
    bool sortir = false;

    while (!sortir) {
        if (_usuariActual.empty()) {
            mostrarMenuPrincipal();
            cout << "Selecciona una opció: ";
            cin >> opcio;
            cin.ignore();

            switch (opcio) {
            case 1:
                iniciarSessio();
                break;
            case 0:
                sortir = true;
                cout << "\nAdéu! Gràcies per utilitzar PlanGo.\n";
                break;
            default:
                cout << "\nOpció no vàlida. Torna-ho a intentar.\n";
            }
        }
        
    }
}

void CapaDePresentacio::mostrarMenuPrincipal() {
    cout << "-----------------------------------------\n";
    cout << "-          SISTEMA PLAN-GO                -\n";
    cout << "-    Gestió de Reserves d'Experiències  -\n";
    cout << "------------------------------------------\n\n";
    cout << "  1. Iniciar sessió\n";
    cout << "  2. Registrar-se\n";
    cout << "  3. Veure experiències disponibles\n";
    cout << "  0. Sortir\n\n";
}

void CapaDePresentacio::iniciarSessio() {
    cout << "--- INICIAR SESSIÓ ---\n\n";

    string sobrenom, contrasenya;
    cout << "Username: ";
    getline(cin, sobrenom);
    cout << "Contrasenya: ";
    getline(cin, contrasenya);

    try {
        DTOUsuari usuari = CtrlIniciSessio::obtenirInfoUsuari(sobrenom, contrasenya);
        _usuariActual = sobrenom;
        cout << "\n- Benvingut/da, " << usuari.sobrenomU << "!\n";
    }
    catch (const exception& e) {
        cout << "\n? Error: " << e.what() << "\n";
    }
}