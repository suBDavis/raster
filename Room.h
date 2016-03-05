#ifndef ROOM_H
#define ROOM_H
#include "v3.h"
#include "RoomObject.h"
#include "Renderer.h"
#include "Light.h"
#include "Ray.h"
#include <vector>
#include <armadillo>
using std::vector;

class Room
{
public:
    Room(mat44 cam, double left, double right, double bottom, double top, double near, double far, v3 bg);
    ~Room(){}
    
    void addObject(RoomObject* obj);
    void addLight(Light l);
    void rasterize(Renderer r);

private:
    void transform(mat44 trans);

    vector<RoomObject*> objs;
    vector<Light> lights;
    
    v3 bg;
    double left;
    double right;
    double bottom;
    double top;
    double near;
    double far;
    mat44 cam;
    double step_x;
    double step_y;
};

#endif // ROOM_H
