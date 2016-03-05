#include "Light.h"
Light::Light(v3 point, v3 color) : point(point), color(color) {}

void Light::transform(mat44 trans){
    point = point.transform_4(trans);
}
