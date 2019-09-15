#include "matematica.cpp"

class Cone {
    protected:
    Ponto base;
    Ponto vertice;
    Vetor normal;
    double raio;
    double altura;


    public:
    Cone(Ponto base, Vetor normal, double raio, double altura) {
        this->base = base;
        this->normal = normal;
        this->raio = raio;
        this->altura = altura;
        this->vertice = *somaPontoVetor(this->base, *(this->normal.multEscalar(this->altura)));
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

    Ponto getVertice() {
        return this->vertice;
    }

    /*Implementar
    double getCossenoGeratrz()*/

};