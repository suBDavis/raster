#ifndef ROOMOBJECT_H
#define ROOMOBJECT_H
#include "v3.h"
#include "Phong.h"
#include "Triangle.h"
#include <armadillo>
#include <string>
#include <vector>

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
    virtual void transform(mat *transform) = 0;
    virtual std::string to_str() = 0;
    virtual std::vector<Triangle> get_triangles() = 0;
    
    /* Static Methods */
    static mat44 uniform_scale_transform(double k){
        /* takes a scalar k and returns a 4x4 homogeneous matrix */
        mat44 t= {{ k, 0, 0, 0 },
                  { 0, k, 0, 0 },
                  { 0, 0, k, 0 },
                  { 0, 0, 0, 1 }};
        return t;
    }
    
    static mat44 nonuniform_scale_transform(double x, double y, double z){
        /* takes a scalar k and returns a 4x4 homogeneous matrix */
        mat44 t= {{ x, 0, 0, 0 },
                  { 0, y, 0, 0 },
                  { 0, 0, z, 0 },
                  { 0, 0, 0, 1 }};
        return t;
    }
    static mat44 translate_transform(v3 new_point){
        /* Takes a vector and makes a matrix to translate it there */
        double x = new_point.x;
        double y = new_point.y;
        double z = new_point.z;
        mat44 t= {{1,0,0,x},
                  {0,1,0,y},
                  {0,0,1,z},
                  {0,0,0,1}};
        return t;
    }
};

#endif // ROOMOBJECT_H
