#include <iostream>
#include <math.h>
#include <vector>
#include "RenderAPI.h"
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

static class Factory {
	public:
	Matriz *getTranslacao(double tx, double ty, double tz) {
		vector<vector<double>> matriz = { {} };
		vector<double> prilin = { 1,0,0,tx };
		vector<double> seglin = { 0,1,0,ty };
		vector<double> terlin = { 0,0,1,tz };
		vector<double> qualin = { 0,0,0, 1 };
		matriz = { prilin,seglin,terlin,qualin };
		return new Matriz(matriz);
	}
};


int pontoID = 1;
class Ponto {
    protected:
		int id;
        double x;
        double y;
        double z;

    public:
        Ponto() {
            this->x = 0;
            this->y = 0;
            this->z = 0;
            this->id = pontoID;
			pontoID++;
        }
        
        Ponto(double x, double y, double z) {
            this->x = x;
            this->y = y;
            this->z = z;
			this->id = pontoID;
			pontoID++;
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

   //     Cor getCor() {
			//return this->cor;
   //     }

   //     void setCor(float red, float green, float blue) {
   //         this->cor = {red, green, blue};
   //     }

		bool igual(Ponto *p) {
			if (this->x == p->getX() && this->y == p->getY() && this->z == p->getZ()) {
				return true;
			}
			else {
				return false;
			}
		}

        void print() {
            cout << "Ponto " << this->id << " (X:" << this->x <<"; Y:" << this->y << "; Z:" << this->z << ")" << endl;
        }
};

int vetorID = 1;
class Vetor: public Ponto {
    public:
        Vetor() {
			this->x = 0;
			this->y = 0;
			this->z = 0;
			this->id = vetorID;
			vetorID++;
		}

        Vetor(double x, double y, double z) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->id = vetorID;
			vetorID++;
		}

        double produtoEscalar(Vetor vetor) {
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
            cout << "Vetor " << this->id << " [X:" << this->x << "; Y:" << this->y << "; Z:" << this->z << "]" << endl;
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
            
			delete(vetorUnitI);
			delete(vetorUnitJ);
			delete(vetorUnitK);
			delete(diagonalPrincipal);
			delete(diagonalSecundaria);
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

class Quaternio {
    public:
        double x;    // vetor do eixo de rotação, que passa pela origem
        double y;
        double z;
        double w; // angulo da rotação ao redor do eixo

        Quaternio(){    // Quaternio neutro
            x = 0;
            y = 0;
            z = 0;
            w = 1;
        }

        Quaternio(Vetor *v, double wA){
            x = v->getX();
            y = v->getY();
            z = v->getZ();
            w = wA;
        }

        void normalizar(){
            double magnitude = sqrt(x*x + y*y + z*z + w*w);
            x /= magnitude;
            y = magnitude;
            z /= magnitude;
            w /= magnitude;
        }

        Quaternio* operator * (Quaternio *q2){
            Quaternio *q1 = this;
            Quaternio *qOut = new Quaternio();
            
            qOut->w = q1->w*q2->w - q1->x*q2->x - q1->y*q2->y - q1->z*q2->z;
            qOut->x = q1->w*q2->x + q2->w*q1->x + q1->y*q2->z - q1->z*q2->y;
            qOut->y = q1->w*q2->y + q2->w*q1->y + q1->z*q2->x - q1->x*q2->z;
            qOut->z = q1->w*q2->z + q2->w*q1->z + q1->x*q2->y - q1->y*q2->x;

            return qOut;
        }

        Matriz* rotacao(){
            vector< vector< double >> m = {{w*w + x*x - y*y - z*z, 2*x*y - 2*w*y, 2*x*z + 2*w*y, 0},
                                           {2*x*y + 2*w*z, w*w - x*x + y*y - z*z, 2*y*z + 2*w*x, 0},
                                           {2*x*z - 2*w*y, 2*y*z - 2*w*x, w*w - x*x - y*y + z*z, 0},
                                           {0            , 0           , 0                     , 1}};
        }
};

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

            double a = - (*vetorDistancia(*new Ponto(0,0,0),posicao) * i);
            double b = - (*vetorDistancia(*new Ponto(0,0,0),posicao) * j);
            double c = - (*vetorDistancia(*new Ponto(0,0,0),posicao) * k);

            vector<double> primeiraLinha = {i.getX(), i.getY(), i.getZ(), a};
            vector<double> segundalinha  = {j.getX(), j.getY(), j.getZ(), b};
            vector<double> terceiraLinha = {k.getX(), k.getY(), k.getZ(), c};
            vector<double> quartalinha	 = {0       , 0       , 0       , 1};

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

		Vetor converteVetor(Vetor vet) {
			vector<vector<double>> vetorAtransformar = { {vet.getX()}, {vet.getY()}, {vet.getZ()}, {0} };
			Matriz* resultado = matriz->produto(new Matriz(vetorAtransformar));
			return *new Vetor(resultado->get(0, 0), resultado->get(1, 0), resultado->get(2, 0));
		}
};


class Objeto {
    protected:
        static int incrementador;
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
            this->id = incrementador;
			incrementador++;
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

