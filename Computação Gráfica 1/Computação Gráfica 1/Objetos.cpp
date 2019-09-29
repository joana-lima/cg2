#include <iostream>
#include <math.h>
#include <vector>
#include "RenderAPI.h"
//#include <bits/stdc++.h>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Matriz {
    protected:
        vector<vector<double>> matriz = {};
        int linhas;
        int colunas;

    public:
        Matriz(int nLinhas, int nColunas){
            this->linhas = nLinhas;
            this->colunas = nColunas;

            vector<double> linhas;
            vector<vector<double>> linhasComColunas;

            for(int i = 0; i < nLinhas; i++){
                for(int j = 0; j < nColunas; j++){
                    linhas.push_back(0.0);
                };

                linhasComColunas.push_back(linhas);
                linhas.clear();
            };

            this->matriz = linhasComColunas;
        }

        Matriz(vector<vector<double>> matriz){
            this->matriz = matriz;
            this->linhas = matriz.size();
            this->colunas = matriz[0].size();
        }

        void inserirValor(int linha, int coluna, double valor){
            this->matriz[linha, coluna] = {valor};
        }

        double get(int i, int j){
            return matriz[i][j];
        }

        void print(){
            for(int i = 0; i < this->matriz.size(); i++){
                for(int j = 0; j < this->matriz[0].size(); j++){
                    cout << this->matriz[i][j] << " ";
                };
                cout << endl;
            };
        }

        Matriz* produto(Matriz* B){
            Matriz* A = this;

            if(A->colunas != B->linhas){
                cout << "\nNão é permitido multiplicar as matrizes dadas.\n";
                return NULL;
            } else {
                Matriz* C = new Matriz(A->linhas, B->colunas);

                for(int i = 0; i < A->linhas; i++){
                    for(int j = 0; j < B->colunas; j++){
                        for(int k = 0; k < A->colunas; k++){
                            C->matriz[i][j] = C->matriz[i][j] + (A->matriz[i][k] * B->matriz[k][j]);
                        };
                    };
                };
                
                return C;
            }
        }
};

class Cor {
    protected:
        int r;
        int g;
        int b;

    public:
        Cor(){
            this->r = 0;
            this->g = 0;
            this->b = 0;
        }

        Cor(int r, int g, int b){
            this->r = r;
            this->g = g;
            this->b = b;
        }

        int getR(){
            return this->r;
        }

        int getG(){
            return this->g;
        }

        int getB(){
            return this->b;
        }

        void setCor(int r, int g, int b){
            this->r = r;
            this->g = g;
            this->b = b;
        }
};

class Ponto {
    protected:
        int id = 0;
        double x;
        double y;
        double z;
        vector<float> cor;

    public:
        Ponto() {
            this->x = 0;
            this->y = 0;
            this->z = 0;
            this->id++;
        }
        
        Ponto(double x, double y, double z) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->id++;
        }

        int getID() {
            return this->id;
        }

        double getX() {
            return this->x;
        }

        double getY() {
            return this->y;
        }

        double getZ() {
            return this->z;
        }

        void setX(double x) {
            this->x = x;
        }

        void setY(double y) {
            this->y = y;
        }

        void setZ(double z) {
            this->z = z;
        }

        vector<float> getCor() {
            return this->cor;
        }
        
        void setCor(float red, float green, float blue) {
            this->cor = {red, green, blue};
        }

        void print() {
            cout << "Ponto - X:" << this->x <<"; Y:" << this->y << "; Z:" << this->z << endl;
        }
};

class Vetor: public Ponto {
    public:
        Vetor(): Ponto() {}
        Vetor(double x, double y, double z) : Ponto(x,y,z){}

        double produtoEscalar(Vetor vetor){
            double resultado;
            resultado = (this->x*vetor.getX()) + (this->y*vetor.getY()) + (this->z*vetor.getZ());
            return resultado;
        }

        Vetor* multEscalar(double escalar) {  //Multiplicaçao de um vetor por um escalar
            double novoX, novoY, novoZ;
            novoX = this->x * escalar;
            novoY = this->y * escalar;
            novoZ = this->z * escalar;
            Vetor* resultado = new Vetor(novoX, novoY, novoZ);
            return resultado;
        }

        double calcularNorma() {
            double norma = sqrt(this->produtoEscalar(*this));
            return norma;
        }

        Vetor* normalizar() {
            double norma = this->calcularNorma();
            Vetor* novoVetor = this->multEscalar(1/norma);
            return novoVetor;
        }
        
