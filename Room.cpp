#include "Room.h"
#include <stdexcept>

//cam is the transform matrix for putting the camera into world space
Room::Room(mat44 cam, double left, double right, double bottom, double top, double near, double far, v3 bg): 
cam(cam), left(left), right(right), bottom(bottom), top(top), near(near), far(far), bg(bg){}

void Room::rasterize(Renderer r){
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
     * Part a) Calculate Field of View In X
     * Part b) Calculate Field of View in Y
     * Part c) Calculate the tranform matrix
     * 
    /*/
    
    mat44 perspective = {
    {(2 * near) / (right - left),  0 ,                        (left + right) / (left - right),  0                       },
    {0,                           (2*near) / (top - bottom),  (top + bottom) / (bottom - top),  0                       },
    {0,                            0,                         (far + near) / (near - far),     (2*far*near)/(far - near)},
    {0,                            0,                         1,                                0                       }};
    this->transform(perspective);
    
    /*
     * Step 3 - Viewport Transform.  
     * 
     * Get this information from the renderer.
     * 
     */ 
     int nx = r.getWidth();
     int ny = r.getHeight();
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
        objs[i]->transform(trans);
    }
    for(unsigned int i = 0; i < lights.size(); i++) {
        lights[i].transform(trans);
    }
}