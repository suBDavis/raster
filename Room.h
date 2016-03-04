#ifndef ROOM_H
#define ROOM_H
#include "v3.h"
#include "RoomObject.h"
#include "Light.h"
#include "Ray.h"
#include <vector>
using std::vector;

class Room
{
public:
    Room(Ray cam, v3 top_l, v3 top_r, v3 bottom_l, v3 bg);
    ~Room(){}
    
    void addObject(RoomObject* obj);
    void addLight(Light l);

private:
    vector<RoomObject*> objs;
    vector<Light> lights;
    
    v3 bg;
    Ray cam;
    double step_x;
    double step_y;
    v3 bottom_l;
    v3 top_r;
    v3 top_l;
};

#endif // ROOM_H
