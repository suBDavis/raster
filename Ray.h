#ifndef CAMERA_H
#define CAMERA_H
#include "v3.h"

class Ray
{
public:
    Ray();
    Ray(v3 point, v3 direction);
    ~Ray();
    v3 point;
    v3 direction;
};

#endif // CAMERA_H

