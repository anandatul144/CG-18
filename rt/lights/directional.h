#ifndef CG1RAYTRACER_LIGHTS_DIRECTIONAL_HEADER
#define CG1RAYTRACER_LIGHTS_DIRECTIONAL_HEADER

#include <rt/lights/light.h>
#include <core/color.h>
#include<core/vector.h>

namespace rt {

class DirectionalLight : public Light {
public:
        Vector direction;
        RGBColor color;
	DirectionalLight() {}
        DirectionalLight(const Vector& direction, const RGBColor& color):direction(direction),color(color){}
	virtual LightHit getLightHit(const Point& p) const;
    virtual RGBColor getIntensity(const LightHit& irr) const;
};

}

#endif

