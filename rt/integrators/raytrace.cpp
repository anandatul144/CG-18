#include <rt/integrators/raytrace.h>
#include <rt/lights/light.h>
#include <rt/lights/pointlight.h>
#include <rt/solids/solid.h>


namespace rt {


    //RGBColor RayTracingIntegrator(World* world) : Integrator(world) {}
    RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const
    {
    	Intersection intersection = this->world->scene->intersect(ray, FLT_MAX);//MAX_DST);
    	RGBColor color = RGBColor(0,0,0);
    	if (intersection)
    	{
                Vector normal = intersection.normal();
                if (dot(normal, ray.d.normalize()) > 0)
                        normal = -normal;

                //solid can be of any subtype of Primitive
                auto solid = intersection.solid;
                Point texPoint = intersection.solid->texMapper->getCoords(intersection);
                color = color + solid->material->getEmission(texPoint, normal, ray.d.normalize());

                //itrating over all light sources, could be any of the lightsource type
                for (auto Source : this -> world -> light)
                {
                        LightHit LH = Source->getLightHit(intersection.hitPoint());

                        if (dot(LH.direction, normal) < 0)
                                continue;				//break loop if the vectors are obtuse

                        Ray shadowRay = Ray(intersection.hitPoint() + LH.direction*0.0001, LH.direction);  //Adding offset to shadow ray

                        Intersection SR_intersection = this->world->scene->intersect(shadowRay, LH.distance);
                        if(SR_intersection)
                                continue;

                        //collecting color intensity with each reflectance
                        //hitPoint probably should be local coordinates
                        RGBColor reflection = solid->material->getReflectance(texPoint, normal, ray.d.normalize(), LH.direction);

                        color = color + reflection * Source->getIntensity(LH);



                }
    	}
    	return color;
    }


}
