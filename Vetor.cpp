#include<iostream>
#include "Ponto.cpp"
using namespace std;

class Vetor: public Ponto {
    public:

    Vetor(double x, double y, double z) : Ponto(x,y,z){}

    Vetor *soma(Vetor vetor) {

        double XNovo, YNovo, ZNovo;
        XNovo = this->x + vetor.getX();
        YNovo = this->y + vetor.getY();
        ZNovo = this->z + vetor.getZ();
        Vetor *resultado = new Vetor(XNovo, YNovo, ZNovo);
        return resultado;
    }

    void printCoordenadas() {
        cout << this->x << endl;
        cout << this->y << endl;
        cout << this->z << endl;
    }
};