#include "Reta.cpp"

int main() {

    double resultado;                    //Escalar qualquer
    Ponto *ponto1 = new Ponto(1,1,1);
    Vetor *vetor1 = new Vetor(1,1,1);   //Vetores para testes
    Vetor *vetor2 = new Vetor(2,2,2);
    Vetor *vetor3;
    Vetor *vetor4;
    Vetor *vetor5 = new Vetor(1,2,0);
    Vetor *vetor6 = new Vetor(3,-2,0);
    Vetor *vetor7 = new Vetor(0,0,1);

    // **********INICIO TESTE DA CLASSE VETOR***************

    cout << "-----------Teste print------------" << endl;
    vetor1->print();
    vetor2->print();

    cout << "------------Teste Produto Escalar------------" << endl;
    resultado = vetor1->produtoEscalar(*vetor2);
    cout << resultado << endl;

    cout << "------------Teste Multiplicação por Escalar-----------" << endl;
    vetor3 = vetor2->multEscalar(4);
    vetor3->print();
    vetor3 = vetor2->multEscalar(0);
    vetor3->print();
    
    cout << "--------------Teste Cálculo da Norma------------" << endl;
    resultado = vetor1->calcularNorma();
    cout << "vetor1 - Norma: " << resultado << endl;
    cout << "vetor2 - Norma: " << resultado << endl;


    cout << "--------------Teste Normalizar----------" << endl;
    vetor4 = new Vetor(4,2,8);
    vetor4 = vetor4->normalizar();
    vetor4->print();

    cout << "---------------Teste do operador + --------------- " << endl;
    *vetor3 = *vetor1 + *vetor2;
    vetor3->print();

    cout << "---------------Teste do operador - ----------------" << endl;
    *vetor3 = *vetor1 - *vetor2;
    vetor3->print();

    cout << "---------------Teste do operador * (produto escalar)---------" << endl;
    resultado = *vetor1 * *vetor2;
    cout << "produto escalar: " << resultado << endl;

    cout << "-----------Teste Produto Vetorial------------------" << endl;
    vetor3 = vetor5->produtoVetorial(*vetor6);
    vetor3->print();

    //****************FIM TESTES DA CLASSE VETOR******************
    
    //****************TESTES DA CLASSE RETA***********************
    cout << "---------Teste de instanciação da reta e print------------------" << endl;
    Reta *reta1 = new Reta(*ponto1, *vetor7);
    reta1->print();

    cout << "---------Teste do ponto atingido-------" << endl;
    Ponto *ponto2 = reta1->pontoAtingido(3);
    ponto2->print();

    /*int c = reta1->minhaSoma(2,3);
    cout << c;
    return 0;*/
}