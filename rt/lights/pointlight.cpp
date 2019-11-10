#include <rt/lights/pointlight.h>
#include <rt/ray.h>

/*
struct LightHit {
	Vector direction;  //the direction where the light is coming FROM at the given point
	float distance;    //the distance that has to be checked, along the direction, for occlusion
};
*/

namespace rt
{

	PointLight::PointLight(const Point& position, const RGBColor& intensity)
	{
		this->position = position;
		this->intensity = intensity;
	}
	LightHit PointLight::getLightHit(const Point& p) const	
	{
		LightHit LH;
                Vector light_dir = position - p;
		LH.distance = light_dir.length();
		LH.direction = light_dir.normalize();
		return LH;
	}
    RGBColor PointLight::getIntensity(const LightHit& irr) const
    {
    	float dissipation = 1 / (irr.distance * irr.distance);
        return dissipation*intensity;
    }
}