		virtual Objeto* transforma(Observador obs)	{	return 0; }
		virtual Vetor* getNormal(Ponto p) 			{	return 0; }
		virtual vector<Ponto> intRaio(Reta reta)	{	return {};}
		virtual Objeto* translate(double tx, double ty, double tz) { return 0; }

};

int Objeto::incrementador = 1;

class Plano : public Objeto{
    protected:
        Ponto ponto;
        Vetor normal;

    public:
        Plano(Ponto ponto, Vetor normal) {
            this->ponto = ponto;
            this->normal = *normal.normalizar();
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
            return new Plano(obs.converte(ponto), obs.converteVetor(normal));
        }
};

class Triangulo : public Objeto {
    public:
        Ponto ponto1;
        Ponto ponto2;
        Ponto ponto3;

        Triangulo() : Objeto() {}
        
        Triangulo(Ponto ponto1, Ponto ponto2, Ponto ponto3) {
            this->ponto1 = ponto1;
            this->ponto2 = ponto2;
            this->ponto3 = ponto3;

            this->adicionarVertice(ponto1);
            this->adicionarVertice(ponto2);
            this->adicionarVertice(ponto3);
/*
            this->adicionarAresta(ponto1, ponto2);
            this->adicionarAresta(ponto2, ponto3);
            this->adicionarAresta(ponto3, ponto1);

            this->adicionarFace(ponto1, ponto2, ponto3);*/
        }

        vector<Ponto> intRaio(Reta raio) {
			
            Vetor* p1p2 = vetorDistancia(vertices[0], vertices[1]);
            Vetor* p1p3 = vetorDistancia(vertices[0], vertices[2]);
            Vetor* p2p3 = vetorDistancia(vertices[1], vertices[2]);
            Vetor* p3p1 = vetorDistancia(vertices[2], vertices[0]);
            Vetor* n = p1p2->produtoVetorial(*p1p3)->normalizar();


			
            Plano* planoTriangulo = new Plano(vertices[0], *n);
            vector<Ponto> pontoInt = planoTriangulo->intRaio(raio);


            if(pontoInt.size() == 0){
                return pontoInt;
            }
			
            Vetor* p1p = vetorDistancia(vertices[0], pontoInt[0]);
            Vetor* p2p = vetorDistancia(vertices[1], pontoInt[0]);
            Vetor* p3p = vetorDistancia(vertices[2], pontoInt[0]);

			Vetor* p1p2xp1p3 = p1p2->produtoVetorial(*p1p3);
			double sE = p1p2->produtoVetorial(*p1p)->produtoEscalar(*p1p2xp1p3);
			double sN = p2p3->produtoVetorial(*p2p)->produtoEscalar(*p1p2xp1p3);
			double sS = p3p1->produtoVetorial(*p3p)->produtoEscalar(*p1p2xp1p3);

			free(p1p2);
			free(p1p3);
			free(p2p3);
			free(p3p1);
			free(n);
			delete(planoTriangulo);
			free(p1p);
			free(p2p);
			free(p3p);
			free(p1p2xp1p3);

            if(sE >= 0 && sN >= 0 && sS >= 0){
                return pontoInt;
            } else {
                pontoInt.clear();
                return pontoInt;
            }
			
			return pontoInt;

		}

        Vetor* getNormal(Ponto p){
            Vetor* p1p2 = vetorDistancia(vertices[0], vertices[1]);
            Vetor* p1p3 = vetorDistancia(vertices[0], vertices[2]);
            Vetor* normal = p1p2->produtoVetorial(*p1p3)->normalizar();

            return normal;
        }

