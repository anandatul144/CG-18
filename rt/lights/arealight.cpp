#include <rt/lights/arealight.h>
#include <iostream>
#include <core/color.h>
#include <algorithm>

namespace rt {


AreaLight::AreaLight(Solid* source)
{
    this->source = source;
}

LightHit AreaLight::getLightHit(const Point& p) const 
{
	LightHit LH;
	Point position = source -> sample().point;
        Vector light_vec = (position - p);
        LH.distance = light_vec.length()- 0.0002f;
        LH.direction = light_vec.normalize();
	return LH;
}

RGBColor AreaLight::getIntensity(const LightHit & irr) const
{
	//Dummy Value 
	// Mul SF of light source
	// Div by dist * dist
	// dot (normals of source n surface)
	float dissipation = 1 / (irr.distance * irr.distance);
	float SourceArea = source->getArea();
        float N_Dot = std::fabs(dot(source->sample().normal, irr.direction));
	RGBColor Emission = source->material->getEmission(Point::rep(0.f),Vector::rep(0.f),Vector::rep(0.f));
        Emission=(dissipation*SourceArea*Emission*N_Dot);


    return Emission;
}

}
