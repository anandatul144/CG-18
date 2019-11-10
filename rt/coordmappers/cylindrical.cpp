#include "cylindrical.h"
#include <iostream>
namespace rt {

Point CylindricalCoordMapper::getCoords(const Intersection& hit) const{


    Vector newPolar = (pA.normalize()- dot(lA.normalize(),pA.normalize())*lA).normalize();
    Vector hitP=hit.hitPoint()-origin;
    float y= dot(lA.normalize(),hitP);
    Vector polarHit=(hitP- dot(lA.normalize(),hitP)*lA.normalize()).normalize();
    float x=(dot(polarHit,newPolar)+1)/2;
//    printf("original point: %f %f %f \n",hit.hitPoint().x,hit.hitPoint().y,hit.hitPoint().z);
//    printf("new point: %f %f %f \n",x,y,1.0f);



    return Point (x,y,1);

}
}
