#include "bvh.h"
#include "bvhnode.h"
#include <rt/bbox.h>
#include <iostream>

namespace rt{


    Intersection BVH::intersect(const Ray& ray, float previousBestDistance) const
    {

        BVHNode* node;
        Intersection a,b;
        float previousdist=previousBestDistance;
        std::vector<BVHNode*> nodes;
        nodes.push_back(this->root);
        node=nodes.back();
        while(!nodes.empty())
        {
            node=nodes.back();
            nodes.pop_back();

            if(node->isLeaf)
            {

                for (auto i:node->prims)
                {
                    a=i->intersect(ray,previousdist);
                    if(a)
                    {
                            if(a.distance<previousdist)
                            {
                                previousdist=a.distance;
                                b=a;
                                std::cout<<"Ray intersects";
                            }

                    }
                }
            }

                else
            {

                BBox Bbox=node->leftChild->boundingBox;
                auto dist=Bbox.intersect(ray);
                if(std::get<0>(dist)<std::get<0>(dist))
                    nodes.push_back(node->leftChild);


                Bbox=node->rightChild->boundingBox;
                dist=Bbox.intersect(ray);
                if(std::get<0>(dist)<std::get<0>(dist))
                    nodes.push_back(node->rightChild);



            }

        }

        if (previousdist<previousBestDistance)
            return b;
        else
            return Intersection::failure();
    }
}
