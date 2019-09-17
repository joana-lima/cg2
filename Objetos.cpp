#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

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
            cout << "Ponto X:" << this->x <<"; Y:" << this->y << "; Z:" << this->z << endl;
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
        cout << "Vetor X:" << this->x <<"; Y:" << this->y << "; Z:" << this->z << "\n" << endl;
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

    double operator * (Vetor const &obj) {
        double resultado;
        resultado = x*obj.x + y*obj.y + z*obj.z;
        return resultado;
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

vector<double> equacaoSegundoGrau(double a, double b, double c) {
    double delta = b*b - 4*a*c;
    double x1, x2;
    vector<double> escalares;
    if(delta < 0)
        return escalares;
    else {
        x1 = (-b + sqrt(delta))/2*a;
        escalares.push_back(x1);
        if(delta == 0)
            return escalares;
        else {
            x2 = (-b - sqrt(delta))/2*a;
            escalares.push_back(x2);
            return escalares;
        }
    }
}

class Objeto {
    protected:
    int id = 0;
    vector<Ponto> vertices;
    vector<vector<Ponto>> arestas;
    vector<vector<Ponto>> faces;
    bool visibilidade;

    public:
    Objeto() {
        this->vertices = {};
        this->arestas = {{}};
        this->faces = {{}};
        this->visibilidade = true;
        this->id++;
    }

    void print(){
        cout << "Objeto - ID: " << id <<endl;
        cout << "Visibilidade: " << visibilidade ? "true" : "false" << endl;

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

class Plano {
    protected:
    Ponto ponto;
    Vetor normal;

    public:
    Plano(Ponto ponto, Vetor normal) {
        this->ponto = ponto;
        this->normal = normal;
    }

    Ponto *getPonto() {
        return &this->ponto;
    }

    Vetor *getNormal() {
        return &this->normal;
    }

    bool pertencePlano(Ponto ponto) {
        Vetor *distancia = vetorDistancia(this->ponto, ponto);
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
            Vetor *vetor = vetorDistancia(*reta.getPonto(),this->ponto);
            double numerador = *vetor * this->normal;
            double tInt = numerador/temp;
            pontos.push_back(*reta.pontoAtingido(tInt));
            return pontos;
        }
    }
};

class Triangulo : Objeto {
    public:
    Triangulo() : Objeto() {}
    
    Triangulo(Ponto ponto1, Ponto ponto2, Ponto ponto3) {
        this->adicionarVertice(ponto1);
        this->adicionarVertice(ponto2);
        this->adicionarVertice(ponto3);

        this->adicionarAresta(ponto1, ponto2);
        this->adicionarAresta(ponto2, ponto3);
        this->adicionarAresta(ponto3, ponto1);

        this->adicionarFace(ponto1, ponto2, ponto3);
    }

    vector<Ponto> intRaio(Reta raio) {

        Vetor *p1p2 = vetorDistancia(vertices[1], vertices[0]);
        Vetor *p1p3 = vetorDistancia(vertices[2], vertices[0]);
        Vetor *p2p3 = vetorDistancia(vertices[2], vertices[1]);
        Vetor *p3p1 = vetorDistancia(vertices[0], vertices[2]);
        Vetor *n = p1p2->produtoVetorial(*p1p3)->normalizar();

        Plano *planoTriangulo = new Plano(vertices[0], *n);
        vector<Ponto> pontoInt = planoTriangulo->intRaio(raio);

        if(pontoInt.size() == 0){   return pontoInt;}


    }

};

class Cilindro {
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

    vector<Ponto> intRaio(Reta reta) {
        vector<Ponto> pontosAtingidos;

        //Vetor v
        Vetor *bPo = vetorDistancia(this->base,*reta.getPonto()); //(Po - B)
        double aux = (*bPo * this->normal);                       //(Po - B).u  
        Vetor *vetorAux = this->normal.multEscalar(aux);          //((Po - B).u).u
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

};

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
        this->normal = *normal.normalizar();
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

    double getCossenoGeratriz() {
        return this->altura / sqrt(pow(this->altura,2) + pow(this->raio,2));
    }

    vector<Ponto> intRaio(Reta reta) {
        vector<Ponto> pontosAtingidos;
        //vetor v
        Vetor v = *vetorDistancia(*reta.getPonto(), this->vertice);
    
        //Cálculo dos coeficientes da equaçao do segundo grau
        double a = (*reta.getVetor() * this->normal) * (*reta.getVetor() * this->normal);
        double b = (v * *reta.getVetor()) * pow(this->getCossenoGeratriz(),2) - 
                   (v * this->normal) * (*reta.getVetor() * this->normal);
        double c = pow(v * this->normal,2) - (v * v) * pow(this->getCossenoGeratriz(),2);

        //Achando os escalates da intersecao.
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
};