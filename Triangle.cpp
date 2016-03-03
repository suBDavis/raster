#include "Triangle.h"

Triangle::Triangle( v3 triple[3] ){
    p1 = triple[0];
    p2 = triple[1];
    p3 = triple[2];
}

v3 Triangle::get_ortho(v3 *point){}
v3 Triangle::get_point_above(v3 *point){}
bool Triangle::is_reflective(){}
void Triangle::transform(mat transform)
{
    //TODO choose either the rowvec or columnvec to multiply by.
}

