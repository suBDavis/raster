#include "Room.h"
#include "Mesh.h"
#include <stdexcept>
#include <stdio.h>
#include <cstdlib>

//cam is the transform matrix for putting the camera into world space
Room::Room(mat44 cam, double left, double right, double bottom, double top, double n, double f, v3 bg): 
cam(cam), left(left), right(right), bottom(bottom), top(top), n(n), f(f), bg(bg){}

/*
 * Code for the renderer derived from...
 * Triangle Raster      | http://www.cs.cornell.edu/courses/cs4620/2010fa/lectures/07pipeline.pdf
 * Transformations      | http://www.cs.cornell.edu/courses/cs4620/2012fa/lectures/11viewing.pdf
 * General Overview     | http://www.codinglabs.net/article_world_view_projection_matrix.aspx
 * More Triangle Raster | http://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-837-computer-graphics-fall-2012/lecture-notes/MIT6_837F12_Lec21.pdf
 * More Triangle Raster | https://www.cs.unc.edu/xcms/courses/comp770-s07/Lecture08.pdf
 * Edge Function        | https://fgiesen.wordpress.com/2013/02/08/triangle-rasterization-in-practice/
 * Barycentric coords   | https://fgiesen.wordpress.com/2013/02/06/the-barycentric-conspirac/
 * 
 */ 

/* Takes a renderer and the shader mode (0 = none, 1 = flat, 2 = Gorard, 3 = Phong) */
void Room::draw(Renderer *r, int shader_mode){
    
    /*
     * PART 1 - transform room onto 2D viewscreen
     */ 
    this->rasterize(r, shader_mode);
    
    /*
     * Part 2 - draw the viewscreen to the renderer
     * 
     * Iterate over the objects, and raster bottom to top
     */
    
    //set the depth buffer
    const int numrows = r->getHeight();
    const int numcols = r->getWidth();
    double depth[numrows * numcols];
    
    for (unsigned int col = 0; col < numcols; col++)
        for (unsigned int row = 0; row < numrows; row++)
            depth[numcols * row + col] = std::abs(f);

    for (unsigned int i = 0; i < objs.size(); i++)
    {
        //for every object in the room
        std::vector<Triangle> triangles = objs[i]->get_triangles();
         
        for (unsigned int tr = 0; tr < triangles.size(); tr++)
        {
            //for every triangle in the object
            Triangle t = triangles[tr];
            
            t.project();
            
            v3 color1 = v3 (0, 0, 1);
            v3 color2 = v3 (1, 0, 0);
            v3 white = v3(1, 1, 1);
//            r->set_pixel((int)round(t.p1.x)-2, (int)round(t.p1.y)+2, color1);
//            r->set_pixel((int)round(t.p2.x)+1, (int)round(t.p2.y)+1, color2);
//            r->set_pixel((int)round(t.p3.x)-1, (int)round(t.p3.y)-1, v3(0, 1, 0));
             
            //draw the triangle to the renderer
            int minx = std::min({(int)t.p1.x, (int)t.p2.x, (int)t.p3.x});
            int maxx = std::max({(int)t.p1.x, (int)t.p2.x, (int)t.p3.x});
            int miny = std::min({(int)t.p1.y, (int)t.p2.y, (int)t.p3.y});
            int maxy = std::max({(int)t.p1.y, (int)t.p2.y, (int)t.p3.y});
            
            //For now we can assume the triangle is within the box.
            for (unsigned int jy = miny; jy <= maxy; jy++)
            {
                for (unsigned int ix = minx; ix <= maxx; ix++)
                {
                    //for every pixel in the bounding box
                    v3 p = v3(ix, jy, 0);
                    double e1 = compute_edge( t.p2, t.p1, p);
                    double e2 = compute_edge( t.p3, t.p2, p);
                    double e3 = compute_edge( t.p1, t.p3, p);
                    
                    int dex = jy * numcols + ix;
                    
                    if ( e1 >= 0 && e2 >= 0 && e3 >= 0 )
                    {
                        if ( std::abs(t.p1.z) <= depth[dex] )
                        {
                            depth[dex] = std::abs(t.p1.z);
                            
                            if (shader_mode == 0){
                                r->set_pixel(ix, jy, white);
                            } else if (shader_mode == 1){
                                r->set_pixel(ix, jy, t.flat_color);
                            } else if (shader_mode == 2){
                                v3 interp = Mesh::interpolate(p, t);
                                v3 a = t.c1.Scale(interp.x);
                                v3 b = t.c2.Scale(interp.y);
                                v3 c = t.c3.Scale(interp.z);
                                r->set_pixel(ix, jy, a.add(b).add(c));
                            } else if (shader_mode == 3){
                                //v3 Mesh::shade_by_norm(v3 norm, v3 vertex, v3 *camera, std::vector<Light> *lights){
                                v3 mesh_center = v3(0,0,-5);
                                v3 camera = v3 (cam[12], cam[13], cam[14]);
                                
                                v3 interp = Mesh::interpolate(p, t);
                                v3 a = t.point_norm(0).Scale(interp.x);
                                v3 b = t.point_norm(1).Scale(interp.y);
                                v3 c = t.point_norm(2).Scale(interp.z);
                                v3 norm = a.add(b).add(c); //should be unit
                                
                                v3 shade = objs[i]->shade_by_norm(norm, mesh_center, &camera, &lights);
                                r->set_pixel(ix, jy, shade);
                            }
                        }
                    } 
                    else 
                    {
                        //the triangle was not in the view frame
                    }
                }
            }
        }
    }
}

