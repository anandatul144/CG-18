

#include "infiniteplane.h"

namespace rt
{

    InfinitePlane::InfinitePlane(const Point& origin, const Vector& normal,CoordMapper* texMapper, Material* material):Solid(texMapper, material)
    {
    	this -> origin = origin;
    	this -> normal = normal;

    }

    

    Intersection InfinitePlane::intersect(const Ray& ray, float previousBestDistance) const
    {

    	float denom = dot(ray.d, normal);
    	if (std::abs(denom) > 1e-6) {
    		float t = dot(origin - ray.o, normal) / denom;
    		if (t > 0 && t < previousBestDistance)
    		{
                        return Intersection(t,ray,this,normal,Relpoint(ray.getPoint(t),origin));

    		}
    	}
        return Intersection::failure();
    }

    float InfinitePlane::getArea() const
    {
    	return FLT_MAX;
    }


}


