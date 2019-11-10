#include "volumeintegrator.h"
#include <cmath>
#include <iostream>

namespace rt{


RGBColor VolumeIntegrator::getRadiance(const Ray& ray)const
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

            RGBColor emm_bef_attn=solid->material->getEmission(texPoint, normal, ray.d.normalize());
            //RGBColor emm=this->get_transmittance(ray, intersection.distance,emm_bef_attn); //volume attenuation
            color = color + emm_bef_attn;
            color= color + this->get_emission(ray, intersection.distance); //volume emmission

            Vector reflVec= (ray.d.normalize()- 2*dot(normal.normalize(),ray.d.normalize())*normal.normalize()).normalize();
            Ray reflRay= Ray(intersection.hitPoint(),reflVec);
            color = color + this->get_emission(reflRay, 1000.0f);


            //itrating over all light sources, could be any of the lightsource type
            /*for (auto Source : this -> world -> light)
            {

                    LightHit LH = Source->getLightHit(intersection.hitPoint());

                    if (dot(LH.direction, normal) < 0)
                            continue;				//break loop if the vectors are obtuse

                    Ray shadowRay = Ray(intersection.hitPoint() + LH.direction*0.0001, LH.direction);  //Adding offset to shadow ray
                    //Ray SpecularRay = Ray(intersection.hitPoint() + )



                    Intersection SR_intersection = this->world->scene->intersect(shadowRay, LH.distance);
                    if(SR_intersection)                        
                        continue;                    

                    RGBColor refl_bef_attn=solid->material->getReflectance(texPoint, normal, ray.d.normalize(), LH.direction);
                    //RGBColor refl=this->get_transmittance(shadowRay,LH.distance,refl_bef_attn);
                    //RGBColor refl_at_cam=this->get_transmittance(ray, intersection.distance,refl);

                    color = color + refl_bef_attn * Source->getIntensity(LH);


            }*/


    }
    else
    {
      color=this->get_emission(ray, 1000.0f); //volume emmission , max distance only considered till 10 units change here

    }


    return color;
}


RGBColor VolumeIntegrator::get_emission(const Ray& ray, const float tmax)const
{
    RGBColor sig_t;
    RGBColor tr= RGBColor::rep(0.0f);
    Point pt_temp=ray.o;
    for (float j=0;j<=tmax;j+=stepSize)
    {
        pt_temp=ray.o + j*ray.d;
        for (auto Solids : this -> world -> solidVols)
        {

            if(Solids->inside_check(pt_temp))
            {
                sig_t=Solids->sigma_em(pt_temp, ray.d);
                tr=tr+sig_t*stepSize;


            }

        }
    }

    return tr;

}



RGBColor VolumeIntegrator::get_transmittance(const Ray& ray, const float tmax, const RGBColor &col)const
{

    RGBColor sig_t;
    RGBColor tr=RGBColor::rep(1.0f);
    Point pt_temp=ray.o;
    for (float j=0;j<=tmax;j+=stepSize)
    {
        pt_temp=ray.o + j*ray.d;
        for (auto Solids : this -> world -> solidVols)
        {
            if(Solids->inside_check(pt_temp))
            {
                sig_t=Solids->sigma_at(pt_temp, ray.d,col)+Solids->sigma_os(pt_temp, ray.d,col);
                tr=tr*RGBColor(exp(-sig_t.r*stepSize),exp(-sig_t.g*stepSize),exp(-sig_t.b*stepSize));

            }

        }
    }
    return tr*col;


}

}

