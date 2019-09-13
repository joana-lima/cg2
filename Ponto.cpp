#include<iostream>
#include<list>
using namespace std;

class Ponto {
    protected:
        double x;
        double y;
        double z;
        list<float> cor;

    public:
        Ponto(double x, double y, double z) {
            this->x = x;
            this->y = y;
            this->z = z;
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

        void setCor(float red,float green ,float blue) {
            this->cor = {red, green, blue};
        }

        list<float> getCor() {
            return this->cor;
        }
};