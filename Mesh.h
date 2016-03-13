#ifndef MESH_H
#define MESH_H
#include <armadillo>
#include <vector>
#include <sstream>
#include <string>
#include "RoomObject.h" // Base class: RoomObject
#include "v3.h"
#include "Triangle.h"
#include "Phong.h"

class Mesh : public RoomObject
{
public:
    Mesh(){};
    Mesh(v3 center, Phong p);
    Mesh(v3 center, Phong p, std::vector<Triangle> triangles);
    ~Mesh(){};

    /* the virtual methods I must implement */
    virtual v3 get_ortho(v3 *point);
    virtual v3 get_point_above(v3 *point);
    virtual bool is_reflective();
    virtual void transform(mat *transform);
    virtual Phong get_phong();
    virtual std::string to_str();
    virtual std::vector<Triangle> get_triangles();
    virtual void shade(int shader_mode, std::vector<Light> *lights, v3 *camera);
    
    /* static method to generate a unit sphere centered at 0 0 0*/
    static std::vector<Triangle> generate_unit_sphere(int width, int height);
    /* static method to load a mesh from an obj file */
    static std::vector<Triangle> load_from_file(const char* path);
    /* set triangle vector to the input */
    void set_triangles( std::vector<Triangle> triangles);
    /* just find out how many triangles are in the mesh */
    int num_triangles();
    /* add triangles to the mesh */
    void add_triangle(Triangle t);
    
private:
    v3 center;
    std::vector<Triangle> triangles;
    Phong phong;
};

#endif // MESH_H
