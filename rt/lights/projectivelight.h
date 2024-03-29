#ifndef CG1RAYTRACER_LIGHTS_PROJECTIVELIGHT_HEADER
#define CG1RAYTRACER_LIGHTS_PROJECTIVELIGHT_HEADER

#include <core/point.h>
#include <core/color.h>
#include <rt/lights/light.h>

namespace rt {

class ProjectiveLight : public Light {
public:
        ProjectiveLight() {}
        ProjectiveLight(const Point& position):position(position){}
        virtual LightHit getLightHit(const Point& p) const;
    virtual RGBColor getIntensity(const LightHit& irr) const;

    Point position;

};

}

#endif
