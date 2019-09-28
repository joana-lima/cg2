#include "Objetos.cpp"



using namespace std;

class A{
    protected:
        int number;
    public:


    virtual vector<Ponto> nuwaa(Reta reta){
        vector<Ponto> p;
        p.push_back(*new Ponto(0,0,0));
        

        return p;}
    
    void setNumber(int number){
        this->number = number;
    }

    int getNumber(){
        return number;
    }


};

class B: public A{
    public:
    vector<Ponto> nuwaa(Reta reta){
        vector<Ponto> p;
        p.push_back(*new Ponto(1,0,0));
        

        return p;
    }

};

class C: public A{
    public:
    vector<Ponto> nuwaa(Reta reta){
        vector<Ponto> p;
        p.push_back(*new Ponto(2,0,0));
        

        return p;
    }
};

int teste() {
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
    Objeto *obj1 = new Objeto();
    Ponto *v1 = new Ponto(0, 0, 0);
    Ponto *v2 = new Ponto(1, 0, 0);
    Ponto *v3 = new Ponto(0, 1, 0);
    Ponto *v4 = new Ponto(0, 0, 1);

    obj1->setVisibilidade(false);

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

    Reta *retaTrianguloHit = new Reta(Ponto(0.1, 0.2, -1.0), Vetor(0.0, 0.0, -1.0));
    vector<Ponto> intTrianguloHit = triangulo->intRaio(*retaTrianguloHit);
    // triangulo->print();

    for(int i = 0; i < intTrianguloHit.size(); i++){
        intTrianguloHit[i].print();
    }

    cout << "\n---------Teste de Cubo-------------------" << endl;
    Cubo *cubo = new Cubo(Ponto(0.0, 0.0, 0.0), 2.0, Vetor(0.0, 1.0, 0.0));
    Reta *retaCuboMiss = new Reta(Ponto(2.0, 2.0, -1.0), Vetor(0.0, 0.0, -1.0));
    Reta *retaCuboHit = new Reta(Ponto(0.0, 0.0, -1.0), Vetor(0.0, 0.0, -1.0));

    
    cout << "CUBO" << endl;
    cubo->print();
    cout << endl;

    vector<Ponto> intCuboHit = cubo->intRaio(*retaCuboHit);
    vector<Ponto> intCuboMiss = cubo->intRaio(*retaCuboMiss);

    cout << "\ninicio de teste que deve errar: ";
    for(int i = 0; i < intCuboMiss.size(); i++){
        intCuboMiss[i].print();
    }

    cout << "\ninicio de teste que deve acertar:\n";
    for(int i = 0; i < intCuboHit.size(); i++){
        intCuboHit[i].print();
    }*/




    Mundo *mundo = new Mundo(*new Vetor(1,1,1));
    Objeto *cilindro = new Cilindro(*new Ponto(7,0,0), *new Vetor(0,1,0), 3.0, 7.0);
    cilindro->setMaterial(new Vetor(1,1,1));
    mundo->addObjeto(cilindro);

    Observador* observador = new Observador(*new Ponto(0,0,0), *new Ponto(7,2,0), *new Ponto(0,1,0));
    Mundo *obsMundo = mundo->obsMundo(*observador);  
    

    Painel *painel = new Painel(obsMundo, 2, 10, 25);
    vector<vector<Color>> mtrx = painel->getMatrix();
    int pixels=25; 
    for (int i = 0; i < pixels; i++){
        for (int j = 0; j < pixels; j++){
            cout << mtrx[i][j].r << "," << mtrx[i][j].g << "," << mtrx[i][j].b << " - ";
        }
        cout << endl;
    }

/*

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

    return 0;
}