        Objeto* transforma(Observador obs){
            return new Triangulo(obs.converte(ponto1),obs.converte(ponto2),obs.converte(ponto3));
        }

		Objeto* translate(double tx, double ty, double tz) {
			Factory* factory = new Factory();
			Matriz *translacao = factory->getTranslacao(tx, ty, tz);
			Matriz* temp;
			vector<vector<double>> p;
			vector<Ponto> t;
			Ponto p1;
			for (vector<Ponto>::iterator i = vertices.begin(); i != vertices.end(); i++){
				p = { {(*i).getX()}, {(*i).getY()}, {(*i).getZ()}, {1}};
				temp = translacao->produto(new Matriz(p));
				t.push_back(*new Ponto(temp->get(0, 0), temp->get(1, 0), temp->get(2, 0)));
			}

			Objeto* triangulo = new Triangulo(t[0], t[1], t[2]);
			triangulo->setMaterial(this->getMaterial());
			return triangulo;
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

        Cubo(Ponto centro, float largura){
            this->centro = centro;
            this->largura = largura;

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
            
           /* this->adicionarAresta(*p1, *p2);
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
            this->adicionarFace(*p4, *p5, *p1);*/

            this->triangulo1  = new Triangulo(*p1, *p2, *p3);
            this->triangulo2  = new Triangulo(*p1, *p3, *p4);
            this->triangulo3  = new Triangulo(*p5, *p7, *p6);
            this->triangulo4  = new Triangulo(*p5, *p8, *p7);
            this->triangulo5  = new Triangulo(*p1, *p5, *p6);
            this->triangulo6  = new Triangulo(*p1, *p6, *p2);
            this->triangulo7  = new Triangulo(*p2, *p6, *p7);
            this->triangulo8  = new Triangulo(*p2, *p7, *p3);
            this->triangulo9  = new Triangulo(*p3, *p7, *p8);
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

		vector<Ponto> intRaio(Reta raio) {
			vector<vector<Ponto>> pontosIntRaio = { {} };

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

			vector<Ponto> pontosIntRaioMeio;
			for (int i = 0; i < pontosIntRaio.size(); i++) {
				if (pontosIntRaio[i].size() > 0) {
					pontosIntRaioMeio.push_back(pontosIntRaio[i][0]);
				}
			}

			vector<Ponto> pontosIntRaioFim;    // Checagem do caso em que o ponto de interseção retorna, erroneamente, pontos repetidos
			bool repetido = false;

			if (pontosIntRaioMeio.size() > 1) {
				for (int i = 0; i < pontosIntRaioMeio.size(); i++) {
					for (int j = 0; j < pontosIntRaioFim.size(); j++) {
						repetido = false;
						if (pontosIntRaioMeio[i].igual(&pontosIntRaioFim[j])) {
							repetido = true;
						}
					}

					if (repetido == false) {
						pontosIntRaioFim.push_back(pontosIntRaioMeio[i]);
					}
				}

				/*if (pontosIntRaioMeio.size() != 0) {
					free(&pontosIntRaioMeio);
				}*/
				return pontosIntRaioFim;
			}

			return pontosIntRaioMeio;
		}
        
        Objeto* transforma(Observador obs){
            return new Cubo(obs.converte(centro), largura);
        }

        Vetor* getNormal(Ponto p){
			Vetor* iCubo = vetorDistancia(this->vertices[0], this->vertices[3])->normalizar();
			Vetor* iNegativoCubo = vetorDistancia(this->vertices[3], this->vertices[0])->normalizar();
			Vetor* jCubo = vetorDistancia(this->vertices[4], this->vertices[0])->normalizar();
			Vetor* jNegativoCubo = vetorDistancia(this->vertices[0], this->vertices[4])->normalizar();
			Vetor* kCubo = vetorDistancia(this->vertices[0], this->vertices[1])->normalizar();
			Vetor* kNegativoCubo = vetorDistancia(this->vertices[1], this->vertices[0])->normalizar();

			if (p.getX() == this->vertices[3].getX()){
                return iCubo;
            } else if (p.getX() == this->vertices[0].getX()) {
				return iNegativoCubo;
			}
			else if (p.getY() == this->vertices[0].getY()) {
				return jCubo;
			}
			else if (p.getY() == this->vertices[7].getY()) {
				return jNegativoCubo;
			}
			else if (p.getZ() == this->vertices[1].getZ()) {
				return kCubo;
			}
			else if (p.getZ() == this->vertices[0].getZ()){
                return kNegativoCubo;
            } else {
                cout << "WHAT THE FUCK\n";
            }

        }

};

class Esfera : public Objeto {  //TODO Testar
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
			for (vector<double>::iterator i = tIntersecao.begin(); i != tIntersecao.end(); i++) {
				pontos.push_back(*raio.pontoAtingido(*i));
			}

            return pontos;
        }

        Vetor* getNormal(Ponto p){
            Vetor* normal = vetorDistancia(this->centro,p)->normalizar();
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
            return new Cilindro(obs.converte(base), obs.converteVetor(normal),   raio, altura);
			//return new Cilindro(obs.converte(base), normal, raio, altura);

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
                teste = *vetorDistancia(base, p) * this->normal;
                if(0<=teste && teste<=this->altura) {
                    pontosAtingidos.push_back(p);
                }
            }
            return pontosAtingidos;
        }


