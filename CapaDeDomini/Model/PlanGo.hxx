#pragma once
#include <odb/core.hxx>
#include <string>

using namespace std;

#pragma db object
class PlanGo {
public:

    static PlanGo& getInstance();
    float getDescompte() const;
    void setDescompte(float d);

private:
    friend class odb::access;

    PlanGo();

    #pragma db member(_descompte) check("_descompte >= 0.0 AND _descompte <= 1.0")
    float _descompte;

    // Instància única del singleton
    static PlanGo* _instancia;
};