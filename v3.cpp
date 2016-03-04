#include "v3.h"
#include <cmath>

v3::v3(){
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

v3::v3(double xi, double yi, double zi){
    x = xi;
    y = yi;
    z = zi;
}

v3 v3::Scale (double scalar){
    v3 v (x * scalar,y * scalar,z * scalar);
    return v;
}
v3 v3::Unit(){
    v3 uv (x, y, z);
    return uv.Scale(1.0 / Magnitude());
}

double v3::Magnitude(){
    return sqrt( x*x + y*y + z*z);
}

v3 v3::add_const(double c){
    v3 v (x+c, y+c, z+c);
    return v;
}
v3 v3::add(v3 b){
    v3 v (x+b.x, y+b.y, z+b.z);
    return v;
}
v3 v3::multiply(v3 b){
    v3 v (x*b.x, y*b.y, z*b.z);
    return v;
}

double v3::dot(v3 b){
    return (x*b.x + y*b.y + z*b.z);
}
v3 v3::cross(v3 b){
    //unimplemented
    double i = y * b.z -  z * b.y;
    double j = z * b.x - x * b.z;
    double k = x * b.y - y * b.x;
    return v3(i,j,k);
}

v3 v3::minus(v3 b){
    v3 v (x - b.x, y - b.y, z - b.z);
    return v;
}

std::string v3::to_str(){
    std::ostringstream strs;
    strs << "< " << x << " " << y << " " << z << " >";
    std::string str = strs.str();
    return str;
}

v3 v3::transform_4(mat44 t_mat){
    colvec4 operand = {x, y, z, 1};
    colvec4 product = t_mat * operand;
    return v3(product[0], product[1], product[1]);
}

colvec4 v3::get_colvec4(){
    colvec4 c = {x, y, z, 1};
    return c;
}

rowvec4 v3::get_rowvec4(){
    rowvec4 r = {x, y, z, 1};
    return r;
}