#ifndef CG1RAYTRACER_GROUPS_GROUP_HEADER
#define CG1RAYTRACER_GROUPS_GROUP_HEADER

#include <vector>
#include <rt/primitive.h>
#include <core/assert.h>
#include <rt/materials/dummy.h>


namespace rt {

/*
A group is a container of multiple primitives.
*/
class Group : public Primitive {
public:
    typedef std::vector<Primitive*> Primitives;
    Primitives prims;
    virtual void rebuildIndex() = 0;

    virtual void add(Primitive* p) = 0;
    virtual void setMaterial(Material* m);


    float getArea() const {}

   
};

}

#endif    
