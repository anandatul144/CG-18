#ifndef CG1RAYTRACER_SOLIDS_SPHERE_HEADER
#define CG1RAYTRACER_SOLIDS_SPHERE_HEADER

#include <rt/solids/solid.h>
#include <core/point.h>
#include <rt/intersection.h>
#include <rt/ray.h>
#include <core/assert.h>
#include <iostream>
namespace rt {

class CoordMapper;
class Material;

class Sphere : public Solid {
public:
    Point center;
    float radius;
    Sphere() {}
    Sphere(const Point& center, float radius, CoordMapper* texMapper, Material* material):center(center),radius(radius),Solid(texMapper,material){}

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
        virtual Solid::Sample sample() const{NOT_IMPLEMENTED;}
    virtual float getArea() const;
};

}


#endif