        void print() {
            cout << "Vetor [X:" << this->x <<"; Y:" << this->y << "; Z:" << this->z << "]";// << "\n" << endl;
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

        Vetor elemMult (Vetor obj) {
            Vetor res;
            res.x = x * obj.x;
            res.y = y * obj.y;
            res.z = z * obj.z;
            return res;
        }

        double operator * (Vetor const &obj) {
            double resultado;
            resultado = x*obj.x + y*obj.y + z*obj.z;
            return resultado;
        }

        Vetor* produtoVetorial(Vetor vetor){
            Vetor* vetorUnitI = new Vetor(1.0, 0.0, 0.0);
            Vetor* vetorUnitJ = new Vetor(0.0, 1.0, 0.0);
            Vetor* vetorUnitK = new Vetor(0.0, 0.0, 1.0);

            double xVetor = vetor.getX();
            double yVetor = vetor.getY();
            double zVetor = vetor.getZ();

            Vetor* diagonalPrincipal = new Vetor;
            *diagonalPrincipal = *vetorUnitI->multEscalar(this->y * zVetor) + *vetorUnitJ->multEscalar(this->z * xVetor) + *vetorUnitK->multEscalar(this->x * yVetor);
            Vetor* diagonalSecundaria = new Vetor;
            *diagonalSecundaria = *vetorUnitK->multEscalar(this->y * xVetor) + *vetorUnitI->multEscalar(this->z * yVetor) + *vetorUnitJ->multEscalar(this->x * zVetor);
            Vetor* resultado = new Vetor(diagonalPrincipal->getX() - diagonalSecundaria->getX(), diagonalPrincipal->getY() - diagonalSecundaria->getY(), diagonalPrincipal->getZ() - diagonalSecundaria->getZ());
            
            return resultado;
        }
};

Ponto* somaPontoVetor(Ponto ponto, Vetor vetor) {
    double x, y, z;
    x = ponto.getX() + vetor.getX();
    y = ponto.getY() + vetor.getY();
    z = ponto.getZ() + vetor.getZ();
    Ponto* atingido = new Ponto(x,y,z);
    return atingido;
}

Vetor* vetorDistancia(Ponto p1, Ponto p2) {     //(p2 - p1) Vetor que vai de p1 à p2
    Vetor* distancia;
    double x = p2.getX() - p1.getX();
    double y = p2.getY() - p1.getY();
    double z = p2.getZ() - p1.getZ();
    distancia = new Vetor(x,y,z);
    return distancia;
}

vector<double> equacaoSegundoGrau(double a, double b, double c) {
    double delta = (b*b) - (4*a*c);
    double x1, x2;
    vector<double> escalares;

    if(delta < 0)
        return escalares;
    else {
        x1 = (-b + sqrt(delta))/(2*a);
        escalares.push_back(x1);
        if(delta == 0)
            return escalares;
        else {
            x2 = (-b - sqrt(delta))/(2*a);
            escalares.push_back(x2);
            return escalares;
        }
    }
}

class Reta {
    protected:
        Ponto ponto;
        Vetor vetor;

    public:
        Reta(Ponto ponto, Vetor vetor) {
            this->ponto = ponto;
            this->vetor = *vetor.normalizar();
        }

        Ponto* getPonto() {
            return &this->ponto;
        }

        Vetor* getVetor() {
            return &this->vetor;
        }

        void print() {
            cout << "----Reta----" << endl;
            ponto.print();
            vetor.print();
        }

        Ponto* pontoAtingido(double k) {
            Ponto* atingido = somaPontoVetor(this->ponto, *(this->vetor.multEscalar(k)));
            return atingido;
        }
};

class Observador{
    private:
        Ponto posicao;
        Ponto lookat;
        Ponto viewup;
        Matriz *matriz;

    public:
        Observador(Ponto posicao, Ponto lookat, Ponto viewup){
            this->posicao = posicao;
            this->lookat = lookat;
            this->viewup = viewup;

            Vetor i = this->getI();
            Vetor j = this->getJ();
            Vetor k = this->getK();

            double a = - (*vetorDistancia(*new Vetor(0,0,0),posicao) * i);
            double b = - (*vetorDistancia(*new Vetor(0,0,0),posicao) * j);
            double c = - (*vetorDistancia(*new Vetor(0,0,0),posicao) * k);

            vector<double> primeiraLinha = {i.getX(), i.getY(), i.getZ(), a};
            vector<double> segundalinha  = {j.getX(), j.getY(), j.getZ(), b};
            vector<double> terceiraLinha = {k.getX(), k.getY(), k.getZ(), c};
            vector<double> quartalinha = {0,0,0,1};

            vector<vector<double>> matrizDeTransformacao = {primeiraLinha, segundalinha, terceiraLinha, quartalinha};
            this->matriz = new Matriz(matrizDeTransformacao);
        }

        Ponto* getPosicao(){
            return &posicao;
        }
        
        Vetor getI(){
            return *(*(*vetorDistancia(posicao, viewup)).produtoVetorial(getK())).normalizar();
        }

        Vetor getJ(){
            return *getK().produtoVetorial(getI());
        }

        Vetor getK(){
            return *(*vetorDistancia(lookat, posicao)).normalizar();
        }


        Ponto converte(Ponto ponto){
            vector<vector<double>> pontoAtransformar =  {{ponto.getX()}, {ponto.getY()}, {ponto.getZ()}, {1}};
            Matriz* resultado = matriz->produto(new Matriz(pontoAtransformar));
            return *new Ponto(resultado->get(0,0), resultado->get(1,0), resultado->get(2,0));
        }
};


class Objeto {
    protected:
        static int icrementador;
		int id;
        vector<Ponto> vertices;
        vector<vector<Ponto>> arestas;
        vector<vector<Ponto>> faces;
        bool visibilidade;
        Vetor* material;

