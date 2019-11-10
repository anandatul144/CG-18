#ifndef CG1RAYTRACER_GROUPS_SIMPLEGROUP_HEADER
#define CG1RAYTRACER_GROUPS_SIMPLEGROUP_HEADER

#include <vector>
#include <rt/groups/group.h>
#include <rt/intersection.h>
#include <core/assert.h>
#include <rt/bbox.h>
#include <iostream>

namespace rt {

class SimpleGroup : public Group {
public:

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
    virtual void rebuildIndex(){};


    float getArea() const {}


     void add(Primitive* p);
     void setMaterial(Material* m);
    virtual void setCoordMapper(CoordMapper* cm){NOT_IMPLEMENTED;}

};
}

#endif


