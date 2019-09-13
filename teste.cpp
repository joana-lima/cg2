#include "Vetor.cpp"

int main() {

    Vetor *vetor1 = new Vetor(1,1,1);
    Vetor *vetor2 = new Vetor(2,2,2);
    Vetor *vetor3 = vetor1->soma(*vetor2);

    vetor3->printCoordenadas();

    cout << "teste" << endl;
    return 0;
}