    public:
        Objeto() {
            this->vertices = {};
            this->arestas = {};
            this->faces = {};
            this->visibilidade = true;
            this->id = icrementador;
			icrementador++;
        }

        int getId(){
        	return id;
    	}

        void setMaterial(Vetor* material){
            this->material = material;
        }

        virtual void print(){
            cout << "Objeto - ID: " << id <<endl;
            cout << "Visibilidade: ";
            visibilidade ? cout << "true\n" : cout<<"false\n";

            cout << vertices.size() << " Vertices: " << endl;
            for (int i = 0; i < vertices.size(); i++){
                vertices[i].print();
            }
            cout << endl;

            cout << arestas.size() << " Arestas: " << endl << "[\n";
            for (int i = 0; i < arestas.size(); i++) {
                cout << "[" ;
                for(int j = 0; j < arestas[i].size(); j++){
                    cout << " ";
                    arestas[i][j].print();
                    cout << " ";
                }
                cout << "]\n";
            }
            cout << "]" << endl;

            cout << faces.size() << " faces: " << endl << "[\n";
            for (int i = 0; i < faces.size(); i++){
                cout << "[";
                for(int j = 0; j < faces[i].size(); j++){
                    cout << " ";
                    faces[i][j].print();
                }
                cout << "]\n";
            }
            cout << "]" << endl;
            
        }

        bool getVisibilidade(){
            return this->visibilidade;
        }
        
        void setVisibilidade(bool visibilidade){
            this->visibilidade = visibilidade;
        }

        void adicionarVertice(Ponto vertice){
            this->vertices.push_back(vertice);
        }

        void adicionarAresta(Ponto vertice1, Ponto vertice2){
            this->arestas.push_back({vertice1, vertice2});
        }

        void adicionarFace(Ponto vertice1, Ponto vertice2, Ponto vertice3){
            this->faces.push_back({vertice1, vertice2, vertice3});
        }

        vector<Ponto> getVertices(){
            return this->vertices;
        }

        vector<vector<Ponto>> getArestas(){
            return this->arestas;
        }

        vector<vector<Ponto>> getFaces(){
            return this->faces;
        }

        Vetor* getMaterial(){
            return this->material;
        }

		virtual Objeto* transforma(Observador obs) { return 0; }
		virtual Vetor* getNormal(Ponto p) { return 0; }
		virtual vector<Ponto> intRaio(Reta reta) { return {}; }

};

int Objeto::icrementador = 0;

class Plano : public Objeto{
    protected:
        Ponto ponto;
        Vetor normal;

    public:
        Plano(Ponto ponto, Vetor normal) {
            this->ponto = ponto;
            this->normal = normal;
        }

        Ponto* getPonto() {
            return &this->ponto;
        }

        Vetor* getNormal() {
            return &this->normal;
        }

		Vetor* getNormal(Ponto ponto) {
			return &this->normal;
		}

        bool pertencePlano(Ponto ponto) {
            Vetor* distancia = vetorDistancia(this->ponto, ponto);
            double resultado = *distancia * (this->normal);
            if(resultado == 0)      return true;
            else                    return false;   
        }

        vector<Ponto> intRaio(Reta reta) {
            vector<Ponto> pontos;
            double temp = this->normal * (*reta.getVetor());
            if(temp == 0) {
                return pontos;
            }
            else {
                Vetor* vetor = vetorDistancia(*reta.getPonto(),this->ponto);
                double numerador = *vetor * this->normal;
                double tInt = numerador/temp;
                pontos.push_back(*reta.pontoAtingido(tInt));
                return pontos;
            }
        }

        Objeto* transforma(Observador obs){
            return new Plano(obs.converte(ponto), *vetorDistancia(*new Ponto(0,0,0) , obs.converte(normal)));
        }
};

class Triangulo : public Objeto {
    public:
        Ponto ponto1;
        Ponto ponto2;
        Ponto ponto3;
    public:
        Triangulo() : Objeto() {}
        
        Triangulo(Ponto ponto1, Ponto ponto2, Ponto ponto3) {
            this->ponto1 = ponto1;
            this->ponto2 = ponto2;
            this->ponto3 = ponto3;
            this->adicionarVertice(ponto1);
            this->adicionarVertice(ponto2);
            this->adicionarVertice(ponto3);

            this->adicionarAresta(ponto1, ponto2);
            this->adicionarAresta(ponto2, ponto3);
            this->adicionarAresta(ponto3, ponto1);

            this->adicionarFace(ponto1, ponto2, ponto3);
        }

