#ifndef MESH_H
#define MESH_H
#include <armadillo>
#include <vector>
#include "RoomObject.h" // Base class: RoomObject
#include "v3.h"
#include "Triangle.h"

class Mesh : public RoomObject
{
public:
    Mesh(){}
    Mesh(v3 center);
    Mesh(v3 center, std::vector<Triangle> triangles);
    ~Mesh(){}

    /* the virtual methods I must implement */
    virtual v3 get_ortho(v3 *point);
    virtual v3 get_point_above(v3 *point);
    virtual bool is_reflective();
    virtual void transform(mat transform);
    
    /* static method to generate a unit sphere centered at 0 0 0*/
    static std::vector<Triangle> generate_unit_sphere(int width, int height);
    /* set triangle vector to the input */
    void set_triangles( std::vector<Triangle> triangles);
    
private:
    v3 center;
    std::vector<Triangle> triangles;
};

#endif // MESH_H
