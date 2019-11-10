/*#include <rt/materials/glass.h>
#include <core/random.h>
#include <math.h>
#include <core/scalar.h>

namespace rt {


GlassMaterial::GlassMaterial(float eta)
{
	this -> eta = eta;
}

RGBColor GlassMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    
    Vector currentNormal;
    float currentEta;
    float cosI = dot(normal, inDir);

    bool comingFromAir = cosI < 0;

    if(comingFromAir)
        currentEta = this->eta;
    else
        currentEta = 1/this->eta;

    float sinI = sqrt(1.f - powf(cosI,2));
    float sinR = currentEta * sinI;
    float cosR = sqrt(1.f - powf(sinI,2));

    //if(sinI < 1.f)
    //    return RGBColor::rep(1.f);

    float rParallelSq = powf( (eta*cosR - cosI ) / ( eta*cosR + cosI), 2 );
    float rPerpendiSq = powf( (eta*cosI - cosR ) / ( eta*cosI + cosR), 2 );
    float FR = (rParallelSq + rPerpendiSq) / 2;


    return RGBColor::rep(FR);
}

RGBColor GlassMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor::rep(0.f);
}

Material::SampleReflectance GlassMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {

    Vector refRDir;                         //Refraction
    Vector refLDir;                         //Reflection
    Vector offset = normal * epsilon * 20;

    float cosI = dot(normal, outDir);           
    refLDir = outDir - 2 * cosI * normal;
    
    Vector currentNormal;
    float currentEta;
    bool comingFromAir = cosI < 0;

    if(comingFromAir)
    {
        currentEta = eta;
        cosI = -cosI;
    }
    else
    {
        currentEta = 1/eta;
        currentNormal = -normal;
        //cosI = -cosI;
    }


    float sinI = sqrt(1.0f - powf(cosI,2));
    float sinR = currentEta * sinI;
    float cosR = sqrt(1.0f - powf(sinR,2));

    refRDir = currentEta * ( outDir + cosI * currentNormal) - (cosR * currentNormal);
    
    if(random() > 0.5)
    {
        //reflection
        return SampleReflectance(-refLDir, getReflectance(texPoint + offset, currentNormal, outDir, -refLDir));
    }
    else{
        //refraction
        return SampleReflectance(-refRDir, getReflectance(texPoint - offset, currentNormal, outDir, -refRDir));
    }

}

Material::Sampling GlassMaterial::useSampling() const {
    return Material::SAMPLING_ALL; //SAMPLING_SECONDARY
}


}
*/

#include "glass.h"
#include<core/random.h>
#include <math.h>

namespace rt
{
    GlassMaterial::GlassMaterial(float eta)
    {
        this->eta = eta;
    }
    RGBColor GlassMaterial::getReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir, const Vector & inDir) const
    {
        return RGBColor(1, 1, 1); 
    }
    RGBColor GlassMaterial::getEmission(const Point & texPoint, const Vector & normal, const Vector & outDir) const
    {
        return RGBColor(0, 0, 0);
    }
    Material::SampleReflectance GlassMaterial::getSampleReflectance(const Point & texPoint, const Vector & normal, const Vector & outDir) const
    {
        // adapted from: https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
        Vector finalDirection;

        float cosThetaOut = dot(normal, -outDir);
        bool comingFromAir = cosThetaOut > 0 ? true : false;
        Vector currentNormal = normal;
        float currentEta = eta;

        if (!comingFromAir)
        {
            currentEta = 1 / eta;
            currentNormal = -1 * normal;
            cosThetaOut = -1 * cosThetaOut;
        }

        float randomN = random();

        //Ray gets reflected:
        if (randomN > 0.8)
        {
            finalDirection = (outDir + 2 * cosThetaOut * currentNormal).normalize();
        }

        // Ray get refracted:
        else
        {
            float theta1 = acos(cosThetaOut);
            float theta2 = asin(sin(theta1) / currentEta);
            Vector C = cos(theta1) * currentNormal;
            Vector M = (outDir + C) / sin(theta1);
            Vector A = sin(theta2) * M;
            Vector B = -cos(theta2) * currentNormal;
            finalDirection = (A + B).normalize();
        }       
        return SampleReflectance(finalDirection, RGBColor(1, 1, 1));
    }

}
