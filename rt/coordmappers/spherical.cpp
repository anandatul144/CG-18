#include "spherical.h"

namespace rt {

Point SphericalCoordMapper::getCoords(const Intersection& hit) const{

    Vector hitP=hit.hitPoint()-origin;
    Vector newPolar = (aR.normalize()- dot(aR.normalize(),z.normalize())*z).normalize();
    float y=(dot(hitP.normalize(),z.normalize())+1)/2;
    Vector hitP_Polar=(hitP- dot(hitP,z.normalize())*z).normalize();
    float x=(dot(hitP_Polar,newPolar)+1)/2;
    return Point (x,y,1);
}

}
