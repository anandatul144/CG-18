#ifndef CG1RAYTRACER_SOLIDS_TRIANGLE_HEADER
#define CG1RAYTRACER_SOLIDS_TRIANGLE_HEADER

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

class Triangle : public Solid {
public:
    Triangle() {}
    Triangle(Point vertices[3], CoordMapper* texMapper, Material* material);
    Triangle(const Point& v1, const Point& v2, const Point& v3, CoordMapper* texMapper, Material* material);

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
    virtual Solid::Sample sample() const;
    virtual float getArea() const;
    Point bary(Point hitpoint) const;

	Point P1,P2,P3;
	Point centroid;
	Vector normal;
	float area;

};



}

#endif
