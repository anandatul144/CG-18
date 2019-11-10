#include "bvh.h"
#include <rt/intersection.h>
#include <algorithm>
#include "bvhnode.h"

#include <stdio.h>



namespace rt {


    BVH::BVH() {
            //BVHNode * root = NULL;	//defined in private :
    }

    BVH::~BVH(){}

    BBox BVH::getBounds() const
    {
            return BBox();
    }



    void BVH::add(Primitive* p)
    {
       Material *m=new DummyMaterial();
       prims.push_back(p);
       this->setMaterial(m);
    }

    void BVH::setMaterial(Material* m)
    {
        for (auto i:prims)
        {
            i->setMaterial(m);
        }
    }

    void BVH::insertPrim(BVHNode* curr, Primitive *p)	//inster a primitive into a BVHNode
    {
            curr->extend(p->getBounds());//const BBox & boundingBox);
            curr->prims.push_back(p);
            curr->numChildren++ ;
    }

    void BVH::rebuildIndex()
    {

            ROOT->prims = prims;
            buildTree(ROOT);
            return;
    }




    void BVH::buildTree(BVHNode * root)	//Recurssive , pass BVHNode object with root->prims[] filled

        {
            float kLenBest;
            int start = 0;
            Primitive *p ;
            int end = root->prims.size() -1;


            int numElements = root->prims.size();

            if (numElements <= 0)
                    return;
            if (numElements < 3)
            {
                    root->isLeaf = true;
		    root->boundingBox =root->prims[0]->getBounds();
		    root->numChildren++;

                    for (int i = start+1; i <= end; i++)
                    {
                            root->numChildren++;
                            p = root->prims[i];
                            root->extend(p->getBounds());

                    }

                    return;
            }

            if (numElements >= 3)
            {

                root->isLeaf = false;
                root->leftChild = new BVHNode();
                root->leftChild->parent = root;
                root->rightChild = new BVHNode();
                root->rightChild->parent = root;
                root->boundingBox =root->prims[0]->getBounds();
                root->numChildren++;

                for (int i = start+1; i <= end; i++)
                {
                        p = root->prims[i];
                        root->numChildren++;
                        root->extend(p->getBounds());
                }
                int dim_index = splitBox(root->boundingBox);

                switch (dim_index)
                {
                    case 0: kLenBest=root->boundingBox.centroidOfBBox().x;break;
                    case 1: kLenBest=root->boundingBox.centroidOfBBox().y;break;
                    case 2: kLenBest=root->boundingBox.centroidOfBBox().z;break;
                }


                if(this->isSAH)     //SAH
                {
                    float costL=0,costR=0,costBest=FLT_MAX,cost,kLen;
                    switch (dim_index)
                    {
                        case 0:
                            for(int k=1;k<10;k++)
                            {
                                kLen=root->boundingBox.min.x+k*(root->boundingBox.max.x- root->boundingBox.min.x)/10;
                                for(auto j:root->prims)
                                {
                                    if(j->getBounds().centroidOfBBox().x<kLen)    //assuming x is the longest dimension
                                        costL=costL+j->getArea();
                                    else
                                        costR=costR+j->getArea();
                                    cost=costL*(kLen-root->boundingBox.min.x)+costR*(root->boundingBox.max.x-kLen);
                                 }
                                if(cost<costBest)
                                {
                                    costBest=cost;
                                    kLenBest=kLen;
                                }
                            } break;

                    case 1:
                        for(int k=1;k<10;k++)
                        {
                            kLen=root->boundingBox.min.y+k*(root->boundingBox.max.y- root->boundingBox.min.y)/10;
                            for(auto j:root->prims)
                            {
                                if(j->getBounds().centroidOfBBox().y<kLen)    //assuming x is the longest dimension
                                    costL=costL+j->getArea();
                                else
                                    costR=costR+j->getArea();
                                cost=costL*(kLen-root->boundingBox.min.y)+costR*(root->boundingBox.max.y-kLen);
                             }
                            if(cost<costBest)
                            {
                                costBest=cost;
                                kLenBest=kLen;
                            }
                        } break;

                    case 2:
                        for(int k=1;k<10;k++)
                        {
                            kLen=root->boundingBox.min.z+k*(root->boundingBox.max.z- root->boundingBox.min.z)/10;
                            for(auto j:root->prims)
                            {
                                if(j->getBounds().centroidOfBBox().z<kLen)    //assuming x is the longest dimension
                                    costL=costL+j->getArea();
                                else
                                    costR=costR+j->getArea();
                                cost=costL*(kLen-root->boundingBox.min.z)+costR*(root->boundingBox.max.z-kLen);
                             }
                            if(cost<costBest)
                            {
                                costBest=cost;
                                kLenBest=kLen;
                            }
                        } break;

                    }
                }



                    switch (dim_index)
                    {
                        case 0:			//x
                            for (int i = start; i <= end; i++)
                            {
                                p = root->prims[i];
                                if (p->getBounds().centroidOfBBox().x < kLenBest)
                                {
                                    root->leftChild->prims.push_back(p);

					//Flag objects that can cause infinite recurssion, move outliars to the front of the list
                                    if(std::abs(p->getBounds().max.x - p->getBounds().min.x) == std::abs(root->boundingBox.max.x - root->boundingBox.min.x)  )
                                        std::swap(root->leftChild->prims.front(), root->leftChild->prims.back());

                                }

                                else
                                {
                                    root->rightChild->prims.push_back(p);
                                    if(std::abs(p->getBounds().max.x - p->getBounds().min.x) == std::abs(root->boundingBox.max.x - root->boundingBox.min.x)  )
                                        std::swap(root->rightChild->prims.front(), root->rightChild->prims.back());
                                }
                            }
                                    break;
                        case 1:			//y
                            for (int i = start; i <= end; i++)
                            {
                                p = root->prims[i];
                                if (p->getBounds().centroidOfBBox().y < kLenBest)
                                {
                                    root->leftChild->prims.push_back(p);
                                    if(std::abs(p->getBounds().max.y - p->getBounds().min.y) == std::abs(root->boundingBox.max.y - root->boundingBox.min.y)  )
                                        std::swap(root->leftChild->prims.front(), root->leftChild->prims.back());

                                }

                                else
                                {
                                    root->rightChild->prims.push_back(p);
                                    if(std::abs(p->getBounds().max.y - p->getBounds().min.y) == std::abs(root->boundingBox.max.y - root->boundingBox.min.y)  )
                                        std::swap(root->rightChild->prims.front(), root->rightChild->prims.back());
                                }
                            }
                                    break;
                        case 2:			//z
                            for (int i = start; i <= end; i++)
                            {
                                p = root->prims[i];
                                if (p->getBounds().centroidOfBBox().z < kLenBest)
                                {
                                    root->leftChild->prims.push_back(p);
                                    if(std::abs(p->getBounds().max.z - p->getBounds().min.z) == std::abs(root->boundingBox.max.z - root->boundingBox.min.z)  )
                                        std::swap(root->leftChild->prims.front(), root->leftChild->prims.back());

                                }

                                else
                                {
                                    root->rightChild->prims.push_back(p);
                                    if(std::abs(p->getBounds().max.z - p->getBounds().min.z) == std::abs(root->boundingBox.max.z - root->boundingBox.min.z)  )
                                        std::swap(root->rightChild->prims.front(), root->rightChild->prims.back());
                                }
                            }
                                    break;
                    }


			//handling infinite recurssion..remove outliar from front of the queue and add into the neighboring empty subtree
			//outliars that cause infinite recurssion will be handled (terminated) automatically in the next recurssion.
                        if (root->leftChild->prims.size() == 0)
                        {

                                root->leftChild->prims.push_back(root->rightChild->prims[0]);
                                root->rightChild->prims.erase(root->rightChild->prims.begin());
                        }

                        else if(root->rightChild->prims.size() == 0)
                        {

                                root->rightChild->prims.push_back(root->leftChild->prims[0]);
                                root->leftChild->prims.erase(root->leftChild->prims.begin());
                        }

            buildTree(root->leftChild);

            buildTree(root->rightChild);

                        return;


                }




        }


