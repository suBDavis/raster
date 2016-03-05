#ifndef VECTOR3_H
#define VECTOR3_H
#include <armadillo>
#include <sstream>
#include <string>
using namespace arma;

class v3
{
public:
    double x;
    double y;
    double z;
    double c; //the extra one

    v3();
    ~v3(){}
    v3(double x, double y, double z);
    v3(double xi, double yi, double zi, double ci);
    v3 Scale (double scalar);
    double dot(v3 b);
    v3 Unit();
    v3 minus(v3 b);
    v3 add_const(double c);
    v3 add(v3 b);
    v3 multiply(v3 b);
    v3 cross(v3 b);
    double Magnitude();
    std::string to_str();
    
    /* Support for armadillo operations - get the one that makes the most sense */
    //rowvec3 get_rowvec();
    //colvec3 get_colvec();
    rowvec4 get_rowvec4();
    colvec4 get_colvec4();
    
    v3 transform_4(mat44 t_mat);
    

private:

};

#endif // VECTOR3_H
