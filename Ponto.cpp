#include<iostream>
#include<list>

using namespace std;

class Ponto {
    protected:
        int id = 0;
        double x;
        double y;
        double z;
        list<float> cor;

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

        list<float> getCor() {
            return this->cor;
        }
        
        void setCor(float red, float green, float blue) {
            this->cor = {red, green, blue};
        }

        void print() {
            cout << "Ponto X:" << this->x <<"; Y:" << this->y << "; Z:" << this->z << "\n" << endl;
        }
};