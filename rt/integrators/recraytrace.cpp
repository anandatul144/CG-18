#include "recraytrace.h"
#include <rt/world.h>
#include <rt/solids/solid.h>
#include "rt/lights/light.h"
#include "rt/intersection.h"
#include "core/color.h"
#include "rt/integrators/castingdist.h"
#include "rt/materials/material.h"

namespace rt {


    RGBColor RecursiveRayTracingIntegrator::getRadiance(const rt::Ray &ray) const {
        return RecursiveTrace(RGBColor(0,0,0), ray, 6);
    }


    RGBColor RecursiveRayTracingIntegrator::RecursiveTrace(RGBColor accumulator, const rt::Ray &ray, int depth) const {

        depth--;
        if (depth == 0 ) return RGBColor(0,0,0);
        float k = epsilon * 20;
        std::vector<Light*> lights = world->light;
        RGBColor result = RGBColor(0,0,0);
        Primitive* p = this->world->scene;
        Intersection intersection = p->intersect(ray);

        if (intersection) {
            Material *material = intersection.solid->material;
            Material::Sampling sampling = material->useSampling();
            CoordMapper* cm = intersection.solid->texMapper;
            Point p1 = cm->getCoords(intersection);

            if (sampling == Material::SAMPLING_NOT_NEEDED || sampling == Material::SAMPLING_SECONDARY) {
                //Iterate over all light sources in the World .
                for(int i = 0; i < lights.size(); i++) {
                    LightHit lHit = lights[i]->getLightHit(intersection.hitPoint());

                    Vector offset = lHit.direction * k;
                    Ray shadowRay = Ray(intersection.hitPoint() + offset, lHit.direction);
                    if (dot(shadowRay.d,intersection.normal()) * dot(-ray.d,intersection.normal()) < 0 ) {
                        continue;
                    }
                    Intersection intersection2 = p->intersect(shadowRay, lHit.distance - k );
                    // No intersection
                    if (intersection2)
                        continue;
                    RGBColor intensity = lights[i]->getIntensity(lHit);
                    RGBColor color = intersection.solid->material->getReflectance(p1, intersection.normal(), -ray.d, lHit.direction);
                    result = result + intensity * color;
                }
                result = result + intersection.solid->material->getEmission( p1, intersection.normal(), -ray.d);
            }


            if (sampling == Material::SAMPLING_ALL || sampling == Material::SAMPLING_SECONDARY) {

                Material::SampleReflectance sr = intersection.solid->material->getSampleReflectance(intersection.hitPoint(), intersection.normal(), -intersection.ray.d);
                return  result + sr.reflectance * RecursiveTrace(accumulator, Ray(intersection.hitPoint() + sr.direction * k, sr.direction), depth);
            }
        }
        return result;
    }
}