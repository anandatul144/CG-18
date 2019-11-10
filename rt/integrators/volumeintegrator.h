#ifndef VOLUMEINTEGRATOR_H
#define VOLUMEINTEGRATOR_H

#include <rt/integrators/integrator.h>
#include <rt/intersection.h>
#include <core/color.h>
#include <core/vector.h>
#include <rt/world.h>
#include <rt/lights/light.h>
#include <rt/solids/solid.h>


namespace rt {


class VolumeIntegrator: public Integrator{
public:
    VolumeIntegrator(World* world, float stepSize) : Integrator(world),stepSize(stepSize) {}

    RGBColor get_transmittance(const Ray& ray, const float tmax,const RGBColor &col)const;
    RGBColor get_emission(const Ray& ray, const float tmax)const;

    RGBColor getSurfaceRadiance(const Ray& ray) const;
    virtual RGBColor getRadiance(const Ray& ray) const;

    float stepSize;


};

}

#endif // VOLUMEINTEGRATOR_H
