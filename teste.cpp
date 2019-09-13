#include "Vetor.cpp"

int main() {

    double resultado;                    //Escalar qualquer
    Vetor *vetor1 = new Vetor(1,1,1);   //Vetores para testes
    Vetor *vetor2 = new Vetor(2,2,2);
    Vetor *vetor3;

    // **********INICIO TESTE DA CLASSE VETOR***************

    cout << "-----------Teste printCoordenadas------------" << endl;
    vetor1->printCoordenadas();
    vetor2->printCoordenadas();

    cout << "------------Teste Produto Escalar------------" << endl;
    resultado = vetor1->produtoEscalar(*vetor2);
    cout << resultado << endl;

    cout << "------------Teste Multiplicação por Escalar-----------" << endl;
    vetor3 = vetor2->multEscalar(4);
    vetor3->printCoordenadas();
    vetor3 = vetor2->multEscalar(0);
    vetor3->printCoordenadas();
    
    cout << "--------------Teste Cálculo da Norma------------" << endl;
    resultado = vetor1->calcularNorma();
    cout << "vetor1 - Norma: " << resultado << endl;
    cout << "vetor2 - Norma: " << resultado << endl;


    cout << "--------------Teste Normalizar----------" << endl;
    Vetor *vetor4 = new Vetor(4,2,8);
    vetor4 = vetor4->normalizar();
    vetor4->printCoordenadas();

    cout << "---------------Teste do operador + --------------- " << endl;
    *vetor3 = *vetor1 + *vetor2;
    vetor3->printCoordenadas();

    cout << "---------------Teste do operador - ----------------" << endl;
    *vetor3 = *vetor1 - *vetor2;
    vetor3->printCoordenadas();


    //****************FIM TESTES DA CLASSE VETOR******************

    return 0;
}