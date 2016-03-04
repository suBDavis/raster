#ifndef ROOMOBJECT_H
#define ROOMOBJECT_H
#include "v3.h"
#include "Phong.h"
#include <armadillo>
#include <string>
using namespace arma;

class RoomObject
{
public:
    virtual ~RoomObject(){}
    
    /* Public methods */
    virtual Phong get_phong() = 0;
    virtual v3 get_ortho(v3 *point) = 0;
    virtual v3 get_point_above(v3 *point) = 0;
    virtual bool is_reflective() = 0;
    virtual void transform(mat transform) = 0;
    virtual std::string to_str() = 0;
    
    /* Static Methods */
    static mat44 uniform_scale_transform(double k){
        /* takes a scalar k and returns a 4x4 homogeneous matrix */
        mat44 t= {{ k, 0, 0, 0 },
                  { 0, k, 0, 0 },
                  { 0, 0, k, 0 },
                  { 0, 0, 0, 1 }};
        return t;
    }
};

#endif // ROOMOBJECT_H
