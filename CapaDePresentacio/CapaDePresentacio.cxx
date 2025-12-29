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
#include "../CtrlModificaUsuari.hxx"
#include "../CtrlEsborraUsuari.hxx"
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
            cout << "Selecciona una opcio: ";
            cin >> opcio;
            cin.ignore();

            switch (opcio) {
            case 1:
                iniciarSessio();
                break;
            case 2:
                registrarUsuari();
                break;
			case 3: 
                executarConsultes();
                break;
            case 0:
                sortir = true;
                cout << "\nAdéu! Gràcies per utilitzar PlanGo.\n";
                break;
            default:
                cout << "\nOpció no vàlida. Torna-ho a intentar.\n";
            }
        }
        else {
            // *** Menu quan hi ha sessio iniciada ***
            mostrarMenuSessioIniciada();
            std::cout << "Selecciona una opcio: ";
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
                    std::cout << "Selecciona una opcio: ";
                    std::cin >> opcioUsuari;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    switch (opcioUsuari) {
                    case 1:
						consultarUsuari();
                        break;
                    case 2:
                        modificaUsuari();
                        break;
                    case 3:
                        esborraUsuari();//Falta la parte de las reservas
                        break;
                    case 4:
                        tancarSessio();
                        opcioUsuari = 0; // salir del submenu
                        break;
                    case 0:
                        break;
                    default:
                        std::cout << "Opcio no valida.\n";
                    }
                }
                break;
            }

            case 2: {
                int opcioReserves = -1;
                while (opcioReserves != 0) {
                    mostrarMenuGestioReserves();
                    std::cout << "Selecciona una opció: ";
                    std::cin >> opcioReserves;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    switch (opcioReserves) {
                    case 1:
                        std::cout << "Reservar escapada (pendent)\n";
                        break;
                    case 2:
                        std::cout << "Reservar activitat (pendent)\n";
                        break;
                    case 3:
                        std::cout << "Visualitzar reserves (pendent)\n";
                        break;
                    case 0:
                    break;                   
                    default:
                        std::cout << "Opcio no valida.\n";
                    }
                }
                break;
            }

            case 3:
                executarConsultes();
                break;

            case 4:
                tancarSessio(); // <-- implementar a sota
                break;
            case 0:
                sortir = true;
                std::cout << "\nAdéu! Gràcies per utilitzar PlanGo.\n";
                break;
            default:
                std::cout << "\nOpció no vàlida. Torna-ho a intentar.\n";
            }
        }
    }
}

void CapaDePresentacio::mostrarMenuPrincipal() {
    cout << "-----------------------------------------\n";
    cout << "-          SISTEMA PLAN-GO                -\n";
    cout << "-    Gestio de Reserves d'Experiencies  -\n";
    cout << "------------------------------------------\n\n";
    cout << "  1. Iniciar sessio\n";
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
    std::cout << "  3. Consulta més reservades \n";
    std::cout << "  0. Sortir\n\n";
}
void CapaDePresentacio::executarConsultes() {
    int opcioConsultes = -1;
    while (opcioConsultes != 0) {
        mostrarMenuConsultes();
        cout << "Selecciona una opció: ";
        cin >> opcioConsultes;
        cin.ignore();

        switch (opcioConsultes) {
        case 1:
            cout << "Consulta experiencies (pendent)\n";
            break;
        case 2:
            cout << "Consulta novetats (pendent)\n";
            break;
        case 3:
            cout << "Consulta més reservades (pendent)\n";
            break;
        case 0:
            break;
        default:
            cout << "Opció no vàlida.\n";
        }
    }
}
void CapaDePresentacio::iniciarSessio() {
    cout << "--- INICIAR SESSIO ---\n\n";

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
        std::cout << "\nUsuari registrat amb exit\n";
    }
    catch (const std::exception& e) {
        std::cout<< e.what() << "\n";
    }
}

void CapaDePresentacio::consultarUsuari() {
    std::cout << "--- CONSULTAR USUARI ---\n\n";
    try {
        DTOUsuari dto;
        CtrlConsultaUsuari ctrl;
        dto = ctrl.consultarUsuari(_usuariActual);
        std::cout << "Informació de l'usuari:\n";
        std::cout << "Sobrenom: " << dto.sobrenomU << "\n";
        std::cout << "Nom complet: " << dto.nomComplet << "\n";
        std::cout << "Correu electronic: " << dto.email << "\n";
        std::cout << "Edat: " << dto.edat << "\n";
        std::cout << "Numero de reserves: " << dto.numReserves << "\n\n";
    }
    catch (const std::exception& e) {
        std::cout << "\n? Error en consultar usuari: " << e.what() << "\n";
    }
}
void CapaDePresentacio::modificaUsuari() {
    std::cout << "--- MODIFICAR USUARI ---\n\n";

    try {
        CtrlConsultaUsuari ctrlConsulta;
        DTOUsuari dto = ctrlConsulta.consultarUsuari(_usuariActual);

        std::cout << "Dades actual:\n";
        std::cout << "Nom complet: " << dto.nomComplet << "\n";
        std::cout << "Correu electronic: " << dto.email << "\n";
        std::cout << "Edat: " << dto.edat << "\n\n";

        std::string nouNom, nouEmail, liniaEdat;
        int novaEdat = -1;

        std::cout << "Nou nom complet (<Intro> per mantenir): ";
        std::getline(std::cin, nouNom);

        std::cout << "Nou correu electronic (<Intro> per mantenir): ";
        std::getline(std::cin, nouEmail);

        std::cout << "Nova edat (<Intro> per mantenir): ";
        std::getline(std::cin, liniaEdat);

        if (!liniaEdat.empty()) {
            try {
                novaEdat = std::stoi(liniaEdat);
            }
            catch (...) {
                throw std::runtime_error("L'edat ha de ser un nombre valid");
            }
        }

        CtrlModificaUsuari ctrl(_usuariActual);
        ctrl.modificaUsuari(nouNom, nouEmail, novaEdat);

        std::cout << "\nUsuari modificat correctament.\n";
    }
    catch (const std::exception& e) {
        std::cout << "\n? Error en modificar usuari: " << e.what() << "\n";
    }
}
void CapaDePresentacio::esborraUsuari() {
    std::cout << "--- ESBORRAR USUARI ---\n\n";

    try {
        std::string contrasenya;
        std::cout << "Introdueix la contrasenya: ";
        std::getline(std::cin, contrasenya);
        char confirmacio;
        std::cout << "Vols confirmar l'esborrat? (S/N): ";
        std::cin >> confirmacio;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (confirmacio != 'S' && confirmacio != 's') {
            std::cout << "Esborrat cancel�lat.\n";
            return;
        }
        CtrlEsborrarUsuari ctrl(_usuariActual);
        ctrl.esborraUsuari(contrasenya);

        std::cout << "Usuari esborrat correctament.\n";
        _usuariActual.clear();
    }
    catch (const std::exception& e) {
        std::cout << "\n? Error en esborrar usuari: " << e.what() << "\n";
    }
}

