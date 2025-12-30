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
#include "../CapaDeDomini/CtrlReservarActivitat.hxx"
#include "../CapaDeDomini/CtrlConsultarReserves.hxx"
#include "../CapaDeDomini/CtrlConsultarExperiencies.hxx"
#include "../CapaDeDomini/CtrlConsultaNovetats.hxx"
#include "../CapaDeDomini/CtrlConsultaMesReservades.hxx"


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
                    std::cout << "Selecciona una opció: ";
                    std::cin >> opcioReserves;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    switch (opcioReserves) {
                    case 1:
						reservarEscapada();
                        break;
                    case 2:
                        reservarActivitat();
                        break;
                    case 3:
						consultarReserves();
                        break;
                    case 0:
                        sortir = true;
                        std::cout << "\nAdéu! Gràcies per utilitzar PlanGo.\n";
                    break;                    default:
                        std::cout << "Opció no vàlida.\n";
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
						consultarExperiencies();
                        break;
                    case 2:
						consultarNovetats();
                        break;
                    case 3:
                        consultaMesReservades();
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

void CapaDePresentacio::reservarActivitat() {
    std::cout << "--- RESERVAR ACTIVITAT ---\n\n";
    try {
        CtrlReservarActivitat ctrl;
        DTOExperiencia dto;
        string nomActivitat;
        cin >> nomActivitat;
        dto = ctrl.consultarActivitat(nomActivitat);
        cout << "Informació de l'activitat:\n";
        cout << "Nom: " << dto.nom << "\n";
        cout << "Descripció: " << dto.descripcio << "\n";
        cout << "Ciutat: " << dto.ciutat << "\n";
        cout << "Places: " << dto.maxPlaces << "\n";
        cout << "Preu: " << dto.preu << " €\n";
        cout << "Data alta: " << dto.dataAlta << "\n";
        cout << "Durada: " << dto.durada << " hores\n";
        cout << "Introdueix el nombre de persones que volen realitzar l'activitat: ";
        int numPersones;
        cin >> numPersones;
        if (numPersones > dto.maxPlaces) {
            throw std::runtime_error("No hi ha places suficients per a l'activitat.");
        }
        char siono;
        std::cout << "Vols continuar amb la reserva? (S/N)\n";
        std::cin >> siono;
        if (siono == 'S') {
            float preu = ctrl.reservarActivitat(_usuariActual, nomActivitat);
            std::cout << "Reserva realitzada correctament. Preu total: " << preu << " €\n";
        }
    }
    catch (const std::exception& e) {
        std::cout << "\n? Error en reservar activitat: " << e.what() << "\n";
    }
}

void CapaDePresentacio::consultarReserves() {
    std::cout << "--- CONSULTAR RESERVES ---\n\n";
    try {
        DTOLlistaReserves dto;
        CtrlConsultarReserves ctrl;
        dto = ctrl.consultarReservesUsuari(_usuariActual);
		std::cout << "Total pagat en totes les reserves: " << dto.totalPagat << " €\n\n";
        std::cout << " **Escapades**" << "\n";
        for (const auto& reserva : dto.llistaReserves) {
            if (reserva.experienciaReservada.tipusExp == "Escapada") {
                std::cout << "ID Reserva: " << reserva.idReserva << "\n";
                std::cout << "Nom: " << reserva.experienciaReservada.nom << "\n";
                std::cout << "Descripció: " << reserva.experienciaReservada.descripcio << "\n";
                std::cout << "Ciutat: " << reserva.experienciaReservada.ciutat << "\n";
                std::cout << "Preu total: " << reserva.preuTotal << " €\n";
                std::cout << "Hotel: " << reserva.experienciaReservada.hotel << "\n";
                std::cout << "Nº nits: " << reserva.experienciaReservada.numNits << "\n";
            }
        }
        for (const auto& reserva : dto.llistaReserves) {
            if (reserva.experienciaReservada.tipusExp == "Activitat") {
                std::cout << "ID Reserva: " << reserva.idReserva << "\n";
                std::cout << "Nom: " << reserva.experienciaReservada.nom << "\n";
                std::cout << "Descripció: " << reserva.experienciaReservada.descripcio << "\n";
                std::cout << "Ciutat: " << reserva.experienciaReservada.ciutat << "\n";
                std::cout << "Preu total: " << reserva.preuTotal << " €\n";
                std::cout << "Durada: " << reserva.experienciaReservada.durada << " hores\n";
            }
        }
    }
    catch (const std::exception& e) {
        std::cout << "\n? Error en consultar reserves: " << e.what() << "\n";
    }
}

void CapaDePresentacio::consultarExperiencies() {
    std::cout << "--- CONSULTAR EXPERIENCIES ---\n\n";
    try {
        std::string ciutat;
		int numPlaces;
        std::cout << "Introdueix la ciutat per consultar les experiències disponibles: ";
        std::getline(std::cin, ciutat);
        std::cout << "Introdueix el nombre mínim de places disponibles: ";
        cin >> numPlaces;
        CtrlConsultarExperiencies ctrl;
        std::vector<DTOExperiencia> experiencies = ctrl.consultarExperienciesPerCiutat(ciutat, numPlaces);
        if (experiencies.empty()) {
            std::cout << "No hi ha experiències disponibles a la ciutat de " << ciutat << ".\n";
        }
        else {
            std::cout << "**Escapades** " << ciutat << ":\n";
            for (const auto& exp : experiencies) {
                if (exp.tipusExp != "Escapada") continue;
                std::cout << "Nom: " << exp.nom << "\n";
                std::cout << "Descripció: " << exp.descripcio << "\n";
                std::cout << "Tipus: " << exp.tipusExp << "\n";
                std::cout << "Preu: " << exp.preu << " €\n";
                std::cout << "Data alta: " << exp.dataAlta << "\n\n";
            }
            std::cout << "**Escapades** " << ciutat << ":\n";
            for (const auto& exp : experiencies) {
                if (exp.tipusExp != "Activitat") continue;
                std::cout << "**Activitats** " << ciutat << ":\n";
                std::cout << "Nom: " << exp.nom << "\n";
                std::cout << "Descripció: " << exp.descripcio << "\n";
                std::cout << "Tipus: " << exp.tipusExp << "\n";
                std::cout << "Preu: " << exp.preu << " €\n";
                std::cout << "Data alta: " << exp.dataAlta << "\n\n";
            }
        }
    }
    catch (const std::exception& e) {
        std::cout << "\n? Error en consultar experiències: " << e.what() << "\n";
    }
}

void CapaDePresentacio::consultarNovetats() {
    std::cout << "--- CONSULTAR NOVETATS ---\n\n";
    try {
        int lim = 10;
        CtrlConsultaNovetats ctrl;
        std::vector<DTOExperiencia> novetats = ctrl.consultarNovetats(lim);
        if (novetats.empty()) {
            std::cout << "No hi ha novetats disponibles.\n";
        }
        else {
            int count = 0;
            for (const auto& exp : novetats) {
				if (count++ >= lim) break;
                
                if (exp.tipusExp == "Escapada") {
                    std::cout << "Nom: " << exp.nom << "\n";
                    std::cout << "Descripció: " << exp.descripcio << "\n";
                    std::cout << "Ciutat: " << exp.ciutat << "\n";
                    std::cout << "Preu: " << exp.preu << " €\n";
                    std::cout << "Data alta: " << exp.dataAlta << "\n";
                    std::cout << "Hotel: " << exp.hotel << "\n";
                    std::cout << "Nº nits: " << exp.numNits << "\n\n";
                }
                if (exp.tipusExp == "Activitat") {
                    std::cout << "Nom: " << exp.nom << "\n";
                    std::cout << "Descripció: " << exp.descripcio << "\n";
                    std::cout << "Ciutat: " << exp.ciutat << "\n";
                    std::cout << "Preu: " << exp.preu << " €\n";
                    std::cout << "Data alta: " << exp.dataAlta << "\n";
                    std::cout << "Durada: " << exp.durada << " hores\n\n";
                }

            }
        }
    }
    catch (const std::exception& e) {
        std::cout << "\n? Error en consultar novetats: " << e.what() << "\n";
    }
}

void CapaDePresentacio::consultaMesReservades() {
    std::cout << "--- CONSULTAR MÉS RESERVADES ---\n\n";
    try {
        CtrlConsultaMesReservades ctrl;
        std::vector<DTOExperiencia> escapades = ctrl.consEscMesReservades(5);
        std::vector<DTOExperiencia> activitats = ctrl.consActMesReservades(5);
        std::cout << "**Escapades més reservades**:\n";
        for (const auto& exp : escapades) {
            std::cout << "Nom: " << exp.nom << "\n";
            std::cout << "Descripció: " << exp.descripcio << "\n";
            std::cout << "Ciutat: " << exp.ciutat << "\n";
            std::cout << "Preu: " << exp.preu << " €\n";
            std::cout << "Número de reserves: " << exp.numReserves << "\n";
			std::cout << "Hotel: " << exp.hotel << "\n";
			std::cout << "Nº nits: " << exp.numNits << "\n\n";
        }
        std::cout << "**Activitats més reservades**:\n";
        for (const auto& exp : activitats) {
            std::cout << "Nom: " << exp.nom << "\n";
            std::cout << "Descripció: " << exp.descripcio << "\n";
            std::cout << "Ciutat: " << exp.ciutat << "\n";
            std::cout << "Preu: " << exp.preu << " €\n";
            std::cout << "Número de reserves: " << exp.numReserves << "\n";
			std::cout << "Durada: " << exp.durada << " hores\n\n";
        }
    }
    catch (const std::exception& e) {
        std::cout << "\n? Error en consultar més reservades: " << e.what() << "\n";
    }
}