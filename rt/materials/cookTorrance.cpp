#include <rt/materials/cookTorrance.h>
#include <rt/materials/material.h>
#include <core/scalar.h>
#include <math.h>

namespace rt
{
    CookTorrance::CookTorrance(Texture* texture, float diffuse,  float fresnel, float roughness)
    {
        this->texture = texture;
        this->fresnel = fresnel;
        this->diffuse = diffuse;
        this->roughness = roughness;
    }
    RGBColor CookTorrance::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
    {
        RGBColor diffusedColor = diffuse * texture->getColor(texPoint) * dot(inDir, normal) / pi;
        
        Vector normalN = normal.normalize();
        Vector halfVector = (inDir - outDir).normalize();
        float grazingViewingAngle_NdotO = std::max(dot(normalN, -outDir), 0.f);
        float grazingIlluminationAngle_NdotI = std::max(dot(normalN, inDir), 0.f);
        
        float specularCoeff = 0.0f;
        if(grazingIlluminationAngle_NdotI > 0.0f)
        {
            float IdotH = std::max(dot(inDir, halfVector), 0.f);
            float OdotH = std::max(dot(-outDir, halfVector), 0.f);
            float NdotH = std::max(dot(normalN, halfVector), 0.f);

            //Schlick approximation to the Fresnel equation
			float F = fresnel + (1 - fresnel) * powf((1 - OdotH), 5);
            // float F = fresnel + fresnel * powf((1 - OdotH), 5);

            //Microfacet Distribution / roughness
            float roughnessSq = roughness * roughness;
            float NdotHSq = NdotH * NdotH;
            float r1 =  1.0 / ( 4.0 * roughnessSq * NdotHSq * NdotHSq);
            float r2 = (NdotHSq - 1 ) / (roughnessSq * NdotHSq);
            float D = r1 * exp(r2);

            //Geometrical attenuation
            float Gb = 2 * NdotH * grazingViewingAngle_NdotO / OdotH;
            float Gc = 2 * NdotH * grazingIlluminationAngle_NdotI / IdotH;
            float G = std::min(1.0f, std::min( Gb, Gc));
            specularCoeff = F * D * G / pi * grazingIlluminationAngle_NdotI * grazingViewingAngle_NdotO;

        }

        RGBColor specularColor = (1 - diffuse) * texture->getColor(texPoint) * dot(inDir, normal) * specularCoeff;

        return diffusedColor + specularColor;
    }
    RGBColor CookTorrance::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
    {
        return RGBColor(0.0f, 0.0f, 0.0f);

    }
    Material::SampleReflectance CookTorrance::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
    {  
        return SampleReflectance();
    }
    Material::Sampling CookTorrance::useSampling() const
    {
        return Material::Sampling::SAMPLING_NOT_NEEDED;
    }
}
