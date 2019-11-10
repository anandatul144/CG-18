#include <rt/integrators/recraytrace.h>
#include <rt/coordmappers/world.h>
#include <core/color.h>
#include <core/vector.h>
#include <rt/lights/light.h>
#include <rt/intersection.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>
#include <rt/materials/combine.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/integrators/integrator.h>
#include <core/vector.h>
#include <core/color.h>

#include <rt/world.h>

namespace rt
{
	RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray& ray ) const
	{
		return getRadiance(ray, 0);
	}

	RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray & ray, int depth) const
        {
                RGBColor color = RGBColor(0, 0, 0);
                if (depth >= 6)
                        return color;

                Intersection intersection = this->world->scene->intersect(ray, FLT_MAX);

                if (intersection)
                {
                        Vector normal = intersection.normal().normalize();

                        auto texMap = intersection.solid->texMapper;
                        if (texMap == nullptr)
                                texMap = new WorldMapper();

                        Point texturePoint = texMap->getCoords(intersection);

                        auto currentMaterial = intersection.solid->material;
                        auto outDirFlipped = ray.d.normalize();
                        // This vector should ideally be directed towards the other way but 
                        // due to risk of regression it might stay flipped forever :)

                        if (currentMaterial->useSampling() == Material::Sampling::SAMPLING_NOT_NEEDED)
                        {
                                for (auto lightSource : this->world->light)
                                {
                                        LightHit lightHit = lightSource->getLightHit(intersection.hitPoint());
                                        Vector inDir = lightHit.direction;
                                        if (dot(inDir, normal) < 0)
                                                continue;

                                        Ray shadowRay = Ray(intersection.hitPoint() + 0.01f * inDir, inDir);
                                        Intersection shadowRayIntersection = this->world->scene->intersect(shadowRay, lightHit.distance - 1.1 * 0.01f);
                                        if (shadowRayIntersection)
                                                continue;

                                        RGBColor reflected = currentMaterial->getReflectance(texturePoint, normal, outDirFlipped, inDir);
                                        RGBColor lightIntensity = lightSource->getIntensity(lightHit);
                                        color = color + reflected * lightIntensity;
                                }
                        }

                        else if (currentMaterial->useSampling() == Material::Sampling::SAMPLING_ALL)
                        {
                                auto reflectance = currentMaterial->getSampleReflectance(texturePoint, normal, outDirFlipped);
                                Vector inDir = reflectance.direction.normalize();

                                        Ray shadowRay = Ray(intersection.hitPoint() + 0.01f * normal, inDir);
                                        
                                        RGBColor incomingLightColor = this->getRadiance(shadowRay, depth + 1);
                                        color = incomingLightColor * reflectance.reflectance;
                                
                        }

                        else if (currentMaterial->useSampling() == Material::Sampling::SAMPLING_SECONDARY)
                        {
                                for (auto lightSource : this->world->light)
                                {
                                        LightHit lightHit = lightSource->getLightHit(intersection.hitPoint());
                                        Vector inDir = lightHit.direction;
                                        if (dot(inDir, normal) < 0)
                                                continue;

                                        Ray shadowRay = Ray(intersection.hitPoint() + 0.01f * inDir, inDir);
                                        Intersection shadowRayIntersection = this->world->scene->intersect(shadowRay, lightHit.distance);
                                        if (shadowRayIntersection)
                                                continue;

                                        RGBColor reflected = currentMaterial->getReflectance(texturePoint, normal, outDirFlipped, inDir);
                                        color = color + reflected * lightSource->getIntensity(lightHit);
                                }

                                auto reflectance = currentMaterial->getSampleReflectance(texturePoint, normal, outDirFlipped);
                                Vector inDir = reflectance.direction.normalize();

                                Point rayOrigin = intersection.hitPoint();
                                Ray shadowRay = Ray(rayOrigin + 0.01f * inDir, inDir);

                                RGBColor incomingLightColor = this->getRadiance(shadowRay, depth + 1);
                                color = color + incomingLightColor * reflectance.reflectance;
                        }
                        color = color + intersection.solid->material->getEmission(texturePoint, normal, ray.d.normalize());
                }

                return color;
        }



}
