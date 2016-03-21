#include <stdio.h>
#include <armadillo>
#include <vector>
#include "v3.h"
#include "RoomObject.h"
#include "Mesh.h"
#include "Triangle.h"
#include "Phong.h"
#include "Room.h"

/*
 * To switch back to the regular (seeemingly correct) renderer, 
 * make the depth vaues positive, 
 * modify renderer iteration order somehow
 * change camera to identity
 */

using namespace arma;

/* Method Declarations */
int unit_tests();
int pa2_none();
int pa2_flat();
int pa2_gouraud();

int main(int argc, char **argv)
{
    pa2_none();
    pa2_flat();
    pa2_gouraud();
    return 0;
}

int pa2_none(){
    
    //Create a Room
    mat44 camera = mat44 {{1,0,0,0},
                          {0,1,0,0},
                          {0,0,1,0},
                          {0,0,0,1}};
    
    Room room = Room(camera, -.1, .1, -.1, .1, -.1, -1000, v3(0,0,0));
    
    //Create a light
    Light l1 = Light(v3(-4,4,-3), v3(1,1,1));

    //Create a Sphere Mesh
    Phong p = Phong( v3(0,.2, 0), v3(0, .5, 0), v3(.5,.5,.5) , 32);
    Mesh m3 = Mesh( v3(0,0,0) , p, Mesh::generate_unit_sphere(32, 16));
    
    //Put the Sphere mesh in world Space
    mat scale_mat = RoomObject::uniform_scale_transform(2);
    mat44 translate_mat = RoomObject::translate_transform( v3(0,0,-7) );
    
    m3.transform(&scale_mat);
    m3.transform(&translate_mat);
    
    //Put the objects we created into the room
    room.addObject(&m3);
    room.addLight(l1);
    
    //Create a renderer
    Renderer renderer = Renderer(512, 512, 2.2);

    //Draw the room to a renderer without lighting
    room.draw(&renderer, 0);
    //output
    renderer.render_ppm("../Images/none.ppm");

    return 0;
}
int pa2_flat(){
    
    //Create a Room
    mat44 camera = mat44 {{1,0,0,0},
                          {0,1,0,0},
                          {0,0,1,0},
                          {0,0,0,1}};
    
    Room room = Room(camera, -.1, .1, -.1, .1, -.1, -1000, v3(0,0,0));
    
    //Create a light
    Light l1 = Light(v3(-4,4,-3), v3(1,1,1));

    //Create a Sphere Mesh
    Phong p = Phong( v3(0,.2, 0), v3(0, .5, 0), v3(.5,.5,.5) , 32);
    Mesh m3 = Mesh( v3(0,0,0) , p, Mesh::generate_unit_sphere(32, 16));
    
    //Put the Sphere mesh in world Space
    mat scale_mat = RoomObject::uniform_scale_transform(2);
    mat44 translate_mat = RoomObject::translate_transform( v3(0,0,-7) );
    
    m3.transform(&scale_mat);
    m3.transform(&translate_mat);
    
    //Put the objects we created into the room
    room.addObject(&m3);
    room.addLight(l1);
    
    //Create a renderer
    Renderer renderer = Renderer(512, 512, 2.2);

    //draw to renderer flat
    room.draw(&renderer, 1);
    //Output the image
    renderer.render_ppm("../Images/flat.ppm");

    return 0;
}

int pa2_gouraud(){
    
    //Create a Room
    mat44 camera = mat44 {{1,0,0,0},
                          {0,1,0,0},
                          {0,0,1,0},
                          {0,0,0,1}};
    
    Room room = Room(camera, -.1, .1, -.1, .1, -.1, -1000, v3(0,0,0));
    
    //Create a light
    Light l1 = Light(v3(-4,4,-3), v3(1,1,1));

    //Create a Sphere Mesh
    Phong p = Phong( v3(0,.2, 0), v3(0, .5, 0), v3(.5,.5,.5) , 32);
    Mesh m3 = Mesh( v3(0,0,0) , p, Mesh::generate_unit_sphere(32, 16));
    
    //Put the Sphere mesh in world Space
    mat scale_mat = RoomObject::uniform_scale_transform(2);
    mat44 translate_mat = RoomObject::translate_transform( v3(0,0,-7) );
    
    m3.transform(&scale_mat);
    m3.transform(&translate_mat);
    
    //Put the objects we created into the room
    room.addObject(&m3);
    room.addLight(l1);
    
    //Create a renderer
    Renderer renderer = Renderer(512, 512, 2.2);
    
    //Draw the room to the renderer g
    room.draw(&renderer, 2);
    //Output the image
    renderer.render_ppm("../Images/gouraud.ppm"); 

    return 0;
}