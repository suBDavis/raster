#include "Room.h"
#include <stdexcept>
#include <stdio.h>

//cam is the transform matrix for putting the camera into world space
Room::Room(mat44 cam, double left, double right, double bottom, double top, double n, double f, v3 bg): 
cam(cam), left(left), right(right), bottom(bottom), top(top), n(n), f(f), bg(bg){}

/*
 * Code for the renderer derived from...
 * Triangle Raster      : http://www.cs.cornell.edu/courses/cs4620/2010fa/lectures/07pipeline.pdf
 * Transformations      : http://www.cs.cornell.edu/courses/cs4620/2012fa/lectures/11viewing.pdf
 * General Overview     : http://www.codinglabs.net/article_world_view_projection_matrix.aspx
 * More Triangle Raster : http://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-837-computer-graphics-fall-2012/lecture-notes/MIT6_837F12_Lec21.pdf
 */ 

void Room::draw(Renderer *r){
    
    /*
     * PART 1 - transform room onto 2D viewscreen
     */ 
    this->rasterize(r);
    
    /*
     * Part 2 - draw the viewscreen to the renderer
     * 
     * Iterate over the objects, and raster bottom to top
     */
     
     //set the depth buffer
     std::vector<std::vector<double>> depth(r->getWidth(), std::vector<double>(r->getHeight()));
     for (int i = 0; i < depth.size(); ++i)
     {
         for (int j = 0; j < depth[i].size(); ++j)
         {
             depth[i][j] = std::abs(f);
         }
     }
     
     //Variables we'll set in the loop
     //Triangle t;
     //v3 p;
     //int minx;
     //int miny;
     //int maxx;
     //int maxy;
     
     for (unsigned int i = 0; i < objs.size(); i++){
        //for every object in the room
        std::vector<Triangle> triangles = objs[i]->get_triangles();
         
        for (unsigned int tr = 0; tr < triangles.size(); tr++){
            //for every triangle in the object
            Triangle t = triangles[tr];
            //Tell the triangles to project themselves into the view plane
            t.project();
             
            //draw the triangle to the renderer
            int minx = std::min({(int)t.p1.x, (int)t.p2.x, (int)t.p3.x});
            int maxx = std::max({(int)t.p1.x, (int)t.p2.x, (int)t.p3.x});
            int miny = std::min({(int)t.p1.y, (int)t.p2.y, (int)t.p3.y});
            int maxy = std::max({(int)t.p1.y, (int)t.p2.y, (int)t.p3.y});
            
            //For now we can assume the triangle is within the box.
            for (int j = miny; j <= maxy; j++){
                for (int i = minx; i <= maxx; i++){
                    //for every pixel on the screen
                    v3 p = v3(i, j, 0);
                    double e1 = compute_edge( t.p1, t.p2, p);
                    double e2 = compute_edge( t.p2, t.p3, p);
                    double e3 = compute_edge( t.p3, t.p1, p);
                    
                    if ( e1 >= 0 && e2 >= 0 && e3 >= 0 ){
                        if ( std::abs(t.p1.z) < depth[i][j] ){
                            depth[i][j] = std::abs(t.p1.z);
                            r->set_pixel(i, j, v3(255, 255, 255));
                        }
                    } else {
                        if ( std::abs(t.p1.z) < depth[i][j] ){
                            depth[i][j] = std::abs(t.p1.z);
                            r->set_pixel(i, j, v3(0,0,0));
                        }
                    }
                }
            }
        }
    }
}

double Room::compute_edge(v3 a, v3 b, v3 p){
    return (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
}

void Room::rasterize(Renderer *r){
    //Step 0 - Object Space to World Space transform - Already Done.
    
    if (objs.size() == 0 ){
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

void Room::addObject(RoomObject* obj){
    objs.push_back(obj);
}
void Room::addLight(Light l){
    lights.push_back(l);
}
void Room::transform(mat44 trans){
    //transforms everything in the room except for the camera.
    for(unsigned int i = 0; i < objs.size(); i++) {
        objs[i]->transform(&trans);
    }
    for(unsigned int i = 0; i < lights.size(); i++) {
        lights[i].transform(trans);
    }
}