#include "world.h"
#include <iostream>
namespace rt{

Point WorldMapper::getCoords(const Intersection& hit) const
{
    Point p = hit.hitPoint();

 return Point(p.x*scale.x,p.y*scale.y,p.z*scale.z);
}

}
