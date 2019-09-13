#include<iostream>
#include<math.h>
#include "Ponto.cpp"
using namespace std;

class Vetor: public Ponto {
    public:
    Vetor(): Ponto() {}
    Vetor(double x, double y, double z) : Ponto(x,y,z){}

    Vetor *soma(Vetor vetor) {
        double XNovo, YNovo, ZNovo;
        XNovo = this->x + vetor.getX();
        YNovo = this->y + vetor.getY();
        ZNovo = this->z + vetor.getZ();
        Vetor *resultado = new Vetor(XNovo, YNovo, ZNovo);
        return resultado;
    }

    double produtoEscalar(Vetor vetor){
        double resultado;
        resultado = (this->x*vetor.getX()) + (this->y*vetor.getY()) + (this->z*vetor.getZ());
        return resultado;
    }

    Vetor *multEscalar(double escalar) {  //Multiplicaçao de um vetor por um escalar
        double novoX, novoY, novoZ;
        novoX = this->x*escalar;
        novoY = this->y*escalar;
        novoZ = this->z*escalar;
        Vetor *resultado = new Vetor(novoX, novoY, novoZ);
        return resultado;
    }

    double calcularNorma() {
        double norma = sqrt(this->produtoEscalar(*this));
        return norma;
    }

    Vetor *normalizar() {
        double norma = this->calcularNorma();
        Vetor *novoVetor = this->multEscalar(1/norma);
        return novoVetor;
    }
    
    void printCoordenadas() {
        cout << "Vetor - X:" << this->x <<"; Y:" << this->y << "; Z:" << this->z << "\n";
    }

    Vetor operator + (Vetor const &obj) { 
         Vetor res; 
         res.x = x + obj.x; 
         res.y = y + obj.y;
         res.z = z + obj.z;
         return res; 
    }
};