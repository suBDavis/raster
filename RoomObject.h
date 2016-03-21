#ifndef ROOMOBJECT_H
#define ROOMOBJECT_H
#include "v3.h"
#include "Phong.h"
#include "Light.h"
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
    virtual void shade(int shader_mode, std::vector<Light> *lights, v3 *camera) = 0;
};

#endif // ROOMOBJECT_H
