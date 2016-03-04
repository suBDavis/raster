#include "Triangle.h"

Triangle::Triangle( v3 triple[3] ){
    p1 = triple[0];
    p2 = triple[1];
    p3 = triple[2];
    phong = Phong();
}

Triangle::Triangle( v3 triple[3] , Phong p){
    p1 = triple[0];
    p2 = triple[1];
    p3 = triple[2];
    phong = p;
}

v3 Triangle::get_ortho(v3 *point){}

v3 Triangle::get_point_above(v3 *point){}

bool Triangle::is_reflective(){}

Phong Triangle::get_phong(){ return this->phong; }

void Triangle::transform(mat t_mat)
{
    if (t_mat.n_cols == 4 && t_mat.n_rows == 4){
        //this is a 4x4
        p1 = p1.transform_4(t_mat);
        p2 = p2.transform_4(t_mat);
        p3 = p3.transform_4(t_mat);
    } else if (t_mat.n_cols == 3 && t_mat.n_rows == 3) {
        //this is a 3x3
    }
}

std::string Triangle::to_str(){
    std::stringstream ss;
    ss << p1.to_str() << " " <<  p2.to_str() << " " << p3.to_str() << std::endl;
    return ss.str();
}

