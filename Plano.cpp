#include "matematica.hpp"

class Plano {
    protected:
    Ponto ponto;
    Vetor normal;

    public:
    Plano(Ponto ponto, Vetor normal) {
        this->ponto = ponto;
        this->normal = normal; 
    }

    Ponto *getPonto() {
        return &this->ponto;
    }

    Vetor *getNormal() {
        return &this->normal;
    }

    bool pertencePlano(Ponto ponto) {
        Vetor *distancia = vetorDistancia(this->ponto, ponto);
        double resultado = *distancia * (this->normal);
        if(resultado == 0)      return true;
        else                    return false;   
    }
};