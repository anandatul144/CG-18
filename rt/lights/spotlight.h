#ifndef CG1RAYTRACER_LIGHTS_SPOTLIGHT_HEADER
#define CG1RAYTRACER_LIGHTS_SPOTLIGHT_HEADER

#include <core/scalar.h>
#include <core/vector.h>
#include <core/color.h>
#include <core/point.h>
#include <rt/lights/light.h>

namespace rt {

class SpotLight : public Light {
public:
    Point position;
    Vector direction;
    float angle;
    float exp;
    RGBColor intensity;
	SpotLight() {}
        SpotLight(const Point& position, const Vector& direction, float angle, float exp, const RGBColor& intensity):position(position),direction(direction),angle(angle),exp(exp),intensity(intensity){}
    virtual LightHit getLightHit(const Point& p) const;
    virtual RGBColor getIntensity(const LightHit& irr) const;
};

}

#endif

