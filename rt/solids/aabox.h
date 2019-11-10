#ifndef CG1RAYTRACER_SOLIDS_BOX_HEADER
#define CG1RAYTRACER_SOLIDS_BOX_HEADER

#include <rt/solids/solid.h>
#include <rt/bbox.h>
#include <rt/intersection.h>

namespace rt {

class AABox : public Solid {
public:
    AABox() {}
    AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material);

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
    virtual Solid::Sample sample() const;
    virtual float getArea() const;

private:
	Point min_P,max_P;
	Point corner1,corner2;
	Point centroid;


};

}

#endif