        vector<Ponto> intRaio(Reta raio) {

            Vetor* p1p2 = vetorDistancia(vertices[1], vertices[0]);
            Vetor* p1p3 = vetorDistancia(vertices[2], vertices[0]);
            Vetor* p2p3 = vetorDistancia(vertices[2], vertices[1]);
            Vetor* p3p1 = vetorDistancia(vertices[0], vertices[2]);
            Vetor* n = p1p2->produtoVetorial(*p1p3)->normalizar();

            Plano* planoTriangulo = new Plano(vertices[0], *n);
            vector<Ponto> pontoInt = planoTriangulo->intRaio(raio);

            if(pontoInt.size() == 0){
                return pontoInt;
            };

            Vetor* p1p = vetorDistancia(pontoInt[0], vertices[0]);
            Vetor* p2p = vetorDistancia(pontoInt[0], vertices[1]);
            Vetor* p3p = vetorDistancia(pontoInt[0], vertices[2]);

            Vetor* p1p2xp1p3 = p1p2->produtoVetorial(*p1p3);
            double sE = p1p2->produtoVetorial(*p1p)->produtoEscalar(*p1p2xp1p3);
            double sN = p2p3->produtoVetorial(*p2p)->produtoEscalar(*p1p2xp1p3);
            double sS = p3p1->produtoVetorial(*p3p)->produtoEscalar(*p1p2xp1p3);

            if(sE >= 0 && sN >= 0 && sS >= 0){
                return pontoInt;
            } else {
                pontoInt.clear();
                return pontoInt;
            }
        }

        Vetor* getNormal(Ponto p){
            Vetor* p1p2 = vetorDistancia(vertices[1], vertices[0]);
            Vetor* p1p3 = vetorDistancia(vertices[2], vertices[0]);
            Vetor* normal = p1p2->produtoVetorial(*p1p3)->normalizar();

            return normal;
        }

        Objeto* transforma(Observador obs){
            return new Triangulo(obs.converte(ponto1),obs.converte(ponto2),obs.converte(ponto3));
        }

    
};

class Cubo : public Objeto {
    protected:
        Ponto centro;
        Vetor direcao;
        float largura;

        Triangulo* triangulo1;
        Triangulo* triangulo2;
        Triangulo* triangulo3;
        Triangulo* triangulo4;
        Triangulo* triangulo5;
        Triangulo* triangulo6;
        Triangulo* triangulo7;
        Triangulo* triangulo8;
        Triangulo* triangulo9;
        Triangulo* triangulo10;
        Triangulo* triangulo11;
        Triangulo* triangulo12;

    public:
        Cubo() : Objeto() {}

        Cubo(Ponto centro, float largura, Vetor direcao){
            this->centro = centro;
            this->largura = largura;
            this->direcao = direcao;
            
            double ml = largura/2;  //Meia Largura: ml
            Ponto* p1 = new Ponto(this->centro.getX() - ml, this->centro.getY() + ml, this->centro.getZ() - ml);
            Ponto* p2 = new Ponto(this->centro.getX() - ml, this->centro.getY() + ml, this->centro.getZ() + ml);
            Ponto* p3 = new Ponto(this->centro.getX() + ml, this->centro.getY() + ml, this->centro.getZ() + ml);
            Ponto* p4 = new Ponto(this->centro.getX() + ml, this->centro.getY() + ml, this->centro.getZ() - ml);
            Ponto* p5 = new Ponto(this->centro.getX() - ml, this->centro.getY() - ml, this->centro.getZ() - ml);
            Ponto* p6 = new Ponto(this->centro.getX() - ml, this->centro.getY() - ml, this->centro.getZ() + ml);
            Ponto* p7 = new Ponto(this->centro.getX() + ml, this->centro.getY() - ml, this->centro.getZ() + ml);
            Ponto* p8 = new Ponto(this->centro.getX() + ml, this->centro.getY() - ml, this->centro.getZ() - ml);

            this->adicionarVertice(*p1);
            this->adicionarVertice(*p2);
            this->adicionarVertice(*p3);
            this->adicionarVertice(*p4);
            this->adicionarVertice(*p5);
            this->adicionarVertice(*p6);
            this->adicionarVertice(*p7);
            this->adicionarVertice(*p8);
            
            this->adicionarAresta(*p1, *p2);
            this->adicionarAresta(*p2, *p3);
            this->adicionarAresta(*p3, *p4);
            this->adicionarAresta(*p4, *p1);
            this->adicionarAresta(*p5, *p6);
            this->adicionarAresta(*p6, *p7);
            this->adicionarAresta(*p7, *p8);
            this->adicionarAresta(*p8, *p5);
            this->adicionarAresta(*p1, *p5);
            this->adicionarAresta(*p2, *p6);
            this->adicionarAresta(*p3, *p7);
            this->adicionarAresta(*p4, *p8);

            this->adicionarFace(*p1, *p2, *p3);
            this->adicionarFace(*p1, *p3, *p4);
            this->adicionarFace(*p5, *p7, *p6);
            this->adicionarFace(*p5, *p8, *p7);
            this->adicionarFace(*p1, *p5, *p6);
            this->adicionarFace(*p1, *p6, *p2);
            this->adicionarFace(*p2, *p6, *p7);
            this->adicionarFace(*p2, *p7, *p3);
            this->adicionarFace(*p3, *p7, *p8);
            this->adicionarFace(*p3, *p8, *p4);
            this->adicionarFace(*p4, *p8, *p5);
            this->adicionarFace(*p4, *p5, *p1);

            this->triangulo1 = new Triangulo(*p1, *p2, *p3);
            this->triangulo2 = new Triangulo(*p1, *p3, *p4);
            this->triangulo3 = new Triangulo(*p5, *p7, *p6);
            this->triangulo4 = new Triangulo(*p5, *p8, *p7);
            this->triangulo5 = new Triangulo(*p1, *p5, *p6);
            this->triangulo6 = new Triangulo(*p1, *p6, *p2);
            this->triangulo7 = new Triangulo(*p2, *p6, *p7);
            this->triangulo8 = new Triangulo(*p2, *p7, *p3);
            this->triangulo9 = new Triangulo(*p3, *p7, *p8);
            this->triangulo10 = new Triangulo(*p3, *p8, *p4);
            this->triangulo11 = new Triangulo(*p4, *p8, *p5);
            this->triangulo12 = new Triangulo(*p4, *p5, *p1);
        }

