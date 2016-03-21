#ifndef LIGHT_H
#define LIGHT_H
#include "v3.h"
#include <armadillo>

class Light
{
public:
    Light(){}
    Light(v3 point, v3 color);
    void transform(mat44 trans);
    ~Light(){}
    v3 point;
    v3 color;
};

#endif // LIGHT_H