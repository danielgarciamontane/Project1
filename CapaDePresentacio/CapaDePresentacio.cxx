//CapaDePresentacio.cxx
#include "CapaDePresentacio.hxx"
#include <iostream>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "../CapaDeDomini/CtrlIniciSessio.hxx"
#include "../CapaDeDomini/CtrlTancaSessio.hxx"
#include "../CapaDeDomini/CtrlRegistraUsuari.hxx"
#include "../CapaDeDades/DAOUsuari.hxx"
#include "../CapaDeDomini/CtrlConsultaUsuari.hxx"
#include "../CapaDeDomini/CtrlModificaUsuari.hxx"
#include "../CapaDeDomini/CtrlEsborraUsuari.hxx"
#include "../CapaDeDomini/CtrlReservaEscapada.hxx"

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
            case 2:
                registrarUsuari();
                break;
            case 0:
                sortir = true;
                cout << "\nAdéu! Gr�cies per utilitzar PlanGo.\n";
                break;
            default:
                cout << "\nOpció no v�lida. Torna-ho a intentar.\n";
            }
        }
        else {
            // *** Menú quan hi ha sessi� iniciada ***
            mostrarMenuSessioIniciada();
            std::cout << "Selecciona una opció: ";
            if (!(std::cin >> opcio)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (opcio) {
            case 1: {
                int opcioUsuari = -1;
                while (opcioUsuari != 0) {
                    mostrarMenuGestioUsuari();
                    std::cout << "Selecciona una opció: ";
                    std::cin >> opcioUsuari;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    switch (opcioUsuari) {
                    case 1:
                        consultarUsuari();
                        break;
                    case 2:
						modificarUsuari();
                        break;
                    case 3:
						esborraUsuari();
                        break;
                    case 4:
                        tancarSessio();
                        opcioUsuari = 0; // salir del submenú
                        break;
                    case 0:
                        sortir = true;
                        std::cout << "\nAd�u! Gràcies per utilitzar PlanGo.\n";
                        break;
                    default:
                        std::cout << "Opció no vàlida.\n";
                    }
                }
                break;
            }

            case 2: {
                int opcioReserves = -1;
                while (opcioReserves != 0) {
                    mostrarMenuGestioReserves();
                    std::cout << "Selecciona una opci�: ";
                    std::cin >> opcioReserves;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    switch (opcioReserves) {
                    case 1:
						reservarEscapada();
                        break;
                    case 2:
                        std::cout << "Reservar activitat (pendent)\n";
                        break;
                    case 3:
                        std::cout << "Visualitzar reserves (pendent)\n";
                        break;
                    case 0:
                        sortir = true;
                        std::cout << "\nAd�u! Gr�cies per utilitzar PlanGo.\n";
                    break;                    default:
                        std::cout << "Opci� no v�lida.\n";
                    }
                }
                break;
            }

            case 3: {
                int opcioConsultes = -1;
                while (opcioConsultes != 0) {
                    mostrarMenuConsultes();
                    std::cout << "Selecciona una opci�: ";
                    std::cin >> opcioConsultes;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    switch (opcioConsultes) {
                    case 1:
                        std::cout << "Consulta experiencies (pendent)\n";
                        break;
                    case 2:
                        std::cout << "Consulta novetats (pendent)\n";
                        break;
                    case 3:
                        std::cout << "Consulta m�s reservades (pendent)\n";
                        break;
                    case 0:
                        sortir = true;
                        std::cout << "\nAdéu! Gr�cies per utilitzar PlanGo.\n";
                        break;
                    default:
                        std::cout << "Opció no vàlida.\n";
                    }
                }
                break;
            }

            case 4:
                tancarSessio(); // <-- implementar a sota
                break;
            case 0:
                sortir = true;
                std::cout << "\nAd�u! Gr�cies per utilitzar PlanGo.\n";
                break;
            default:
                std::cout << "\nOpci� no v�lida. Torna-ho a intentar.\n";
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
    cout << "  3. Consultes\n";
    cout << "  0. Sortir\n\n";
}


void CapaDePresentacio::mostrarMenuSessioIniciada() {
    std::cout << "-----------------------------------------\n";
    std::cout << "-           Sessio iniciada             -\n";
    std::cout << "-----------------------------------------\n\n";
    std::cout << " Usuari: " << _usuariActual << "\n\n";
    std::cout << "  1. Gestio usuaris\n";
    std::cout << "  2. Gestio reserves\n";
    std::cout << "  3. Consultes\n";
    std::cout << "  4. Tancar sessio\n";
    std::cout << "  0. Sortir\n\n";
}
void CapaDePresentacio::mostrarMenuGestioUsuari() {
    std::cout << "-----------------------------------------\n";
    std::cout << "-           Gestio Usuari             -\n";
    std::cout << "-----------------------------------------\n\n";
    std::cout << " Usuari: " << _usuariActual << "\n\n";
    std::cout << "  1. Consulta usuari\n";
    std::cout << "  2. Modifica usuari\n";
    std::cout << "  3. Esborra usuari\n";
    std::cout << "  4. Tancar sessio\n";
    std::cout << "  0. Sortir\n\n";
}
void CapaDePresentacio::mostrarMenuGestioReserves() {
    std::cout << "-----------------------------------------\n";
    std::cout << "-         Gestio Reserves             -\n";
    std::cout << "-----------------------------------------\n\n";
    std::cout << " Usuari: " << _usuariActual << "\n\n";
    std::cout << "  1. Reservar escapada\n";
    std::cout << "  2. Reservar activitat\n";
    std::cout << "  3. Visualtizar reserves\n";
    std::cout << "  0. Sortir\n\n";
}
void CapaDePresentacio::mostrarMenuConsultes() {
    std::cout << "-----------------------------------------\n";
    std::cout << "-              Consultes               -\n";
    std::cout << "-----------------------------------------\n\n";
    std::cout << "  1. Consulta experiencies \n";
    std::cout << "  2. Consulta novetats\n";
    std::cout << "  3. Consulta m�s reservades \n";
    std::cout << "  0. Sortir\n\n";
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

void CapaDePresentacio::tancarSessio() {
    try {
        CtrlTancaSessio ctrl;
        bool confirma = ctrl.tancarSessio(_usuariActual);
        if (confirma) _usuariActual.clear();
    }
    catch (const std::exception& e) {
        std::cout << "\n? Error en tancar sessio: " << e.what() << "\n";
    }
}


void CapaDePresentacio::registrarUsuari() {
    std::cout << "--- REGISTRAR USUARI ---\n\n";

    std::string nomU, sobrenomU, contrasenyaU, correuU, edatStr;
    int edatU = 0;

    std::cout << "Nom complet: ";
    std::getline(std::cin, nomU);

    std::cout << "Sobrenom (username): ";
    std::getline(std::cin, sobrenomU);

    std::cout << "Contrasenya: ";
    std::getline(std::cin, contrasenyaU);

    std::cout << "Correu electronic: ";
    std::getline(std::cin, correuU);

    std::cout << "Edat: ";
    std::getline(std::cin, edatStr);
    try {
        edatU = std::stoi(edatStr);
    }
    catch (...) {
        std::cout << "\n? Error: L'edat ha de ser un enter valid.\n";
        return;
    }

    try {
        CtrlRegistraUsuari ctrl;
        ctrl.registrarUsuari(nomU, sobrenomU, contrasenyaU, correuU, edatU);
        std::cout << "\nUsuari registrat amb �xit\n";
    }
    catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }
}

void CapaDePresentacio::consultarUsuari() {
    std::cout << "--- CONSULTAR USUARI ---\n\n";
    try {
        DTOUsuari dto;
        CtrlConsultaUsuari ctrl;
        dto = ctrl.consultarUsuari(_usuariActual);
        std::cout << "Informaci� de l'usuari:\n";
        std::cout << "Sobrenom: " << dto.sobrenomU << "\n";
        std::cout << "Nom complet: " << dto.nomComplet << "\n";
        std::cout << "Correu electrònic: " << dto.email << "\n";
        std::cout << "Edat: " << dto.edat << "\n";
        std::cout << "Número de reserves: " << dto.numReserves << "\n\n";
    }
    catch (const std::exception& e) {
        std::cout << "\n? Error en consultar usuari: " << e.what() << "\n";
    }
}

void CapaDePresentacio::modificarUsuari() {
    std::cout << "--- MODIFICAR USUARI ---\n\n";
	DTOUsuari dto;
    try {
        CtrlModificaUsuari ctrl;
        dto = ctrl.consultarUsuari(_usuariActual);
    }
    catch (const std::exception& e) {
        std::cout << "\n? Error en consultar usuari: " << e.what() << "\n";
        return;
    }
    std::string nouNomComplet, nouEmail, novaEdatStr;
    int novaEdat = dto.edat;
    std::cout << "Nou nom complet (actual: " << dto.nomComplet << "): ";
    std::getline(std::cin, nouNomComplet);
    if (nouNomComplet.empty()) nouNomComplet = dto.nomComplet;
    std::cout << "Nou correu electrònic (actual: " << dto.email << "): ";
    std::getline(std::cin, nouEmail);
    if (nouEmail.empty()) nouEmail = dto.email;
    std::cout << "Nova edat (actual: " << dto.edat << "): ";
    std::getline(std::cin, novaEdatStr);
    if (!novaEdatStr.empty()) {
        try {
            novaEdat = std::stoi(novaEdatStr);
        }
        catch (...) {
            std::cout << "\n? Error: L'edat ha de ser un enter valid.\n";
            return;
        }
    }
    try {
        CtrlModificaUsuari ctrlModifica;
        DTOUsuari updatedDto = ctrlModifica.modificaUsuari(_usuariActual, nouNomComplet, nouEmail, novaEdat);
        std::cout << "\nUsuari modificat amb èxit:\n";
        std::cout << "Sobrenom: " << updatedDto.sobrenomU << "\n";
        std::cout << "Nom complet: " << updatedDto.nomComplet << "\n";
        std::cout << "Correu electr�ènic: " << updatedDto.email << "\n";
        std::cout << "Edat: " << updatedDto.edat << "\n\n";
    }
    catch (const std::exception& e) {
        std::cout << "\n? Error en modificar usuari: " << e.what() << "\n";
	}
}

void CapaDePresentacio::esborraUsuari() {
    std::cout << "--- ESBORRAR USUARI ---\n\n";
    std::string contrasenya;
    std::cout << "Per confirmar has d'entrar la contrasenya: ";
    std::cout << "Contrasenya: ";
    std::getline(std::cin, contrasenya);
    std::cout << "Vols confirmar l'esborrar (S/N): ";
    char confirmacio;
    std::cin >> confirmacio;
    if (confirmacio == 'S') {

        try {
            CtrlEsborraUsuari ctrl;
            ctrl.esborraUsuari(_usuariActual, contrasenya);
            std::cout << "Usuari esborrat correctament.\n";
            _usuariActual.clear();
        }
        catch (const std::exception& e) {
            std::cout << "\n? Error en esborrar usuari: " << e.what() << "\n";
        }
    }
    else {
        std::cout << "Esborrat d'usuari cancel·lat.\n";
    }
}

void CapaDePresentacio::reservarEscapada() {
    std::cout << "--- RESERVAR ESCAPADA ---\n\n";
    try {
        CtrlReservaEscapada ctrl;
        DTOExperiencia dto;
        string nomEscapada;
        cin >> nomEscapada;

        dto = ctrl.consultarEscapada(nomEscapada);
        cout << "Informació de l'escapada:\n";
        cout << "Nom: " << dto.nom << "\n";
        cout << "Descripció: " << dto.descripcio << "\n";
        cout << "Ciutat: " << dto.ciutat << "\n";
        cout << "Hotel: " << dto.hotel << "\n";
        cout << "Nº nits: " << dto.numNits << "\n";
        cout << "Preu per persona: " << dto.preu << " €\n";


        // 3. Número de plazas
        char siono;
        std::cout << "Vols continuar amb la reserva? (S/N)\n";
        std::cin >> siono;

        if (siono == 'S') {
            float preu = ctrl.reservarEscapada(_usuariActual, nomEscapada);
        }
    }
    catch (const std::exception& e) {
        std::cout << "\n? Error en reservar escapada: " << e.what() << "\n";
	}
}