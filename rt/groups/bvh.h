#ifndef CG1RAYTRACER_GROUPS_BVH_HEADER
#define CG1RAYTRACER_GROUPS_BVH_HEADER

#include <core/vector.h>


#include <core/point.h>


#include <rt/groups/group.h>
#include <rt/bbox.h>
#include <core/assert.h>
#include "bvhnode.h"

#define maxElements = 3;

namespace rt {



class BVH : public Group {
public:
    BVH();
    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
    virtual void rebuildIndex();
	virtual ~BVH();
    void add(Primitive* p);
    void setMaterial(Material* m);
    virtual void setCoordMapper(CoordMapper* cm){NOT_IMPLEMENTED;}
    BVHNode *ROOT = new BVHNode();
    void buildTree(BVHNode * root);
    void insertPrim(BVHNode* curr, Primitive *p);



    bool isSAH=false;


private:
	//Primitives PrimList; 	//List of obhjects pushed into the tree
        //BHVNode * root;

};





}

#endif
