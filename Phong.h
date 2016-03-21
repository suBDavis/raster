#ifndef PHONG_H
#define PHONG_H
#include "v3.h"

class Phong
{
public:
    Phong(){}
    Phong(v3 ka, v3 kd, v3 ks, double spower);
    ~Phong(){}

    v3 ka;
    v3 kd;
    v3 ks;
    double spower;
};

#endif // PHONG_H
