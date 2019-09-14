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

    list<Ponto> intRay(Reta reta) {
        list<Ponto> pontos;
        double temp = this->normal * (*reta.getVetor());
        if(temp == 0) {
            return pontos;
        }
        else {
            Vetor *vetor = vetorDistancia(*reta.getPonto(),this->ponto);
            double numerador = *vetor * this->normal;
            double tInt = numerador/temp;
            pontos.push_front(*reta.pontoAtingido(tInt));
            return pontos;
        }
    }
};