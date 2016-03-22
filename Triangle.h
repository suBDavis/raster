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
    Triangle( v3 triple[3] , int p1i, int p2i, int p3i);
    ~Triangle(){}
    
    v3 get_ortho();
    v3 get_point_above(v3 *point);
    bool is_reflective();
    void transform(mat t_mat);
    std::string to_str();
    void set_neighbors(std::vector<v3> neighbors[3]);
    v3 point_norm(int dex);
    //sets the point after we get to world space.
    void mark_point();
    
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
    std::vector<v3> *neighbors;
    std::vector<v3> n1;
    std::vector<v3> n2;
    std::vector<v3> n3;
    int p1i;
    int p2i;
    int p3i;
    v3 c1;
    v3 c2;
    v3 c3;
    v3 flat_color;

    v3 point_1;
    v3 point_2;
    v3 point_3;
};

#endif // TRIANGLE_H
