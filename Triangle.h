#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "RoomObject.h" // Base class: RoomObject
#include <armadillo>
#include <stdio.h>
#include <string>
#include <sstream>

#include "v3.h"

class Triangle : public RoomObject
{
public:
    /* there is currentlly no reason to have a default constructor */
    //Triangle(){}
    /* Constructor for triangles that are part of a mesh */
    Triangle( v3 triple[3] );
    /* this is only for free floating triangles.  
     * Mesh triangles should not have individual phong properties */
    Triangle( v3 triple[3] , Phong p );
    ~Triangle(){}
    
    /* the virtual methods I must implement */
    virtual Phong get_phong();
    virtual v3 get_ortho(v3 *point);
    virtual v3 get_point_above(v3 *point);
    virtual bool is_reflective();
    virtual void transform(mat transform);
    virtual std::string to_str();

private:
    v3 p1;
    v3 p2;
    v3 p3;
    Phong phong;
};

#endif // TRIANGLE_H
