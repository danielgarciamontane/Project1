#include "PlanGo.hxx"
#include <stdexcept>

using namespace std;

PlanGo* PlanGo::_instancia = nullptr;
PlanGo::PlanGo() : _descompte(0.0f) {}


PlanGo& PlanGo::getInstance() {
    if (_instancia == nullptr) {
        _instancia = new PlanGo();
    }
    return *_instancia;
}

float PlanGo::getDescompte() const {
    return _descompte;
}

void PlanGo::setDescompte(float d) {
    if (d < 0.0f || d > 1.0f) {
        throw invalid_argument("El descompte ha d'estar entre 0.0 i 1.0");
    }
    _descompte = d;
}