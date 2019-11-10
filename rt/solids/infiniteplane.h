#ifndef CG1RAYTRACER_SOLIDS_INFINITEPLANE_HEADER
#define CG1RAYTRACER_SOLIDS_INFINITEPLANE_HEADER

#include <rt/solids/solid.h>
#include <rt/intersection.h>
#include <core/assert.h>
#include <algorithm>
#include <core/point.h>
#include <core/vector.h>
#include <rt/intersection.h>
#include <rt/bbox.h>

namespace rt {

class InfinitePlane : public Solid {
public:
    InfinitePlane() {}
    InfinitePlane(const Point& origin, const Vector& normal, CoordMapper* texMapper, Material* material);

    virtual BBox getBounds() const{NOT_IMPLEMENTED;}
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
        virtual Solid::Sample sample() const{NOT_IMPLEMENTED;}
    virtual float getArea() const;

private:
	Vector normal;
	Point origin;

};

}


#endif
