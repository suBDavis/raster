#include <stdio.h>
#include <armadillo>
#include <vector>
#include "v3.h"
#include "RoomObject.h"
#include "Mesh.h"
#include "Triangle.h"
using namespace arma;

/* Method Declarations */
int unit_tests();

int main(int argc, char **argv)
{
    unit_tests();
    return 0;
}

int unit_tests(){
    Mesh m1 = Mesh( v3(0,0,0) );
    
    std::vector<Triangle> triangles = Mesh::generate_unit_sphere(32, 16);
    Mesh m2 = Mesh( v3(0,0,0) , triangles);
    
    return 0;
}
