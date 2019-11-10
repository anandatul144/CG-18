#include "group.h"
#include <rt/materials/material.h>

namespace rt {

void Group::add(Primitive *p)
{
 this->prims.push_back(p);

}

void Group::setMaterial(Material* m)
{
    for (auto i:prims)
    {
        i->setMaterial(m);
    }
}

}
