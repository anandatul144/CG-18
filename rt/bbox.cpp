#include "bbox.h"
#include <rt/ray.h>

namespace rt
{

    std::pair<float,float> BBox::intersect(const Ray& ray) const
    {



            float tmin = (min.x - ray.o.x) / ray.d.x;
            float tmax = (max.x - ray.o.x) / ray.d.x;

            if (tmin > tmax) std::swap(tmin, tmax);

            float tymin = (min.y - ray.o.y) / ray.d.y;
            float tymax = (max.y - ray.o.y) / ray.d.y;

            if (tymin > tymax) std::swap(tymin, tymax);

            if ((tmin > tymax) || (tymin > tmax))
                return std::make_pair(0,-1);

            if (tymin > tmin)
                tmin = tymin;


            if (tymax < tmax)
                tmax = tymax;

            float tzmin = (min.z - ray.o.z) / ray.d.z;
            float tzmax = (max.z - ray.o.z) / ray.d.z;

            if (tzmin > tzmax) std::swap(tzmin, tzmax);

            if ((tmin > tzmax) || (tzmin > tmax))
                return std::make_pair(0,-1);

            if (tzmin > tmin)
                tmin = tzmin;


            if (tzmax < tmax)
                tmax = tzmax;

            return std::pair<float,float> (tmin,tmax) ;


    }


    void BBox::extend(const Point& point)
    {
        if (isEmpty)
        {
            min=point;
            max=point;
            isEmpty=false;
        }
        else
        {
           min=Point(std::min(min.x,point.x),std::min(min.y,point.y),std::min(min.z,point.z));
           max=Point(std::max(max.x,point.x),std::max(max.y,point.y),std::max(max.z,point.z));
        }
    }

    void BBox::extend(const BBox& bbox)
    {
        if (isEmpty)
        {
            min=bbox.min;
            max=bbox.max;
            isEmpty=false;
        }
        else
        {
            min=Point(std::min(min.x,bbox.min.x),std::min(min.y,bbox.min.y),std::min(min.z,bbox.min.z));
            max=Point(std::max(max.x,bbox.max.x),std::max(max.y,bbox.max.y),std::max(max.z,bbox.max.z));
        }
    }

    bool BBox::isUnbound()
    {
        BBox fullbox= BBox::full();
        if(min.x<=fullbox.min.x || min.y<=fullbox.min.y || min.z<=fullbox.min.z || max.x>=fullbox.max.x || max.y>=fullbox.max.y || max.z>=fullbox.max.z )
            return true;
        else
            return false;
    }

    int  splitBox(const BBox& Bbox)
    {
        float xlen=Bbox.max.x-Bbox.min.x;
        float ylen=Bbox.max.y-Bbox.min.y;
        float zlen=Bbox.max.z-Bbox.min.z;

        if(xlen>=ylen && xlen>=zlen )
            return 0;
        if(ylen>=xlen && ylen>=zlen )
            return 1;
        if(zlen>=ylen && zlen>=xlen )
            return 2;
        else
            return -1;
    }
    Point BBox::centroidOfBBox() const
    {
        return Point((max.x+min.x)/2,(max.y+min.y)/2,(max.z+min.z)/2);
    }

    BBox BBox::empty()
    {
        return BBox();
    }

    BBox BBox::full()
    {
        return BBox(Point(-FLT_MAX,-FLT_MAX,-FLT_MAX),Point(FLT_MAX,FLT_MAX,FLT_MAX));
    }

}

