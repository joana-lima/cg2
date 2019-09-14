//Bilioteca para calculos matematicos
#ifndef MATEMATICA_H_INCLUDED
#define MATEMATICA_H_INCLUDED

#include<iostream>
#include "matematica.cpp"

Ponto *somaPontoVetor(Ponto ponto, Vetor vetor);

Vetor *vetorDistancia(Ponto p1, Ponto p2);

list<double> equacaoSegundoGrau(double a, double b, double c);

#endif