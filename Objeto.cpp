#include "Ponto.cpp"

class Objeto {
    protected:
        int id = 0;
        list<Ponto> vertices;
        list<list<Ponto>> arestas;
        list<list<Ponto>> faces;
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
            cout << "Objeto - ID: " << this->id <<endl;
        }

        bool getVisibilidade(){
            return this->visibilidade;
        }
        
        void setVisibilidade(bool visibilidade){
            this->visibilidade = visibilidade;
        }

        void adicionarVertice(Ponto vertice){
            this->vertices.push_front(vertice);
        }

        void adicionarAresta(Ponto vertice1, Ponto vertice2){
            this->arestas.push_front({vertice1, vertice2});
        }

        void adicionarFace(Ponto vertice1, Ponto vertice2, Ponto vertice3){
            this->faces.push_front({vertice1, vertice2, vertice3});
        }

        list<Ponto> getVertices(){
            return this->vertices;
        }

        list<list<Ponto>> getArestas(){
            return this->arestas;
        }

        list<list<Ponto>> getFaces(){
            return this->faces;
        }

};