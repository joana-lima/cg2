#include<iostream>
#include "Vetor.cpp"

Ponto *somaPontoVetor(Ponto ponto, Vetor vetor) {
    double x, y, z;
    x = ponto.getX() + vetor.getX();
    y = ponto.getY() + vetor.getY();
    z = ponto.getZ() + vetor.getZ();
    Ponto *atingido = new Ponto(x,y,z);
    return atingido;
}

Vetor *vetorDistancia(Ponto p1, Ponto p2) {     //(p2 - p1) Vetor que vai de p1 à p2
    Vetor *distancia;
    double x = p2.getX() - p1.getX();
    double y = p2.getY() - p1.getY();
    double z = p2.getZ() - p1.getZ();
    distancia = new Vetor(x,y,z);
    return distancia;
}

list<double> equacaoSegundoGrau(double a, double b, double c) {
    double delta = b*b - 4*a*c;
    double x1, x2;
    list<double> escalares;
    if(delta < 0)
        return escalares;
    else {
        x1 = -b + sqrt(delta)/2*a;
        escalares.push_front(x1);
        if(delta == 0)
            return escalares;
        else {
            x2 = -b - sqrt(delta)/2*a;
            escalares.push_front(x2);
            return escalares;
        }
    }
}