        Objeto* transforma(Observador obs){
            return new Cone(obs.converte(base), obs.converteVetor(normal),   raio, altura);
			//return new Cone(obs.converte(base), normal,raio, altura);
        }

        Vetor* getNormal(Ponto p){
            Vetor* Nc = &this->normal; //vetor normal na base do cone
            Ponto* V = &this->vertice; //ponto do vértice do cone
            Vetor* Vg = vetorDistancia(p, *V); //vetor do ponto pInt(p) até o vértice do cone, ou seja, vetor paralelo à geratriz do cone
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
			//return this;
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
			vector<Ponto> pontos_intersec;
			vector<double> t_intersec;

            
            for(vector<Objeto*>::iterator i=objetos.begin(); i != objetos.end(); i++){ 
                if((*i)->getVisibilidade() == true){

                    pontos_intersec = (*i)->intRaio( *reta );


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

		Reta* getReta() {
			return reta;
		}

        Cor getCor(){
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
					delete(test);
                }
            
                Ia = Ia+*Id+*Is;
                return Cor(Ia.getX(), Ia.getY(), Ia.getZ());
            }
            return Cor(1,1,1);
        }
};


class Painel{
    private:
        double distancia;
        double lado;
        int pixels;
        Mundo* obsMundo;
        vector<vector<Cor>> mtrx;

    public:
        Painel(Mundo* obsMundo, double distancia, double lado, int pixels){
            this->obsMundo = obsMundo;
            this->distancia = distancia;
            this->lado = lado;
            this->pixels = pixels;

            vector<Cor> linhas;
            for(int i = 0; i < pixels; i++){
                for(int j = 0; j < pixels; j++){
                    //Pixel* pixel = new Pixel(*getCenter(i,j), *obsMundo->getObservador()->getPosicao(), obsMundo);
					Pixel* pixel = new Pixel(*getCenter(i,j), *new Ponto(0,0,0), obsMundo);

					linhas.push_back(pixel->getCor());
					delete(pixel);
					//linhas.insert(linhas.begin(), pixel->getCor());
                }
				//mtrx.push_back(linhas);
                mtrx.insert(mtrx.begin(),linhas);
                linhas.clear();
            }

        }

        vector<vector<Cor>> getMatrix(){
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
    
 
    vector<vector<Cor>> colorBuffer = painel->getMatrix();

	
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
	
}


Pixel* p1 = NULL;
Pixel* p2 = NULL;
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		
		if (state == GLUT_DOWN) {
			p1 = new Pixel(*painel->getCenter(y, x), *new Ponto(0, 0, 0), obsMundo);
			if (p1->getSolutions().size() != 0) cout << p1->getSolutions().front().second->getId() << endl;
			else cout << "None" << endl;
		}

