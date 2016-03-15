#include "Mesh.h"
#include <stdio.h>
#include <math.h>
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

/* comment to test mode stuff */
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
std::vector<Triangle> Mesh::load_from_file(const char* path){
    
    std::string inputfile = path;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::vector<Triangle> obj_mesh;
    std::vector<v3> all_vertices;

    std::string err;
    bool ret = tinyobj::LoadObj(shapes, materials, err, inputfile.c_str());

    if (!err.empty()) { // `err` may contain warning message.
      std::cerr << err << std::endl;
    }
    
    std::cout << "Loaded " << path << " from file." << std::endl;
    std::cout << "# of shapes    : " << shapes.size() << std::endl;
    std::cout << "# of materials : " << materials.size() << std::endl;
    
    for (size_t i = 0; i < shapes.size(); i++) {

        size_t indexOffset = 0;
        for (size_t n = 0; n < shapes[i].mesh.num_vertices.size(); n++) {
            int ngon = shapes[i].mesh.num_vertices[n];
            for (size_t f = 0; f < ngon; f++) {
                unsigned int v = shapes[i].mesh.indices[indexOffset + f];
                printf("  face[%ld] v[%ld] = (%f, %f, %f)\n", n,
                    shapes[i].mesh.positions[3*v+0],
                    shapes[i].mesh.positions[3*v+1],
                    shapes[i].mesh.positions[3*v+2]);
                
                all_vertices.push_back( v3((double)shapes[i].mesh.positions[3*v+0], (double)shapes[i].mesh.positions[3*v+1], (double)shapes[i].mesh.positions[3*v+2]) );

            }
        indexOffset += ngon;
        }

    }
    std::cout << all_vertices.size() << std::endl;
    
    for (unsigned int v = 0; v < all_vertices.size() / 3; v++){
        v3 triangle_vertices[3] = {
            all_vertices[v*3+0],
            all_vertices[v*3+1],
            all_vertices[v*3+2]
        };
        printf( "%f, %f \n",triangle_vertices[0].x ,triangle_vertices[0].y);
        Triangle t = Triangle( triangle_vertices );
        obj_mesh.push_back(t);
    }
    
    std::cout << obj_mesh.size() << std::endl;
    
    
    return obj_mesh;
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
std::vector<Triangle> Mesh::get_triangles(){ return triangles; }

/* shades all the triangles in the mesh */
void Mesh::shade(int shader_mode, std::vector<Light> *lights, v3 *camera){
    for(std::vector<Triangle>::iterator it = this->triangles.begin(); it != this->triangles.end(); ++it) {
        
        v3 norm = it->get_ortho();
        v3 I;
        v3 Ia; //ambient
        v3 Id; //diffuse
        v3 Is; //specular
        
        //iterate over all the lights
        for (std::vector<Light>::iterator li = lights->begin(); li != lights->end(); ++li){
            
            //I did a nasty thing by just picking a point at random.
            v3 vector_to_light = li->point.minus(it->p3).Unit();
            
            
            /*
             * Flat Shading
             */
 
            //Ambient Lighting
            v3 li_color = li->color;
            Ia = Ia.add(v3(phong.ka.x * li_color.x, 
                           phong.ka.y * li_color.y,
                           phong.ka.z * li_color.z));
            
            //Diffuse Lighting
            double dot = norm.dot(vector_to_light);
            if (dot >= 0){
                Id = Id.add(v3(phong.kd.x * dot * li_color.x,
                                phong.kd.y * dot * li_color.y,
                                phong.kd.z * dot * li_color.z));
            //Specular Shading
            
            /*
             * Gorard Shading
             */

 
            } else {
                Id = Id.add(v3(0,0,0));
            }
            
            I = I.add(Ia).add(Id);
            
        }
        
        //set the flat color of the triangle.
        it->flat_color = I;
    }
}

/* returns a string with all the triangles */
std::string Mesh::to_str(){
    std::stringstream ss;
    for(std::vector<Triangle>::iterator it = this->triangles.begin(); it != this->triangles.end(); ++it) {
        ss << it->to_str();
    }
    return ss.str();
}

/* Iterate over the triangles in the mesh and transform them */
void Mesh::transform(mat *t_mat){
    for(std::vector<Triangle>::iterator it = this->triangles.begin(); it != this->triangles.end(); ++it) {
        it->transform(*t_mat);
    }
}