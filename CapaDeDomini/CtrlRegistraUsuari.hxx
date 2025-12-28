#pragma once

#include <string>


class CtrlRegistraUsuari {
	public:
        void registrarUsuari(const std::string& nomU,
            const std::string& sobrenomU,
            const std::string& contrasenyaU,
            const std::string& correuElectronicU,
            int edatU);

};