#include "Vetor.cpp"
#include<iostream>

class Reta {
    protected:
    Ponto ponto;
    Vetor vetor;

    public:
    Reta(Ponto ponto, Vetor vetor) {
        this->ponto = ponto;
        this->vetor = vetor;
    }

    Ponto getPonto() {
        return this->ponto;
    }

    Vetor getVetor() {
        return this->vetor;
    }
};