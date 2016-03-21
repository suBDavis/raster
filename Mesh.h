#ifndef MESH_H
#define MESH_H
#include <armadillo>
#include <vector>
#include <sstream>
#include <string>
#include "v3.h"
#include "Triangle.h"
#include "Phong.h"
#include "Light.h"

class Mesh
{
public:
    Mesh(){};
    Mesh(v3 center, Phong p);
    Mesh(v3 center, Phong p, std::vector<Triangle> triangles);
    ~Mesh(){};

    /* the virtual methods I must implement */
    v3 get_ortho(v3 *point);
    v3 get_point_above(v3 *point);
    bool is_reflective();
    void transform(mat *transform);
    Phong get_phong();
    std::string to_str();
    std::vector<Triangle> get_triangles();
    void shade(int shader_mode, std::vector<Light> *lights, v3 *camera);
    
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
    /* internal shading method to determine shade by normal */
    v3 shade_by_norm(v3 norm, v3 vertex, v3 *camera, std::vector<Light> *lights);
    /* interpolate */
    static v3 interpolate(v3 p, Triangle tri);
    
        /* Static Methods */
    static mat44 uniform_scale_transform(double k){
        /* takes a scalar k and returns a 4x4 homogeneous matrix */
        mat44 t= {{ k, 0, 0, 0 },
                  { 0, k, 0, 0 },
                  { 0, 0, k, 0 },
                  { 0, 0, 0, 1 }};
        return t;
    }
    
    static mat44 nonuniform_scale_transform(double x, double y, double z){
        /* takes a scalar k and returns a 4x4 homogeneous matrix */
        mat44 t= {{ x, 0, 0, 0 },
                  { 0, y, 0, 0 },
                  { 0, 0, z, 0 },
                  { 0, 0, 0, 1 }};
        return t;
    }
    static mat44 translate_transform(v3 new_point){
        /* Takes a vector and makes a matrix to translate it there */
        double x = new_point.x;
        double y = new_point.y;
        double z = new_point.z;
        mat44 t= {{1,0,0,x},
                  {0,1,0,y},
                  {0,0,1,z},
                  {0,0,0,1}};
        return t;
    }
    v3 center;
    
private:
    Phong phong;
    std::vector<Triangle> triangles;
};

#endif // MESH_H
