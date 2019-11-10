#ifndef CG1RAYTRACER_SOLIDS_QUAD_HEADER
#define CG1RAYTRACER_SOLIDS_QUAD_HEADER

#include <rt/solids/solid.h>
#include <core/point.h>
#include <core/assert.h>
#include <algorithm>
#include <core/point.h>
#include <core/vector.h>
#include <rt/intersection.h>
#include <rt/bbox.h>
#include <rt/solids/infiniteplane.h>


namespace rt {

class Quad : public Solid {
public:
    Quad() {}
    Quad(const Point& p1, const Vector& span1, const Vector& span2, CoordMapper* texMapper, Material* material);

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
	virtual Solid::Sample sample() const;
    virtual float getArea() const;
protected:
        Point P1;
        Vector span1, span2;
};

}

#endif