        Ponto getCentro(){
            return this->centro;
        }

        Vetor getDirecao(){
            return this->direcao;
        }

        double getLargura(){
            return this->largura;
        }

        vector<Ponto> intRaio(Reta raio){
            vector<vector<Ponto>> pontosIntRaio = {{}};

            pontosIntRaio.push_back(this->triangulo1->intRaio(raio));
            pontosIntRaio.push_back(this->triangulo2->intRaio(raio));
            pontosIntRaio.push_back(this->triangulo3->intRaio(raio));
            pontosIntRaio.push_back(this->triangulo4->intRaio(raio));
            pontosIntRaio.push_back(this->triangulo5->intRaio(raio));
            pontosIntRaio.push_back(this->triangulo6->intRaio(raio));
            pontosIntRaio.push_back(this->triangulo7->intRaio(raio));
            pontosIntRaio.push_back(this->triangulo8->intRaio(raio));
            pontosIntRaio.push_back(this->triangulo9->intRaio(raio));
            pontosIntRaio.push_back(this->triangulo10->intRaio(raio));
            pontosIntRaio.push_back(this->triangulo11->intRaio(raio));
            pontosIntRaio.push_back(this->triangulo12->intRaio(raio));

            vector<Ponto> pontosIntRaioOutput;
            for(int i = 0; i < pontosIntRaio.size(); i++){
                if(pontosIntRaio[i].size() > 0){
                    pontosIntRaioOutput.push_back(pontosIntRaio[i][0]);
                }
            }

            return pontosIntRaioOutput;
        }
        
        Objeto* transforma(Observador obs){
            return new Cubo(obs.converte(centro), largura, *vetorDistancia(*new Ponto(0,0,0) , obs.converte(direcao)));
        }

        Vetor* getNormal(Ponto p){

        }

};

class Esfera:public Objeto {  //TODO Testar
    protected:
        Ponto centro;
        double raio;

    public:
        Esfera(Ponto centro, double raio){
            this->centro = centro;
            this->raio = raio;
        }

        Ponto getCentro(){
            return this->centro;
        }

        double getRaio(){
            return this->raio;
        }

        bool pontoPertence(Ponto p){
            Vetor* vetor = vetorDistancia(p, centro);
            double norma = vetor->calcularNorma();
            norma *= norma;

            if(norma == (this->raio * this->raio)){
                return true;
            } else {
                return false;
            }
        }

        vector<Ponto> intRaio(Reta raio){
            Vetor* vetorAux = vetorDistancia(this->getCentro(),*raio.getPonto());
            double a = raio.getVetor()->produtoEscalar(*raio.getVetor());
            double b = vetorAux->produtoEscalar(*raio.getVetor());
            double c = vetorAux->produtoEscalar(*vetorAux) - this->getRaio()*this->getRaio();

            vector<double> tIntersecao = equacaoSegundoGrau(a, 2*b, c);
            vector<Ponto> pontos;
            pontos.push_back(*raio.pontoAtingido(tIntersecao[0]));
            pontos.push_back(*raio.pontoAtingido(tIntersecao[1]));

            return pontos;
        }

        Vetor* getNormal(Ponto p){
            Vetor* normal = vetorDistancia(p, this->centro)->normalizar();
            return normal;
        }

        Objeto* transforma(Observador obs){
            return new Esfera(obs.converte(centro), raio);
        }
};

class Cilindro : public Objeto{
    protected:
        Ponto base;
        Vetor normal;
        double raio;
        double altura;

    public:
        Cilindro(Ponto base, Vetor normal, double raio, double altura) {
            this->base = base;
            this->normal = *normal.normalizar();
            this->raio = raio;
            this->altura = altura;
        }

        Ponto* getBase() {
            return &this->base;
        }

        Vetor* getNormal() {
            return &this->normal;
        }

        double getRaio() {
            return this->raio;
        }

        double getAltura() {
            return this->altura;
        }

        void print(){
            cout << " Cilindro" << endl;
        }

