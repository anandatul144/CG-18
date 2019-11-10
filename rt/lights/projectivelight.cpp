#include "projectivelight.h"
#include <core/julia.h>
#include <cmath>
#include <iostream>

using namespace rt;

float a1computeWeight(float fx, float fy, const Point& c, float div);
RGBColor a1computeColor(uint x, uint y, uint width, uint height);



namespace rt{

LightHit ProjectiveLight::getLightHit(const Point& p) const
{
        LightHit LH;
        Vector light_dir = position - p;
        LH.distance = light_dir.length();
        LH.direction = light_dir.normalize();
        return LH;
}


RGBColor ProjectiveLight::getIntensity(const LightHit& irr) const
{
    Vector dir=irr.direction;
    Vector a=Vector(1,0,0);
    Vector b=Vector(0,1,0);
    RGBColor color= a1computeColor(fabs(dot(dir.normalize(),a))*500,fabs(dot(dir.normalize()*500,b)), 500, 500);
    RGBColor julia_color=(RGBColor::rep(1.0f) - color);

    float dissipation = 1 / (irr.distance*irr.distance*10);
    return dissipation*julia_color;


}

}
