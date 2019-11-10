#include "simplegroup.h"


namespace rt {

void SimpleGroup::add(Primitive *p)
{

    prims.push_back(p);

}


void SimpleGroup::setMaterial(Material* m)
{
    for (auto i:prims)
    {
        i->setMaterial(m);
    }
}

BBox SimpleGroup::getBounds() const
{
    BBox finalb=BBox(Point(0,0,0),Point(0,0,0));
    float dist=0;
    std::vector<BBox> testb;


    for (auto i : prims)
        testb.push_back(i->getBounds());


    for (auto i : testb)
        for (auto j : testb)
        {
            if((i.max-j.min).length()>dist)
            {
                dist=(i.max-j.min).length();
                finalb.max=i.max;
                finalb.min=j.min;
            }
        }
    return finalb;

}


Intersection SimpleGroup::intersect(const Ray& ray, float previousBestDistance) const
{
    float dist=previousBestDistance;
    Intersection temp,final;
    final=Intersection::failure();
    \
    for (auto i : prims)
      {
          temp=i->intersect(ray,dist);
          if(temp)
          {
              final=temp;
              dist=temp.distance;

          }


      }

      return final;

}


}
