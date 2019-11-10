#include "bvhnode.h"

namespace rt {

BVHNode::BVHNode(const BVHNode &obj)
{
   this->numChildren=obj.numChildren;
   this->isLeaf=obj.isLeaf;
   this->boundingBox=obj.boundingBox;
   this->prims=obj.prims;
   this->parent=obj.parent;
   this->leftChild=obj.leftChild;
   this->rightChild=obj.rightChild;

}

}
