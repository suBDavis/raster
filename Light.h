#ifndef LIGHT_H
#define LIGHT_H
#include "v3.h"

class Light
{
public:
    Light(){}
    Light(v3 point, v3 color);
    ~Light(){}
private:
    v3 color;
    v3 point;
};

#endif // LIGHT_H