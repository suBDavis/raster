#include "v3.h"
#include <cmath>

v3::v3(){
    x = 0.0;
    y = 0.0;
    z = 0.0;
    c = 1.0;
}

v3::v3(double xi, double yi, double zi){
    x = xi;
    y = yi;
    z = zi;
    c = 1.0;
}

v3::v3(double xi, double yi, double zi, double ci){
    x = xi;
    y = yi;
    z = zi;
    c = ci;
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

v3 v3::reflect(v3 norm){
    norm = norm.Unit();
    v3 vv = norm.Scale(this->dot(norm) * 2 );
    return this->minus(vv);
}

std::string v3::to_str(){
    std::ostringstream strs;
    strs << "< " << x << " " << y << " " << z << " >";
    std::string str = strs.str();
    return str;
}

v3 v3::transform_4(mat44 t_mat){
    colvec4 operand = {x, y, z, c};
    colvec4 product = t_mat * operand;
//    if (product(3) == -7 && c==1){
//        std::cout << "operand --" << std::endl;
//        operand.print();
//        std::cout << "product --" << std::endl;
//        product.print();
//        std::cout << "t_mat --" <<std::endl;
//        t_mat.print();
//    }
    return v3(product(0), product(1), product(2), product(3));
}

colvec4 v3::get_colvec4(){
    colvec4 cv = {x, y, z, c};
    return cv;
}

rowvec4 v3::get_rowvec4(){
    rowvec4 rv = {x, y, z, c};
    return rv;
}