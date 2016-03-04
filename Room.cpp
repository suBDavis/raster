#include "Room.h"

Room::Room(Ray cam, v3 top_l, v3 top_r, v3 bottom_l, v3 bg): cam(cam), top_l(top_l), top_r(top_r), bottom_l(bottom_l){}

void Room::addObject(RoomObject* obj){
    objs.push_back(obj);
}
void Room::addLight(Light l){
    lights.push_back(l);
}