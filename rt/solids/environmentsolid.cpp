

#include "environmentsolid.h"

namespace rt
{
    Intersection EnvironmentSolid::intersect(const Ray& ray, float previousBestDistance) const
    {    
        float t=FLT_MAX;
        return Intersection(t,ray,this,ray.d,Point(0,0,0));
    }

    float EnvironmentSolid::getArea() const
    {
    	return FLT_MAX;
    }


}


