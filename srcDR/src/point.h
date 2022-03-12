#ifndef POINT_H
#define POINT_H



class Ponto {
private:
    float x, y, z;
public:
    Ponto();
    Ponto(float, float, float);
    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }
};


#endif // POINT_H