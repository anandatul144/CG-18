#include"tmapper.h"

namespace rt{

float areaT(Vector a,Vector b)
{
    return (cross(a,b).length())/2;
}


Point TriangleMapper::getCoords(const Intersection& hit) const
{

 Point hitP=hit.local();
 Point tex=hitP.x*tv0 + hitP.y*tv1 +hitP.z*tv2;

 return tex;
}


}
