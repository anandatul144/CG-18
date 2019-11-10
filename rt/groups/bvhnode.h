
#ifndef BVHNODE_H
#define BVHNODE_H

#include <rt/bbox.h>
#include <iostream>
#include <rt/primitive.h>
#include <core/assert.h>
namespace rt {

class  BVHNode
{
public:
    BVHNode(){}
    BVHNode(const BVHNode &obj);
    BVHNode(const BBox & boundingBox): boundingBox(boundingBox){}

    BBox boundingBox ;
    bool isLeaf = true;
    int numChildren = 0;				//think about this again, if node is leaf and children = 3, during insertion, split node into two BBox
    BVHNode * leftChild;
    BVHNode * rightChild;

    void extend(const BBox & newBox){boundingBox.extend(newBox);}					//append bbox to existing bbox or empty node
    void rebuildIndex(){NOT_IMPLEMENTED;}
    void add(Primitive* p){prims.push_back(p);}

    typedef std::vector<Primitive*> Primitives;
    Primitives prims;


    BVHNode * parent;

};

}

#endif