        vector<Ponto> intRaio(Reta reta) {
            vector<Ponto> pontosAtingidos;

            //Vetor v
            Vetor* bPo = vetorDistancia(this->base,*reta.getPonto()); //(Po - B)
            double aux = (*bPo * this->normal);                       //(Po - B).u  
            Vetor* vetorAux = this->normal.multEscalar(aux);          //((Po - B).u).u
            Vetor v = *bPo - *vetorAux;                               //Vetor v

            //Vetor w
            double meuEscalar = *reta.getVetor() * this->normal;
            vetorAux = this->normal.multEscalar(meuEscalar);
            Vetor w = *reta.getVetor() -  *vetorAux;

            //Cálculo dos coeficientes da equação do segundo grau.
            double a = w * w;
            double b = v * w;
            double c = v * v - this->raio * this->raio;

            vector<double> escalares = equacaoSegundoGrau(a,2*b,c);

            //Obtendo vectora de pontos Atingidos
            vector<double>::iterator i;
            aux = 0;
            Ponto p;
            Vetor bP;
            double meuTeste;
            for(i=escalares.begin(); i != escalares.end(); i++) {
                //Testando validade dos pontos.
                p = *reta.pontoAtingido(*i);
                bP = *vetorDistancia(this->base, p);        //(P - B)
                meuTeste = bP * this->normal;
                if(0 <= meuTeste && meuTeste <= this->altura) {
                    pontosAtingidos.push_back(p);
                }
            }
            return pontosAtingidos;
            
            //Realizando o teste de validade dos pontos.



        }


        Objeto* transforma(Observador obs){
            //return new Cilindro(obs.converte(base), *vetorDistancia(*new Ponto(0,0,0) , obs.converte(normal)),
                               //raio, altura);
			return new Cilindro(obs.converte(base), normal,
				raio, altura);

		}

        Vetor* getNormal(Ponto p){
            Ponto projecaoPIntEixo = *somaPontoVetor(this->base, *(vetorDistancia(p, this->base)->produtoVetorial(this->normal)->produtoVetorial(this->normal)));
            Vetor* normal = vetorDistancia(p, projecaoPIntEixo)->normalizar();

            return normal;
        }


};

class Cone : public Objeto {
    protected:
        Ponto base;
        Ponto vertice;
        Vetor normal;
        double raio;
        double altura;

    public:
        Cone(Ponto base, Vetor normal, double raio, double altura) {
            this->base = base;
            this->normal = *normal.normalizar();
            this->raio = raio;
            this->altura = altura;
            this->vertice = *somaPontoVetor(this->base, *(this->normal.multEscalar(this->altura)));
        }

        Ponto* getBase() {
            return &this->base;
        }

        Vetor* getNormal() {
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

        double getCossenoGeratriz() {
            return this->altura / sqrt(pow(this->altura,2) + pow(this->raio,2));
        }

        vector<Ponto> intRaio(Reta reta) {
            vector<Ponto> pontosAtingidos;
            //vetor v
            Vetor v = *vetorDistancia(*reta.getPonto(), this->vertice);
        
            //Cálculo dos coeficientes da equaçao do segundo grau
            double a = ((*reta.getVetor() * this->normal) * (*reta.getVetor() * this->normal)) - ((*reta.getVetor() * *reta.getVetor())* pow(this->getCossenoGeratriz(), 2));
            double b = (v * *reta.getVetor()) * pow(this->getCossenoGeratriz(),2) - 
                    (v * this->normal) * (*reta.getVetor() * this->normal);
            double c = pow(v * this->normal,2) - (v * v) * pow(this->getCossenoGeratriz(),2);

            //Achando os escalares da intersecao.
            vector<double> escalares = equacaoSegundoGrau(a,2*b,c);

            vector<double>::iterator i;
            Ponto p;
            double teste;
            for(i=escalares.begin(); i != escalares.end(); i++) {
                //Testando validade dos pontos.
                p = *reta.pontoAtingido(*i);
                teste = *vetorDistancia(p, this->vertice) * this->normal;
                if(0<=teste && teste<=this->altura) {
                    pontosAtingidos.push_back(p);
                }
            }
            return pontosAtingidos;
        }


        Objeto* transforma(Observador obs){
            //return new Cone(obs.converte(base), *vetorDistancia(*new Ponto(0,0,0) , obs.converte(normal)),
                               // raio, altura);
			return new Cone(obs.converte(base), normal,
				raio, altura);
        }

        Vetor* getNormal(Ponto p){
            Vetor* Nc = &this->normal; //vetor normal na base do cone
            Ponto* V = &this->vertice; //ponto do vértice do cone
            Vetor* Vg = vetorDistancia(*V, p); //vetor do ponto pInt(p) até o vértice do cone, ou seja, vetor paralelo à geratriz do cone
            Vetor* Vt = Nc->produtoVetorial(*Vg); //vetor tangente ao cone no ponto pInt(p)
            Vetor* normal = Vt->produtoVetorial(*Vg); //vetor perpendicular à geratriz do cone

            return normal;
        }


};


class Luz{
    private:
        Vetor intensidade;
        Ponto posicao;

    public:
        Luz(Ponto posicao, Vetor intensidade){
            this->posicao =  posicao;
            this->intensidade = intensidade;
        }

        Ponto* getPosicao(){
            return &posicao;
        }

        Vetor getIntensidade(){
            return intensidade;
        }

        Luz* transforma(Observador obs){
            return new Luz(obs.converte(posicao), intensidade);
        }

};

class Mundo{
    private:
        vector<Objeto*> objetos;
        vector<Luz*> luzes;
        Vetor luz_ambiente;
		Observador* observador;

    public:
        Mundo(Vetor luz_ambiente){
            this->luz_ambiente = luz_ambiente;
        }

