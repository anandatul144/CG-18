#include "aabox.h"
#include <core/assert.h>
#include <cmath>
#include <algorithm>
#include <core/point.h>

namespace rt{



        AABox::AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material):Solid(texMapper, material)
	{
		this -> corner1 = corner1;
		this -> corner2 = corner2;
                Point origin=Point(0,0,0);
                if((corner1-origin).length()<=(corner2-origin).length())
                {
                    this -> min_P = corner1;		//corner closer to O
                    this -> max_P = corner2;
                }
                    else
                {
                    this -> max_P = corner1;
                    this -> min_P = corner2;
                }

                this -> centroid = (min_P+max_P)/2;
	}

	float AABox::getArea() const {
		float len = max_P.x - min_P.x;
		float wid = max_P.y - min_P.y;
		float hgt = max_P.z - min_P.z;

		return(2 * (len*wid + wid*hgt + hgt*len));
	}

	BBox AABox::getBounds() const {
                return(BBox(min_P,max_P));
	}


        Intersection AABox::intersect(const Ray& ray, float previousBestDistance) const
        {

            Vector normal =Vector (-1,0,0);
            float tmin = (min_P.x - ray.o.x) / ray.d.x;
            float tmax = (max_P.x - ray.o.x) / ray.d.x;

            if (tmin > tmax) std::swap(tmin, tmax);

            float tymin = (min_P.y - ray.o.y) / ray.d.y;
            float tymax = (max_P.y - ray.o.y) / ray.d.y;

            if (tymin > tymax) std::swap(tymin, tymax);

            if ((tmin > tymax) || (tymin > tmax))
            return Intersection::failure();

            if (tymin > tmin)
            {tmin = tymin;
            normal=Vector(0,-1,0);
            }

            if (tymax < tmax)
            tmax = tymax;

            float tzmin = (min_P.z - ray.o.z) / ray.d.z;
            float tzmax = (max_P.z - ray.o.z) / ray.d.z;

            if (tzmin > tzmax) std::swap(tzmin, tzmax);

            if ((tmin > tzmax) || (tzmin > tmax))
            return Intersection::failure();

            if (tzmin > tmin)
            {
                tmin = tzmin;
                normal=Vector(0,0,1);
            }

            if (tzmax < tmax)
            tmax = tzmax;

            if(tmin>previousBestDistance)
                return Intersection::failure();

            return Intersection(tmin, ray,this, normal, Relpoint(ray.getPoint(tmin),centroid));




	}

	Solid::Sample AABox::sample() const
	{
			NOT_IMPLEMENTED;
	}
}
