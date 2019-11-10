#ifndef CG1RAYTRACER_INTEGRATORS_RAYTRACING_HEADER
#define CG1RAYTRACER_INTEGRATORS_RAYTRACING_HEADER

#include <rt/integrators/integrator.h>
#include <rt/intersection.h>
#include <core/color.h>
#include <core/vector.h>
#include <rt/world.h>
#include <rt/materials/material.h>
#include <rt/materials/dummy.h>

namespace rt {
class World;
class Ray;
class RGBColor;

class RayTracingIntegrator : public Integrator {
public:
    RayTracingIntegrator(World* world) : Integrator(world) {}
    virtual RGBColor getRadiance(const Ray& ray) const;
};

}

#endif
