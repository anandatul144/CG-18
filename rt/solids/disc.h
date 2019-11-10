#ifndef CG1RAYTRACER_SOLIDS_DISC_HEADER
#define CG1RAYTRACER_SOLIDS_DISC_HEADER



#include <rt/solids/solid.h>
#include <core/point.h>
#include <rt/ray.h>
#include <rt/intersection.h>
#include <core/assert.h>

namespace rt {

class Disc : public Solid {
public:
    Point center;
    Vector normal;
    float radius;
    Disc() {}
    Disc(const Point& center, const Vector& normal, float radius, CoordMapper* texMapper, Material* material):center(center),radius(radius),normal(normal),Solid(texMapper, material){}

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
    virtual Solid::Sample sample() const{NOT_IMPLEMENTED;}
    virtual float getArea() const;
};

}


#endif
