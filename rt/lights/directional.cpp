#include "directional.h"
#include <rt/intersection.h>

namespace rt{

LightHit DirectionalLight::getLightHit(const Point& p) const
{
    LightHit t;
    t.direction=-this->direction;
    t.distance=FLT_MAX;
    return t;
}

RGBColor DirectionalLight::getIntensity(const LightHit& irr) const
{
    return this->color;
}

}