        void addObjeto(Objeto* obj){
            objetos.push_back(obj);
        }

        void addLuz(Luz* luz){
            luzes.push_back(luz);
        }

        vector<Objeto*> getObjetos(){
            return objetos;
        }

        vector<Luz*> getLuzes(){
            return luzes;
        }

		void setObservador(Observador *observador) {
			this->observador = observador;
		}

		Observador* getObservador() {
			return observador;
		}

        Vetor getLuzAmbiente(){
            return luz_ambiente;
        }

        Mundo* obsMundo(Observador* obs){
            Mundo *obsMundo = new Mundo(luz_ambiente);
			obsMundo->setObservador(obs);

            for (auto i = objetos.cbegin(); i != objetos.cend(); ++i){
                Objeto* ob = (*i)->transforma(*obs);
                ob->setMaterial((*i)->getMaterial());
                obsMundo->addObjeto(ob);
            } 

            for (auto i = luzes.cbegin(); i != luzes.cend(); ++i){
                Luz* ob = (*i)->transforma(*obs);
                obsMundo->addLuz(ob);
            }

           return obsMundo;
        }

};

bool compare(pair<double, Objeto*> a,  pair<double, Objeto*> b){
    return a.first < b.first;
}

class Pixel{
    private:   
	    vector<pair <double, Objeto*> > solutions;
	    Reta* reta;
	    Mundo* obsMundo;
	    Ponto obs;
	    Ponto center;

    public:
        Pixel(Ponto center, Ponto obs, Mundo* obsMundo){

            this->obsMundo = obsMundo;
            this->center = center;
            this->reta = new Reta( obs, *vetorDistancia(obs, center));
            this->obs = obs;
            vector<Objeto*> objetos = (*obsMundo).getObjetos();
            
            for(vector<Objeto*>::iterator i=objetos.begin(); i != objetos.end(); i++){ 
                if((*i)->getVisibilidade() == true){

                    vector<Ponto> pontos_intersec = (*i)->intRaio( *reta );
                    vector<double> t_intersec;


                    for (vector<Ponto>::iterator it_pontos = pontos_intersec.begin(); it_pontos != pontos_intersec.end(); it_pontos++)
                        t_intersec.push_back( (vetorDistancia( obs, (Ponto)(*it_pontos) ) )->calcularNorma() );

                        

                    for (vector<double>::iterator t = t_intersec.begin(); t != t_intersec.end(); t++)
                        if((*t)>0) solutions.push_back( make_pair((*t),(*i)) ); 
                                   
                    }

            }

            sort(solutions.begin(), solutions.end(), compare);
        }


        vector<pair <double, Objeto*> > getSolutions(){
            return solutions;
        }

        Color getColor(){
            if(solutions.size() != 0) {
                Vetor *Id = new Vetor(0,0,0);
                Vetor *Is = new Vetor(0,0,0);

                Vetor Ia = (*obsMundo).getLuzAmbiente().elemMult( *solutions.front().second->getMaterial() );
                
                vector<Luz*> luzes = (*obsMundo).getLuzes();
                for(vector<Luz*>::iterator it_luzes=luzes.begin(); it_luzes != luzes.end(); it_luzes++){ 

                    Pixel *test = new Pixel(*(*reta).pontoAtingido(solutions.front().first), *((*it_luzes)->getPosicao()), obsMundo);
                    if((*test).getSolutions().size() != 0 && (*test).getSolutions().front().second->getId()==solutions.front().second->getId()){

                        Vetor normal = *solutions.front().second->getNormal(*(*reta).pontoAtingido(solutions.front().first))->normalizar();
                        Vetor l = *(*vetorDistancia(*(*reta).pontoAtingido(solutions.front().first), *(*it_luzes)->getPosicao())).normalizar();
                        double fd = normal * l;
                        if(fd < 0) fd = 0;


                        Vetor r = l - *(*normal.multEscalar(normal*l)-l).multEscalar(2)->normalizar();
                        double fs = *(*vetorDistancia(*(*reta).pontoAtingido(solutions.front().first), obs)).normalizar() * r;
                        if(fs < 0) fs = 0;


                        *Id = *Id + *((*it_luzes)->getIntensidade().elemMult(*solutions.front().second->getMaterial()).multEscalar(fd));
                        *Is = *Is +  *((*it_luzes)->getIntensidade().elemMult(*solutions.front().second->getMaterial()).multEscalar(fs));  
                        
                    }
                }
            
                Ia = Ia+*Id+*Is;
                return Color(Ia.getX(), Ia.getY(), Ia.getZ());
            }
            return Color(1,1,1);
        }
};


class Painel{
    private:
        double distancia;
        double lado;
        int pixels;
        Mundo* obsMundo;
        vector<vector<Color>> mtrx;

    public:
        Painel(Mundo* obsMundo, double distancia, double lado, int pixels){
            this->obsMundo = obsMundo;
            this->distancia = distancia;
            this->lado = lado;
            this->pixels = pixels;

            vector<Color> linhas;
            for(int i = 0; i < pixels; i++){
                for(int j = 0; j < pixels; j++){
                    Pixel* pixel = new Pixel(*getCenter(i,j), *obsMundo->getObservador()->getPosicao(), obsMundo);
					//Pixel* pixel = new Pixel(*getCenter(i,j), *new Ponto(0,0,0), obsMundo);

					linhas.push_back(pixel->getColor());
                }

                mtrx.push_back(linhas);
                linhas.clear();
            }

        }