		if (state == GLUT_UP) {

			p2 = new Pixel(*painel->getCenter(y, x), *new Ponto(0, 0, 0), obsMundo);
			if (p2->getSolutions().size() != 0) cout << p2->getSolutions().front().second->getId() << endl;
			else cout << "None" << endl;
			
			
			/*
			if (p1->getSolutions().size() != 0) {
				Ponto inicio = *p1->getReta()->pontoAtingido(p1->getSolutions().front().first);
				Ponto fim = *p2->getReta()->pontoAtingido(p1->getSolutions().front().first);
				Vetor eixo = *vetorDistancia(inicio, fim);

				obsMundo->addObjeto(p1->getSolutions().front().second->translate(eixo.getX(), eixo.getY(), eixo.getZ()));
				painel = new Painel(obsMundo, 2, 10, 512);

			}
			*/

		}

		
	}
	
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



void testes();

class Retangulo : public Objeto{
public:
	double n;
	double m;
	Ponto ponto;
	Vetor normal;
public:
	Retangulo(double n, double m, Ponto ponto, Vetor normal){
		this->n = n/2;
		this->m = m/2;
		this->ponto = ponto;
		this->normal = normal;

		this->adicionarVertice(Ponto(ponto.getX() + this->n, ponto.getY() + this->m, ponto.getZ()));
		this->adicionarVertice(Ponto(ponto.getX() + this->n, ponto.getY() - this->m, ponto.getZ()));
		this->adicionarVertice(Ponto(ponto.getX() - this->n, ponto.getY() + this->m, ponto.getZ()));
		this->adicionarVertice(Ponto(ponto.getX() - this->n, ponto.getY() - this->m, ponto.getZ()));
	}

	vector<Ponto> intRaio(Reta reta) {
		Plano *pl = new Plano(ponto, normal);
		vector<Ponto> intpl = pl->intRaio(reta);
		vector<Ponto> pontos;
		if (intpl.size() > 0) {
			Vetor aux = *vetorDistancia(ponto, intpl[0]);
			if (aux.getX() < n && aux.getY() < m && aux.getX() > -n && aux.getY() > -m)
				pontos.push_back(intpl[0]);
		}

		return pontos;
	}

	Vetor* getNormal(Ponto p) {
		return &normal;
	}

