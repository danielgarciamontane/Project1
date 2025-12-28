#include "CtrlTancaSessio.hxx"
#include "../CapaDeDades/DAOUsuari.hxx"
#include "Model/Usuari.hxx"
#include <stdexcept>


static char llegirConfirmacioSN(std::istream& in, std::ostream& out) {
    while (true) {
        out << "Vols tancar la sessio? (S/N): " << std::flush;
        std::string linia;
        if (!std::getline(in, linia)) {
            // EOF o error d'entrada
            throw std::runtime_error("No s'ha pogut llegir la confirmacio.");
        }

        // Treu espais i normalitza
        linia.erase(std::remove_if(linia.begin(), linia.end(), ::isspace), linia.end());
        if (linia.empty()) {
            // L’usuari ha premut <Intro> sense resposta; repetim
            continue;
        }

        char c = static_cast<char>(std::toupper(static_cast<unsigned char>(linia.front())));
        if (c == 'S' || c == 'N') return c;

        out << "Resposta invalida. Si us plau, respon amb 'S' o 'N'.\n";
    }
}


bool CtrlTancaSessio::tancarSessio(const std::string& username) {

	if (username == "") {
		throw std::runtime_error("No hi ha cap usuari logejat.");
	}

    // --- Confirmacio per part de l'usuari ---
    char confirm = llegirConfirmacioSN(std::cin, std::cout);

    if (confirm == 'N') {
        std::cout << "S'ha cancel·lat l'operacio. La sessio continua oberta.\n";
		return false;
    }
    else if (confirm == 'S') {
        std::cout << "Sessio tancada correctament.\n";
		return true;
    }
    else return true;
}