    Intersection BVH::intersect(const Ray& ray, float previousBestDistance) const
    {

        BVHNode* node=new BVHNode();
       Intersection a,b;
        BBox Bbox=BBox();
        Primitives primlist;
        float previousdist=previousBestDistance;
        std::vector<BVHNode*> nodes;
        nodes.push_back(this->ROOT);

        //node=nodes.back();
        while(!nodes.empty())
        {


            node=nodes.back();
            nodes.pop_back();


            if(node->isLeaf)
            {
                 primlist=node->prims;



                for (auto i :primlist)
                {
                    a=i->intersect(ray,previousdist);
                    if(a)
                    {
                            if(a.distance<previousdist)
                            {
                                previousdist=a.distance;
                                b=a;

                            }

                    }
                }
            }

                else
            {
                Bbox=node->leftChild->boundingBox;
                auto dist=Bbox.intersect(ray);
                if(std::get<0>(dist)<std::get<1>(dist))
                    nodes.push_back(node->leftChild);


               Bbox=node->rightChild->boundingBox;
                dist=Bbox.intersect(ray);
                if(std::get<0>(dist)<std::get<1>(dist))
                    nodes.push_back(node->rightChild);



            }

        }

        if (previousdist<previousBestDistance)
            return b;
        else
            return Intersection::failure();
    }
}



