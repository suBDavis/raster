#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <armadillo>
#include <stdio.h>
#include <string>
#include <sstream>
#include "v3.h"

class Triangle
{
public:
    /* there is currentlly no reason to have a default constructor */
    //Triangle(){}
    /* Constructor for triangles that are part of a mesh */
    Triangle( v3 triple[3] );
    ~Triangle(){}
    
    v3 get_ortho(v3 *point);
    v3 get_point_above(v3 *point);
    bool is_reflective();
    void transform(mat t_mat);
    std::string to_str();
    
    void project();
    
    static mat44 nonuniform_scale_transform(double x, double y, double z){
        /* takes a scalar k and returns a 4x4 homogeneous matrix */
        mat44 t= {{ x, 0, 0, 0 },
                  { 0, y, 0, 0 },
                  { 0, 0, z, 0 },
                  { 0, 0, 0, 1 }};
        return t;
    }

    v3 p1;
    v3 p2;
    v3 p3;
};

#endif // TRIANGLE_H
