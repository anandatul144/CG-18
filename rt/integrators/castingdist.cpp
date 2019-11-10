#include "castingdist.h"

namespace rt {


RGBColor RayCastingDistIntegrator::getRadiance(const Ray& ray) const
{
    float cosval,factor;
    float r=0,b=0,g=0;
    Intersection a=this->world->scene->intersect(ray,FLT_MAX);
    if(a)
    {
        Vector norm=a.normal().normalize();
        cosval=-(dot(ray.d,norm));
        //Clamping of values between near and far colors
        factor=(a.distance-nearDist)/(farDist-nearDist);
        r=cosval*(nearColor.r + factor*(farColor.r-nearColor.r));
        g=cosval*(nearColor.g + factor*(farColor.g-nearColor.g));
        b=cosval*(nearColor.b + factor*(farColor.b-nearColor.b));


    }
    return RGBColor(r,g,b);

}



}
