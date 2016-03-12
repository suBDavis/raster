#include <stdio.h>
#include <armadillo>
#include <vector>
#include "v3.h"
#include "RoomObject.h"
#include "Mesh.h"
#include "Triangle.h"
#include "Phong.h"
#include "Room.h"

using namespace arma;

/* Method Declarations */
int unit_tests();
int load_obj();

int main(int argc, char **argv)
{
    unit_tests();
    return 0;
}

int unit_tests(){
    Phong p = Phong( v3(0,.2, 0), v3(0, .5, 0), v3(1, 1, 1) , 1);
    mat t_mat = RoomObject::uniform_scale_transform(2);

    mat44 camera = mat44 {{1,0,0,0},
                          {0,1,0,0},
                          {0,0,1,0},
                          {0,0,0,1}};
    
    //Create a room maybe?
    Mesh m3 = Mesh( v3(0,0,0) , p, Mesh::generate_unit_sphere(32, 16));
    m3.transform(&t_mat);
    mat44 translation_mat = RoomObject::translate_transform( v3(0,0,-7) );
    m3.transform(&translation_mat);
    
    //Mesh m4 = Mesh( v3(0,0,0) , p, Mesh::generate_unit_sphere(32, 16));
    Mesh m4 = Mesh( v3(0,0,0) , p , Mesh::load_from_file("../objs/teapot.obj"));
    //m3.transform(&t_mat);
    mat44 tiny_scale =RoomObject::uniform_scale_transform(.06); 
    m4.transform(&tiny_scale);
    translation_mat = RoomObject::translate_transform( v3(0,0,-9) );
    m4.transform(&translation_mat);
    
    
    Room room = Room(camera, -.1, .1, -.1, .1, -.1, -1000, v3(0,0,0));
    
    //room.addObject(&m3);
    room.addObject(&m4);
    
    Renderer renderer = Renderer(512, 512, 1);
    
    room.draw(&renderer);
    
    renderer.render_ppm("../Images/out.ppm");
    
    return 0;
}