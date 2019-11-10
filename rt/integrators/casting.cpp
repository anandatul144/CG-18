#include "casting.h"
#include <stdio.h>

namespace rt{

RGBColor RayCastingIntegrator::getRadiance(const Ray& ray) const{


 float color=0;
 Intersection a=this->world->scene->intersect(ray,FLT_MAX);
 if(a)
 {
     Vector norm=a.normal().normalize();
     color=-(dot(ray.d,norm));



 }


 return RGBColor(color,color,color);


}


}
