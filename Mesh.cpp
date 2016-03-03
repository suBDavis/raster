#include "Mesh.h"
#include <stdio.h>
#include <math.h>

Mesh::Mesh(v3 center, Phong p) : center(center), phong(p) {}
Mesh::Mesh(v3 center, Phong p, std::vector<Triangle> triangles): center(center), phong(p), triangles(triangles) {}

/* Instance Methods  */
std::vector<Triangle> Mesh::generate_unit_sphere(int width, int height){
    
    int* gIndexBuffer    = NULL; // Vertex indices for the triangles.
    
    float theta, phi;
    int t;
    
    int gNumVertices    = (height - 2) * width + 2;
    int gNumTriangles   = (height - 2) * (width - 1) * 2;
    
    v3 vertices[gNumVertices];

    gIndexBuffer = new int[3*gNumTriangles];
    
    t = 0;
    for (int j = 1; j < height-1; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            theta = (float) j / (height-1) * M_PI;
            phi   = (float) i / (width-1)  * M_PI * 2;
            
            float   x   = sinf(theta) * cosf(phi);
            float   y   = cosf(theta);
            float   z   = -sinf(theta) * sinf(phi);
            
            vertices[t] = v3(x, y, z);
            
            t++;
        }
    }
    
    vertices[t] = v3(0,1,0);
    
    t++;
    
    vertices[t] = v3(0, -1, 0);
    
    t++;
    
    t = 0;
    for (int j = 0; j < height-3; ++j)
    {
        for (int i = 0; i < width-1; ++i)
        {
            gIndexBuffer[t++] = j*width + i;
            gIndexBuffer[t++] = (j+1)*width + (i+1);
            gIndexBuffer[t++] = j*width + (i+1);
            gIndexBuffer[t++] = j*width + i;
            gIndexBuffer[t++] = (j+1)*width + i;
            gIndexBuffer[t++] = (j+1)*width + (i+1);
        }
    }
    for (int i = 0; i < width-1; ++i)
    {
        gIndexBuffer[t++] = (height-2)*width;
        gIndexBuffer[t++] = i;
        gIndexBuffer[t++] = i + 1;
        gIndexBuffer[t++] = (height-2)*width + 1;
        gIndexBuffer[t++] = (height-3)*width + (i+1);
        gIndexBuffer[t++] = (height-3)*width + i;
    }
    
    std::vector<Triangle> mesh;
    
    for (int i = 0; i < gNumTriangles; i++){
        int k0 = gIndexBuffer[3*i + 0];
        int k1 = gIndexBuffer[3*i + 1];
        int k2 = gIndexBuffer[3*i + 2];
        
        v3 triangle_vertices[3] = { vertices[k0], vertices[k1], vertices[k2] };
        Triangle t = Triangle( triangle_vertices );
        
        mesh.push_back(t);
    }
    
    return mesh;
}
void Mesh::set_triangles( std::vector<Triangle> triangles){
    this->triangles = triangles;
}

int Mesh::num_triangles(){
    return this->triangles.size();
}

void Mesh::add_triangle(Triangle t){
    this->triangles.push_back(t);
}

/* Virutal Methods */
v3 Mesh::get_ortho(v3 *point){ return v3(); }
v3 Mesh::get_point_above(v3 *point){ return v3(); }
bool Mesh::is_reflective(){ return false; }

Phong Mesh::get_phong(){ return this->phong; }

/* returns a string with all the triangles */
std::string Mesh::to_str(){
    std::stringstream ss;
    for(std::vector<Triangle>::iterator it = this->triangles.begin(); it != this->triangles.end(); ++it) {
        ss << it->to_str();
    }
    return ss.str();
}

/* Iterate over the triangles in the mesh and transform them */
void Mesh::transform(mat t_mat){
    for(std::vector<Triangle>::iterator it = this->triangles.begin(); it != this->triangles.end(); ++it) {
        //it.transform(t_mat);
    }
}