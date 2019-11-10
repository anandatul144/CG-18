#ifndef CG1RAYTRACER_INTEGRATORS_CASTING_HEADER
#define CG1RAYTRACER_INTEGRATORS_CASTING_HEADER

#include <rt/integrators/integrator.h>
#include <core/vector.h>
#include <rt/intersection.h>
#include <core/color.h>
#include <rt/world.h>
#include <iostream>
#include <cmath>

namespace rt {

class World;
class Ray;
class RGBColor;

class RayCastingIntegrator : public Integrator {
public:
    RayCastingIntegrator(World* world) : Integrator(world) {}
    virtual RGBColor getRadiance(const Ray& ray) const;
};

}

#endif
