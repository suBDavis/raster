#include "Mesh.h"
#include <stdio.h>
#include <math.h>

Mesh::Mesh(v3 center) : center(center){}
Mesh::Mesh(v3 center, std::vector<Triangle> triangles): center(center), triangles(triangles) {}

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
    // The index buffer has now been generated. Here's how to use to determine
    // the vertices of a triangle. Suppose you want to determine the vertices
    // of triangle i, with 0 <= i < gNumTriangles. Define:
    //
    // k0 = gIndexBuffer[3*i + 0]
    // k1 = gIndexBuffer[3*i + 1]
    // k2 = gIndexBuffer[3*i + 2]
    //
    // Now, the vertices of triangle i are at positions k0, k1, and k2 (in that
    // order) in the vertex array (which you should allocate yourself at line
    // 27).
    //
    // Note that this assumes 0-based indexing of arrays (as used in C/C++,
    // Java, etc.) If your language uses 1-based indexing, you will have to
    // add 1 to k0, k1, and k2.
}
void Mesh::set_triangles( std::vector<Triangle> triangles){
    this->triangles = triangles;
}

/* Virutal Methods */
v3 Mesh::get_ortho(v3 *point){ return v3(); }
v3 Mesh::get_point_above(v3 *point){ return v3(); }
bool Mesh::is_reflective(){ return true; }
void Mesh::transform(mat transform){}