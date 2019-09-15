#include "matematica.hpp"

class Cilindro {
    protected:
    Ponto base;
    Vetor normal;
    double raio;
    double altura;

    public:
    Cilindro(Ponto base, Vetor normal, double raio, double altura) {
        this->base = base;
        this->normal = normal;
        this->raio = raio;
        this->altura = altura;
    }

    Ponto *getBase() {
        return &this->base;
    }

    Vetor *getNormal() {
        return &this->normal;
    }

    double getRaio() {
        return this->raio;
    }

    double getAltura() {
        return this->altura;
    }

};