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
    
    void addObject(RoomObject *obj);
    void addLight(Light l);
    void draw(Renderer* r);

private:
    void transform(mat44 trans);
    void rasterize(Renderer* r);
    double compute_edge(v3 a, v3 b, v3 p);
    vector<RoomObject*> objs;
    vector<Light> lights;
    
    v3 bg;
    double left;
    double right;
    double bottom;
    double top;
    double n;
    double f;
    mat44 cam;
    double step_x;
    double step_y;
};

#endif // ROOM_H
