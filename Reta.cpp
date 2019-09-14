#include "matematica.hpp"

class Reta {
    protected:
    Ponto ponto;
    Vetor vetor;

    public:
    Reta(Ponto ponto, Vetor vetor) {
        this->ponto = ponto;
        this->vetor = vetor;
    }

    Ponto *getPonto() {
        return &this->ponto;
    }

    Vetor *getVetor() {
        return &this->vetor;
    }

    void print() {
        cout << "----Reta----" << endl;
        ponto.print();
        vetor.print();
    }

    Ponto *pontoAtingido(double k) {
        Ponto *atingido = somaPontoVetor(this->ponto, *(this->vetor.multEscalar(k)));
        return atingido;
    }
};