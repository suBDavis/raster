#include "Triangle.h"
#include <stdio.h>
#include <stdexcept>
#include <vector>

Triangle::Triangle( v3 triple[3] ){
    p1 = triple[0];
    p2 = triple[1];
    p3 = triple[2];
}

Triangle::Triangle(v3 triple[3], int p1i, int p2i, int p3i) : p1i(p1i), p2i(p2i), p3i(p3i){
    p1 = triple[0];
    p2 = triple[1];
    p3 = triple[2];
}

v3 Triangle::get_ortho(){
    v3 a = p1.minus(p2);
    v3 b = p3.minus(p2);
    v3 cross = b.cross(a).Unit();
    return cross;
}

void Triangle::set_neighbors(std::vector<v3> neighbors[3]){
    n1 = neighbors[0];
    n2 = neighbors[1];
    n3 = neighbors[2];
}

v3 Triangle::point_norm(int dex){
    v3 norm;
    
    if (dex == 0){
        for (unsigned int i = 0; i < n1.size(); i++){
            norm = norm.add(n1[i]);
        }
    } else if (dex == 1){
        for (unsigned int i = 0; i < n2.size(); i++){
            norm = norm.add(n2[i]);
        }
    } else {
        for (unsigned int i = 0; i < n3.size(); i++){
            norm = norm.add(n3[i]);
        }
    }
    norm = norm.Unit();
    return norm;   
}

v3 Triangle::get_point_above(v3 *point){}

bool Triangle::is_reflective(){}

void Triangle::transform(mat t_mat)
{
    if (t_mat.n_cols == 4 && t_mat.n_rows == 4){
        //this is a 4x4
        p1 = p1.transform_4(t_mat);
        p2 = p2.transform_4(t_mat);
        p3 = p3.transform_4(t_mat);
        
        //we must also transform all the normals :)
        for (int i = 0; i< n1.size();i++)
            n1[i].transform_4(t_mat);
        for (int i = 0; i< n2.size();i++)
            n2[i].transform_4(t_mat);
        for (int i = 0; i< n3.size();i++)
            n3[i].transform_4(t_mat);

    } else {
        //this is something else
        throw std::invalid_argument( "Received Matrix of Wrong Size" );
    }
}


void Triangle::project(){
    
     mat44 p1t = Triangle::nonuniform_scale_transform( 1/p1.c, 1/p1.c, 1);
     mat44 p2t = Triangle::nonuniform_scale_transform( 1/p2.c, 1/p2.c, 1);
     mat44 p3t = Triangle::nonuniform_scale_transform( 1/p3.c, 1/p3.c, 1);
     
     p1 = p1.transform_4(p1t);
     p2 = p2.transform_4(p2t);
     p3 = p3.transform_4(p3t);
}



std::string Triangle::to_str(){
    std::stringstream ss;
    ss << p1.to_str() << " " <<  p2.to_str() << " " << p3.to_str() << std::endl;
    return ss.str();
}

