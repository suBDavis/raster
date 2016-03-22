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
    
    std::vector<v3> normals[gNumVertices];
    
    std::vector<Triangle> mesh;
    
    for (int i = 0; i < gNumTriangles; i++){
        int k0 = gIndexBuffer[3*i + 0];
        int k1 = gIndexBuffer[3*i + 1];
        int k2 = gIndexBuffer[3*i + 2];
        
        v3 triangle_vertices[3] = { vertices[k0], vertices[k1], vertices[k2] };
        Triangle t = Triangle( triangle_vertices , k0, k1, k2 );
        
        v3 norm = t.get_ortho();
        normals[k0].push_back(norm);
        normals[k1].push_back(norm);
        normals[k2].push_back(norm);
        
        mesh.push_back(t);
    }
    
    //iterate over the triangles again and tell it about its neighbors
    for (int i = 0; i < gNumTriangles; i++){
        int k0 = mesh[i].p1i;
        int k1 = mesh[i].p2i;
        int k2 = mesh[i].p3i;
        
        std::vector<v3> neighbors[3] = {normals[k0], normals[k1], normals[k2]};
        mesh[i].set_neighbors(neighbors);
        
        v3 pn = mesh[i].point_norm(0);
        
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
    //bool ret = tinyobj::LoadObj(shapes, materials, err, inputfile.c_str());

    if (!err.empty()) { // `err` may contain warning message.
      std::cerr << err << std::endl;
    }
    
    std::cout << "Loaded " << path << " from file." << std::endl;
    std::cout << "# of shapes    : " << shapes.size() << std::endl;
    std::cout << "# of materials : " << materials.size() << std::endl;
    
    for (size_t i = 0; i < shapes.size(); i++) {

        size_t indexOffset = 0;
        for (size_t n = 0; n < shapes[i].mesh.num_vertices.size(); n++) {
            unsigned int ngon = shapes[i].mesh.num_vertices[n];
            for (size_t f = 0; f < ngon; f++) {
                unsigned int v = shapes[i].mesh.indices[indexOffset + f];
//                printf("  face[%ld] v[%ld] = (%f, %f, %f)\n", n,
//                    shapes[i].mesh.positions[3*v+0],
//                    shapes[i].mesh.positions[3*v+1],
//                    shapes[i].mesh.positions[3*v+2]);
                
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
        //printf( "%f, %f \n",triangle_vertices[0].x ,triangle_vertices[0].y);
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
        
        Triangle tri = *it;
        
        v3 flat_norm = it->get_ortho();
        v3 flat_vertex = it->p1.add(it->p2).add(it->p3).Scale(.33333333333);
        it->flat_color = shade_by_norm(flat_norm, flat_vertex, camera, lights);
        
        v3 p1n = it->point_norm(0);
        it->c1 = shade_by_norm(p1n, it->p1, camera, lights);
        
        v3 p2n = it->point_norm(1);
        it->c2 = shade_by_norm(p2n, it->p2, camera, lights);
        
        v3 p3n = it->point_norm(2);
        it->c3 = shade_by_norm(p3n, it->p3, camera, lights);
    }
}

v3 Mesh::shade_by_norm(v3 norm, v3 vertex,v3 *camera, std::vector<Light> *lights){

    v3 I;
    v3 Ia; //ambient
    v3 Id; //diffuse
    v3 Is; //specular
    v3 vert = vertex;
    
    //iterate over all the lights
    for (std::vector<Light>::iterator li = lights->begin(); li != lights->end(); ++li){

        v3 vector_to_light = li->point.minus(vert).Unit();
        v3 to_eye = vert.Scale(-1).Unit();
        v3 reflect = norm.Unit().Scale(2 * (norm.Unit().dot(vector_to_light))).minus(vector_to_light).Unit();
        
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
            
            /*
             * Specular Shading
             * Only do this if we also did diffues
             */
            
            v3 reflect_dir = vector_to_light.Scale(-1).reflect(norm);
            v3 half_angle = to_eye.add(vector_to_light).Unit();
            //double spec_angle = std::max(reflect_dir.dot( to_eye ) ,  0.0);
            double spec_angle = std::max(norm.dot(half_angle), 0.0);
            double specular = std::pow(spec_angle, phong.spower);
            
            
            double sr = phong.ks.x * specular * li_color.x;
            double sg = phong.ks.y * specular * li_color.y;
            double sb = phong.ks.z * specular * li_color.z;
             
            /*
             * Specular Lighting alternative form.
             *
            double sr = phong.ks.x * pow( (reflect.dot(to_eye)), phong.spower) * li_color.x;
            double sg = phong.ks.y * pow( (reflect.dot(to_eye)), phong.spower) * li_color.y;
            double sb = phong.ks.z * pow( (reflect.dot(to_eye)), phong.spower) * li_color.z;
             */
            Is = Is.add(v3(sr, sg, sb));
            
        } 
        else 
        {
            Id = Id.add(v3(0,0,0));
        } 
        I = I.add(Ia).add(Id).add(Is);
    }
    
    //set the flat color of the triangle.
    return I;
}

/* returns a string with all the triangles */
std::string Mesh::to_str(){
    std::stringstream ss;
    for(std::vector<Triangle>::iterator it = this->triangles.begin(); it != this->triangles.end(); ++it) {
        ss << it->to_str();
    }
    return ss.str();
}

v3 Mesh::interpolate(v3 p, Triangle t){
    v3 v0 = t.p2;
    v3 v1 = t.p1;
    double f10 = (v0.y - v1.y)*p.x + (v1.x - v0.x) * p.y + (v0.x * v1.y - v0.y * v1.x);
    
    v1 = t.p3;
    v3 v2 = t.p2;
    double f21 = (v1.y - v2.y)*p.x + (v2.x - v1.x) * p.y + (v1.x * v2.y - v1.y * v2.x);
    
    v0 = t.p3;
    v2 = t.p1;
    double f02 = (v2.y - v0.y)*p.x + (v0.x - v2.x) * p.y + (v2.x * v0.y - v2.y * v0.x);
    
    
    double cons = f10 + f21 + f02;
    
    double lambda0 = f21 / cons;
    double lambda1 = f02 / cons;
    double lambda2 = f10 / cons;
    
    //double one =  lambda0 + lambda1 + lambda2;
    
    return v3(lambda0, lambda1, lambda2);
}
/* Iterate over the triangles in the mesh and transform them */
void Mesh::transform(mat *t_mat){
    for(std::vector<Triangle>::iterator it = this->triangles.begin(); it != this->triangles.end(); ++it) {
        it->transform(*t_mat);
    }
}