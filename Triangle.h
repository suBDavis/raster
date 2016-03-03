#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "RoomObject.h" // Base class: RoomObject
#include <armadillo>
#include "v3.h"

class Triangle : public RoomObject
{
public:
    Triangle(){}
    Triangle( v3 triple[3] );
    ~Triangle(){}
    
    /* the virtual methods I must implement */
    virtual v3 get_ortho(v3 *point);
    virtual v3 get_point_above(v3 *point);
    virtual bool is_reflective();
    virtual void transform(mat transform);

private:
    v3 p1;
    v3 p2;
    v3 p3;
};

#endif // TRIANGLE_H
