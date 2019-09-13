#include<iostream>
#include<math.h>
#include "Ponto.cpp"

using namespace std;

class Vetor: public Ponto {
    public:
    Vetor(): Ponto() {}
    Vetor(double x, double y, double z) : Ponto(x,y,z){}

    double produtoEscalar(Vetor vetor){
        double resultado;
        resultado = (this->x*vetor.getX()) + (this->y*vetor.getY()) + (this->z*vetor.getZ());
        return resultado;
    }

    Vetor *multEscalar(double escalar) {  //Multiplicaçao de um vetor por um escalar
        double novoX, novoY, novoZ;
        novoX = this->x * escalar;
        novoY = this->y * escalar;
        novoZ = this->z * escalar;
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
    
    void print() {
        cout << "Vetor - X:" << this->x <<"; Y:" << this->y << "; Z:" << this->z << "\n";
    }

    Vetor operator + (Vetor const &obj) { 
        Vetor res; 
        res.x = x + obj.x; 
        res.y = y + obj.y;
        res.z = z + obj.z;
        return res; 
    }

    Vetor operator - (Vetor const &obj) {
        Vetor res;
        res.x = x - obj.x;
        res.y = y - obj.y;
        res.z = z - obj.z;
        return res;
    }

    Vetor *produtoVetorial(Vetor vetor){
        Vetor *vetorUnitI = new Vetor(1.0, 0.0, 0.0);
        Vetor *vetorUnitJ = new Vetor(0.0, 1.0, 0.0);
        Vetor *vetorUnitK = new Vetor(0.0, 0.0, 1.0);

        double xVetor = vetor.getX();
        double yVetor = vetor.getY();
        double zVetor = vetor.getZ();

        Vetor *diagonalPrincipal = new Vetor;
        *diagonalPrincipal = *vetorUnitI->multEscalar(this->y * zVetor) + *vetorUnitJ->multEscalar(this->z * xVetor) + *vetorUnitK->multEscalar(this->x * yVetor);
        Vetor *diagonalSecundaria = new Vetor;
        *diagonalSecundaria = *vetorUnitK->multEscalar(this->y * xVetor) + *vetorUnitI->multEscalar(this->z * yVetor) + *vetorUnitJ->multEscalar(this->x * zVetor);
        Vetor *resultado = new Vetor(diagonalPrincipal->getX() - diagonalSecundaria->getX(), diagonalPrincipal->getY() - diagonalSecundaria->getY(), diagonalPrincipal->getZ() - diagonalSecundaria->getZ());
        
        return resultado;
    }
};