#include "plane.h"
#include <iostream>


namespace rt{

Point PlaneCoordMapper::getCoords(const Intersection& hit) const{

    Vector hitP=hit.hitPoint() - Point(0,0,0);
    Vector planenorm=cross(e1,e2).normalize();
    Vector pt= hitP - (dot(hitP,planenorm)*planenorm);
    return Point(pt.x,pt.y,pt.z);

}
}
