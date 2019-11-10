#ifndef CG1RAYTRACER_INTEGRATORS_RECURSIVERAYTRACING_HEADER
#define CG1RAYTRACER_INTEGRATORS_RECURSIVERAYTRACING_HEADER

#include <rt/integrators/integrator.h>
#include <rt/intersection.h>

namespace rt {

class World;
class Ray;
class RGBColor;

//class RecursiveRayTracingIntegrator : public Integrator {
//public:
//    RecursiveRayTracingIntegrator(World* world) : Integrator(world) {}
//    virtual RGBColor getRadiance(const Ray& ray) const;
//    virtual RGBColor getRadiance(const Ray&, int depth) const;
//    RGBColor getRadianceSimple(const Ray& ray, Intersection& inter) const;
//    RGBColor getRadianceSampled(const Ray& ray, Intersection& inter,int curr_depth) const;
//	//int depth=0;
//};

class RecursiveRayTracingIntegrator : public Integrator {
public:
    RecursiveRayTracingIntegrator(World* world) : Integrator(world) {}
    virtual RGBColor getRadiance(const Ray& ray) const;
    //virtual RGBColor getRadiance(const Ray&, int depth) const;
    virtual RGBColor RecursiveTrace(RGBColor accumulator, const Ray &ray, int depth) const;
    //float ModifiedhitPoint;
};


}
#endif