        vector<vector<Color>> getMatrix(){
            return mtrx;
        }

        Ponto* getCenter(int i, int j){
            double delx = lado/pixels, dely = lado/pixels;
            double x = -lado/2 + delx/2 + j*delx;
            double y = lado/2 - dely/2 - i*dely;
            double z = -distancia;
            return new Ponto(x,y,z);
        }


};





//pixel buffer
RenderAPI::VertexBuffer vbo;

const int width = 512, height = 512;

Painel* painel;
Mundo* obsMundo;

// display function called by MainLoop(), gets executed every frame 
void disp(void){
    
 
    vector<vector<Color>> colorBuffer = painel->getMatrix();

	
	//Remove the old frame from the buffer
	RenderAPI::BufferClear();

	//Render using RayCast	
	RenderAPI::BufferBind(vbo);
	//get the pixel color list, where if you have 100 x 100 pixels this list will have size 10.000 and will be read line by line
	// vector< vector< Color >> colorBuffer; //TODO: your render function here
	RenderAPI::MapBuffer(colorBuffer, width, height);

	//End frame
	RenderAPI::SwapBuffers();//set the actual frame to the graphic card
	RenderAPI::ReDisplay();//recall the display function
}

// mouse event handlers
int lastX = 0, lastY = 0;
int theButtonState = 0;
int theModifierState = 0;

// camera mouse controls in X and Y direction
void motion(int x, int y)
{
	cout << x << " " << y << endl;
	Pixel* p = new Pixel(*painel->getCenter(x, y), *obsMundo->getObservador()->getPosicao(), obsMundo);
	if (p->getSolutions().size() != 0) cout << p->getSolutions().front().second->getId() << endl;
	else cout << "None" << endl;
}

void mouse(int button, int state, int x, int y)
{/*
	cout << x << " " << y << endl;
	Pixel* p = new Pixel(*painel->getCenter(x, y), *obsMundo->getObservador()->getPosicao(), obsMundo);
	if (p->getSolutions().size() != 0) cout << p->getSolutions().front().second->getId() << endl;
	else cout << "None" << endl;*/
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case(' ')://TODO: your key name here
			//TODO: your key function here
		break;
	}
}

void resize(int w, int h) {
	RenderAPI::setView(w, h);
}

// Main.
int main(int argc, char** argv) {
	
    // teste();
	Mundo* mundo = new Mundo(*new Vetor(0.1, 0.1, 0.1));
	Objeto* cilindro = new Cilindro(*new Ponto(7, 5, 0), *new Vetor(0, -1, 0), 1.0, 5.0);
	cilindro->setMaterial(new Vetor(0.58, 0.29, 0));
	mundo->addObjeto(cilindro);

	cout << cilindro->getId() << endl;

	Objeto* cone = new Cone(*new Ponto(7, 0, 0), *new Vetor(0, -1, 0), 3.0, 5.0);
	cone->setMaterial(new Vetor(0, 0.8, 0));
	mundo->addObjeto(cone);

	cout << cone->getId() << endl;

	/*
	Objeto* esfera1 = new Esfera(*new Ponto(7, 5, 2), 1);
	esfera1->setMaterial(new Vetor(0, 0.8, 0));
	mundo->addObjeto(esfera1);
	

	
	Objeto* esfera2 = new Esfera(*new Ponto(7, 5, -2), 1);
	esfera2->setMaterial(new Vetor(0, 0.8, 0));
	mundo->addObjeto(esfera2);
	
	
	Objeto* plano = new Plano(*new Ponto(0, 0, 0), *new Vetor(0, 1, 0));
	plano->setMaterial(new Vetor(0, 0, 0));
	mundo->addObjeto(plano);
	*/


	mundo->addLuz(new Luz(*new Ponto(0, 0, 0), *new Vetor(0.3, 0.3, 0.3)));

	Observador* observador = new Observador(*new Ponto(0, -1, 0), *new Ponto(7, 0, 0), *new Ponto(0, 10, 0));
	obsMundo = mundo->obsMundo(observador);
	painel = new Painel(obsMundo, 2, 10, 512);

    // Create API window
	RenderAPI::StartRenderAPI(argc, argv, width, height);
    
	// functions for user interaction
    RenderAPI::MouseFunc(mouse);
    RenderAPI::MotionFunc(motion);
    RenderAPI::KeyboardFunc(keyboard);
	RenderAPI::ReshapeFunc(resize);

	//function that will be called to control what will be displayed
	RenderAPI::DisplayFunc(disp);

	//create the pixel buffer
	RenderAPI::CreateVBO(&vbo, width, height);
	
	//start render loop
    RenderAPI::RenderLoop();

    //if i'm here is because the render loop was stopped and i'm exiting the application
	//delete the pixel buffer
	RenderAPI::DeleteVBO(&vbo);
	
}
