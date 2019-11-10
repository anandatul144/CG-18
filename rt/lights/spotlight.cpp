#include "spotlight.h"
#include <cmath>

namespace rt{

LightHit SpotLight::getLightHit(const Point& p) const
{
    LightHit LH;
    Vector light_dir = position - p;
    LH.distance = light_dir.length();
    LH.direction = light_dir.normalize();
    return LH;

}
RGBColor SpotLight::getIntensity(const LightHit& irr) const
{
    float cosa=dot(irr.direction,-this->direction.normalize());

    if(cosa>cos(angle))
    {
        float v=pow(cosa,exp)/(irr.distance*irr.distance);
        return RGBColor(intensity.r*v,intensity.g*v,intensity.b*v);
    }
    else
    {
        return RGBColor(0,0,0);
    }


}

}
