#ifndef ROOMOBJECT_H
#define ROOMOBJECT_H
#include "v3.h"
#include <armadillo>
using namespace arma;

class RoomObject
{
public:
    ~RoomObject(){}
    
    /* Public methods */
    // virtual Phong get_phong() = 0;
    virtual v3 get_ortho(v3 *point) = 0;
    virtual v3 get_point_above(v3 *point) = 0;
    virtual bool is_reflective() = 0;
    virtual void transform(mat transform) = 0;
};

#endif // ROOMOBJECT_H