	Objeto* transforma(Observador obs) {
		return new Retangulo(n, m, obs.converte(ponto), obs.converteVetor(normal));

	}



};

// Main.
int main(int argc, char** argv) {



    bool teste = false;  // altere para alternar entre rodar testes e renderizar o cenário

    if(teste){
        
        testes();
    
    } else {

 
        
    	Mundo* mundo = new Mundo(*new Vetor(0.1, 0.1, 0.1));

        Objeto* cilindro = new Cilindro(*new Ponto(7, -5, 0), *new Vetor(0, 1, 0), 1.0, 5.0);
        cilindro->setMaterial(new Vetor(0.58, 0.29, 0));        
		mundo->addObjeto(cilindro);

        Objeto* cone = new Cone(*new Ponto(7, 0, 0), *new Vetor(0, 1, 0), 3.0, 5.0);
        cone->setMaterial(new Vetor(0, 0.8, 0));
        mundo->addObjeto(cone);

		Objeto* retangulo = new Retangulo(50,50,*new Ponto(10, -5, -3), *new Vetor(0, 1, 0));
		retangulo->setMaterial(new Vetor(1, 1, 1));
		//mundo->addObjeto(retangulo); 

		Objeto* esfera = new Esfera(*new Ponto(7, -3, -4), 2);
		esfera->setMaterial(new Vetor(0.3, 0.3, 0.7));
		mundo->addObjeto(esfera);
		
		Objeto* triangulo = new Triangulo(*new Ponto(7, 0, 0), *new Ponto(7, 0, 5), *new Ponto(7, 5, 0));
		triangulo->setMaterial(new Vetor(0, 1, 0));
		//mundo->addObjeto(triangulo);
	
		Objeto* cubo = new Cubo(*new Ponto(7, 0, -6), 2.0);
		cubo->setMaterial(new Vetor(0.9, 0.9, 0.9));
		//mundo->addObjeto(cubo);

		mundo->addLuz(new Luz(*new Ponto(1, 5, 2), *new Vetor(0.3, 0.3, 0.3)));
		Observador* observador = new Observador(*new Ponto(0, 2, 0), *new Ponto(7, -5, 0), *new Ponto(0, 10, 0));

		mundo->addLuz(new Luz(*new Ponto(4, 1 , 4), *new Vetor(0.3, 0.3, 0.3)));
		Observador* observador = new Observador(*new Ponto(0, -1, 0), *new Ponto(7, 0, 0), *new Ponto(0, 10, 0));
		obsMundo = mundo->obsMundo(observador);
		painel = new Painel(obsMundo, 2, 10, 512);
		
		
		/*
		Mundo* mundo = new Mundo(*new Vetor(0.1, 0.1, 0.1));
		Objeto* triangulo = new Triangulo(*new Ponto(7, 0, 0), *new Ponto(7, 0, 5), *new Ponto(7, 5, 0));
		triangulo->setMaterial(new Vetor(0, 1, 0)); 
		mundo->addObjeto(triangulo);

		Objeto* triangulo2 = new Triangulo(*new Ponto(5, 0, 0), *new Ponto(7, 5, 0), *new Ponto(5, 1, 3));
		triangulo2->setMaterial(new Vetor(0, 1, 0));
		mundo->addObjeto(triangulo2);

		mundo->addLuz(new Luz(*new Ponto(1, 5, 2), *new Vetor(0.3, 0.3, 0.3)));
		Observador* observador = new Observador(*new Ponto(0, 0, 0), *new Ponto(7, 0, 0), *new Ponto(0, 10, 0));
		obsMundo = mundo->obsMundo(observador);
		painel = new Painel(obsMundo, 2, 10, 512);
	
	*/



        
		
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
}


// ################### INICIO DE CÓDIGO DE TESTES #####################################


void testes() {

	vector<Ponto> p;
	p.push_back(*new Ponto(0, 0, 0));
	p.push_back(*new Ponto(1, 0, 0));
	p.push_back(*new Ponto(2, 0, 0));

	for (auto i = p.begin(); i != p.end(); i++) {
		(*i).print();
	}
	
	for (vector<Ponto>::iterator i = p.begin();i != p.end();i++) {
		p.erase(i);
		p.push_back(*new Ponto(1, 1, 1));
	}

	for (auto i = p.begin(); i != p.end(); i++) {
		(*i).print();
	}

	/*
	cout << "\n-----------Teste de Matriz------------" << endl;
	vector<vector<double>> a = {{2, 3},
								{1, 0},
								{4, 5}};

	vector<vector<double>> b = {{3, 1},
								{2, 4}};

	Matriz* A = new Matriz(a);
	Matriz* B = new Matriz(b);

	A->print();
	cout << endl;

	B->print();
	cout << endl;

	Matriz* C = A->produto(B);

	C->print(); //deve printar:
				// 12 14
				// 3  1
				// 22 24
	cout << endl;

	cout << "\n-----------Teste de Equação do 2° grau------------" << endl;

	vector<double> raizes1 = equacaoSegundoGrau(1, 2, 1);
	cout << "\nRaízes de x² + 2x + 1:" << endl;
	cout << raizes1.size() << " raízes\n";
	for(int i = 0; i < raizes1.size(); i++){
		cout << raizes1[i] << endl;
	}

	vector<double> raizes2 = equacaoSegundoGrau(2, 2, -1);
	cout << "\nRaízes de 2x² + 2x - 1:" << endl;
	cout << raizes2.size() << " raízes\n";
	for(int i = 0; i < raizes2.size(); i++){
		cout << raizes2[i] << endl;
	}

	vector<double> raizes3 = equacaoSegundoGrau(1, 2, 0);
	cout << "\nRaízes de x² + 2x:" << endl;
	cout << raizes3.size() << " raízes\n";
	for(int i = 0; i < raizes3.size(); i++){
		cout << raizes3[i] << endl;
	}

	double resultado;                    //Escalar qualquer
	Ponto *ponto1 = new Ponto(1,1,1);
	Ponto *ponto2;
	Ponto *ponto3 = new Ponto(3,-2, 0);
	Vetor *vetor1 = new Vetor(1,1,1);   //Vetores para testes
	Vetor *vetor2 = new Vetor(2,2,2);
	Vetor *vetor3;
	Vetor *vetor4;
	Vetor *vetor5 = new Vetor(1,2,0);
	Vetor *vetor6 = new Vetor(3,-2,0);
	Vetor *vetor7 = new Vetor(0,0,1);

	// **********INICIO TESTE DA CLASSE VETOR***************

	cout << "\n-----------Teste print------------" << endl;
	ponto1->print();
	ponto3->print();
	vetor1->print();
	vetor2->print();

	cout << "\n------------Teste Produto Escalar------------" << endl;
	resultado = vetor1->produtoEscalar(*vetor2);
	cout << resultado << endl;

	cout << "\n------------Teste Multiplicação por Escalar-----------" << endl;
	vetor3 = vetor2->multEscalar(4);
	vetor3->print();
	vetor3 = vetor2->multEscalar(0);
	vetor3->print();

	cout << "\n--------------Teste Cálculo da Norma------------" << endl;
	resultado = vetor1->calcularNorma();
	cout << "vetor1 - Norma: " << resultado << endl;
	cout << "vetor2 - Norma: " << resultado << endl;


	cout << "\n--------------Teste Normalizar----------" << endl;
	vetor4 = new Vetor(4,2,8);
	vetor4 = vetor4->normalizar();
	vetor4->print();

	cout << "\n---------------Teste do operador + --------------- " << endl;
	*vetor3 = *vetor1 + *vetor2;
	vetor3->print();

	cout << "\n---------------Teste do operador - ----------------" << endl;
	*vetor3 = *vetor1 - *vetor2;
	vetor3->print();

	cout << "\n---------------Teste do operador * (produto escalar)---------" << endl;
	resultado = *vetor1 * *vetor2;
	cout << "produto escalar: " << resultado << endl;

	cout << "\n-----------Teste Produto Vetorial------------------" << endl;
	vetor3 = vetor5->produtoVetorial(*vetor6);
	vetor3->print();

	//****************FIM TESTES DA CLASSE VETOR******************

	//****************TESTES DA CLASSE RETA***********************
	cout << "---------Teste de instanciação da reta e print------------------" << endl;
	Reta *reta1 = new Reta(*ponto1, *vetor7);
	reta1->print();

	cout << "---------Teste do ponto atingido-------" << endl;
	ponto2 = reta1->pontoAtingido(3);
	ponto2->print();

	//***************FIM DOS TESTES DA CLASSE RETA*******************

	//***************INICIO TESTES CLASSE PLANO**********************
	cout << "----------Teste do pertencePlano----------------" << endl;
	Plano *meuplano = new Plano(Ponto(0, 0, 0), Vetor(0, 0, 1));
	Ponto *ponto4 = new Ponto(1, 1, 0);
	bool teste = meuplano->pertencePlano(*ponto4);
	cout << teste << endl;

	cout << "---------Teste da interseção raio-plano----" << endl; //Por fazer.

	Vetor *meuvetor = new Vetor(0,0,-1);
	Reta *minhareta = new Reta(Ponto(0, 0, 1),*meuvetor);
	vector<Ponto> intersecao = meuplano->intRaio(*minhareta);
	vector<Ponto>::iterator i;
	for(i=intersecao.begin(); i!=intersecao.end(); i++) {
		i->print();
	}

	cout << "---------Teste da interseçao do cilindro------" << endl;

	//Criando o cilindro
	Ponto *base = new Ponto(2,0,0);
	Vetor *normal = new Vetor(0,1,0);

	//Reta que colidirá com o cilindro
	Ponto *pontoInicio = new Ponto(-4,1,0);
	Vetor *direcaoReta = new Vetor(1,0,0);
	Reta *reta2 = new Reta(*pontoInicio,*direcaoReta);
	Cilindro *cilindro1 = new Cilindro(*base, *normal, 2, 4);


	vector<Ponto> cilindroIntersecao = cilindro1->intRaio(*reta2);
	vector<Ponto>::iterator k;
	for(k=cilindroIntersecao.begin(); k!=cilindroIntersecao.end(); k++) {
		k->print();
	}

	cout << "---------Teste de Objeto-------------------" << endl;
	Objeto *obj1 = new Objeto();*/
	Ponto *v1 = new Ponto(0, 0, 0);
	Ponto *v2 = new Ponto(1, 0, 0);
	Ponto *v3 = new Ponto(0, 1, 0);
	Ponto *v4 = new Ponto(0, 0, 1);

	/*obj1->setVisibilidade(false);

	obj1->adicionarVertice(*v1);
	obj1->adicionarVertice(*v2);
	obj1->adicionarVertice(*v3);
	obj1->adicionarVertice(*v4);

	obj1->adicionarAresta(*v1, *v2);
	obj1->adicionarAresta(*v1, *v3);
	obj1->adicionarAresta(*v1, *v4);
	obj1->adicionarAresta(*v2, *v3);
	obj1->adicionarAresta(*v3, *v4);
	obj1->adicionarAresta(*v4, *v2);

	obj1->adicionarFace(*v1, *v3, *v2);
	obj1->adicionarFace(*v1, *v3, *v4);
	obj1->adicionarFace(*v1, *v4, *v2);
	obj1->adicionarFace(*v2, *v3, *v4);

	obj1->print();

	cout << "---------Teste de Triangulo-------------------" << endl;
	Triangulo *triangulo = new Triangulo(*v1, *v2, *v3);
	Reta *retaTrianguloMiss = new Reta(Ponto(0.0, -0.2, -1.0), Vetor(0.0, 0.0, -1.0));
	vector<Ponto> intTrianguloMiss = triangulo->intRaio(*retaTrianguloMiss);
	// triangulo->print();

	for(int i = 0; i < intTrianguloMiss.size(); i++){
		intTrianguloMiss[i].print();
	}

	Reta *retaTrianguloHit = new Reta(Ponto(0.1, 0.2, -1.0), Vetor(-0.2, 0.0, -1.0));
	vector<Ponto> intTrianguloHit = triangulo->intRaio(*retaTrianguloHit);
	triangulo->print();

	for(int i = 0; i < intTrianguloHit.size(); i++){
		intTrianguloHit[i].print();
	}
		*/

	cout << "\n---------Teste de Cubo-------------------" << endl;
	Cubo* cubo = new Cubo(Ponto(0.0, 0.0, 0.0), 2.0);
	Reta* retaCuboMiss = new Reta(Ponto(2.0, 2.0, -1.0), Vetor(0.0, 0.0, -1.0));
	Reta* retaCuboHit = new Reta(Ponto(1.0, 0.0, -1.0), Vetor(-1.0, 0.0, -1.0));


	cout << "CUBO" << endl;
	cubo->print();
	cout << endl;

	vector<Ponto> intCuboHit = cubo->intRaio(*retaCuboHit);
	vector<Ponto> intCuboMiss = cubo->intRaio(*retaCuboMiss);

	cout << "\ninicio de teste que deve errar: ";
	for (int i = 0; i < intCuboMiss.size(); i++) {
		intCuboMiss[i].print();
	}

	cout << "\ninicio de teste que deve acertar:\n";
	for (int i = 0; i < intCuboHit.size(); i++) {
		intCuboHit[i].print();
	}

	cout << "\ninicio de teste das normais nos pontos de intereseção:\n";
	for (int i = 0; i < intCuboHit.size(); i++) {
		cubo->getNormal(intCuboHit[i])->print();
	}

	/*
	Mundo *mundo = new Mundo(*new Vetor(1,1,1));
	Objeto *cilindro = new Cilindro(*new Ponto(7,0,0), *new Vetor(0,1,0), 3.0, 7.0);
	cilindro->setMaterial(new Vetor(1,1,1));
	mundo->addObjeto(cilindro);

	Observador* observador = new Observador(*new Ponto(0,0,0), *new Ponto(7,2,0), *new Ponto(0,1,0));
	Mundo *obsMundo = mundo->obsMundo(observador);


	Painel *painel = new Painel(obsMundo, 2, 10, 25);
	vector<vector<Cor>> mtrx = painel->getMatrix();
	int pixels=25;
	for (int i = 0; i < pixels; i++){
		for (int j = 0; j < pixels; j++){
			cout << mtrx[i][j].r << "," << mtrx[i][j].g << "," << mtrx[i][j].b << " - ";
		}
		cout << endl;
	}


	cout << "KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK \n\n";
	Reta *reta = new Reta(Ponto(2.0, 2.0, -1.0), Vetor(0.0, 0.0, -1.0));


	vector<pair<double, A*>> as;
	A* a = new B();
	a->setNumber(10);
	as.push_back(make_pair(1, a));
	as.push_back(make_pair(2, new B()));
	as.push_back(make_pair(3, new C()));

	cout << as.front().second->getNumber();

	for(vector<A*>::iterator i=as.begin(); i != as.end(); i++){


		for(vector<Ponto>::iterator it=p.begin(); it != p.end(); it++)
			(*it).print();


	}


	A* b = new B();

	b->setNumber(20);
	cout << b->getNumber();
*/
}

// ################### FIM DE CÓDIGO DE TESTES #####################################
