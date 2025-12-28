#pragma once
#include <string>
#include <ostream>
#include <odb/core.hxx>

#pragma db object polymorphic
class Experiencia {
public:
    Experiencia() = default;
    Experiencia(const std::string& nom, double preu);

    virtual ~Experiencia() = default;

    // Métodos polimórficos
    virtual std::string get_tipus() const = 0;
    virtual void print_info_detalls(std::ostream& os) const = 0;
    void print_info(std::ostream& os) const;

private:
    friend class odb::access;   

#pragma db id auto
    unsigned long id;

    std::string nom;
    double preu;
};