double Room::compute_edge(v3 b, v3 a, v3 p)
{
    return (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
}

/* shader mode (0 = none, 1 = flat, 2 = Gorard, 3 = Phong) */
void Room::rasterize(Renderer *r, int shader_mode)
{
    if (objs.size() == 0 )
    {
        //verify that we have objects to render.
        throw std::logic_error("No objects to render");
    }
    
    /*
     * Step 1 - Camera Space Transform
     * 
     * The camera is assumed to be looking in direction -w
     * 
    /*/
    
    mat44 camera_space_transform = inv(cam);
    this->transform(camera_space_transform);
    
    /*
     * Step 1.5 - shade the lil' triangles
     * Objects are already in world space.
     * 
     */ 
     
    v3 camera = v3 (cam[12], cam[13], cam[14]);
    for (int i = 0; i < this->objs.size(); i++){
        objs[i]->shade(shader_mode, &lights, &camera);
    }
    
    /*
     * Setp 2 - Perspective Projection Transform
     * 
    /*/
    
    mat44 perspective = {
    {(2 * n) / (right - left),     0,                         (left + right) / (left - right),  0                       },
    {0,                           (2*n) / (top - bottom),     (top + bottom) / (bottom - top),  0                       },
    {0,                            0,                         (f + n) / (n - f),               (2*f*n)/(f - n)          },
    {0,                            0,                         1,                                0                       }};
    this->transform(perspective);
    
    /*
     * Step 3 - Viewport Transform.  
     * 
     * Get this information from the renderer.
     * 
     */ 
    double nx = r->getWidth();  // usually 512
    double ny = r->getHeight(); // usually 512
    mat44 viewport = {
    {nx/2, 0,    0,  (nx-1)/2 },
    {0,    ny/2, 0,  (ny-1)/2 },
    {0,    0,    1,  0        },
    {0,    0,    0,  1        }
    };
    this->transform(viewport);

}

void Room::addObject(Mesh* obj)
{
    objs.push_back(obj);
}
void Room::addLight(Light l)
{
    lights.push_back(l);
}

/* 
 * Refactor this code to return a new copy instead of modifying the copy in memory
 * We will need to be able to ask the world model about its lighting
 */ 
void Room::transform(mat44 trans)
{
    //transforms every object in the room, and returns the transformed version.
    for(unsigned int i = 0; i < objs.size(); i++)
        objs[i]->transform(&trans);
        
//    for(unsigned int i = 0; i < lights.size(); i++)
//        lights[i].transform(trans);
}