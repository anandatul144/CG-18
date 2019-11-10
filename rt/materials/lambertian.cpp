#include <rt/materials/lambertian.h>
#include <rt/materials/material.h>
#include <math.h>
#include <core/scalar.h>
#include <core/assert.h>
#include <algorithm>
#include <iostream>

namespace rt{

        LambertianMaterial::LambertianMaterial(Texture* emission, Texture* diffuse)
        {
                this->emission = emission;
                this->diffuse = diffuse;
        }

    RGBColor LambertianMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
    {

        auto Kd = diffuse-> getColor(texPoint);
        //return std::max(0.0f, Kd * dot(inDir, normal));
        //Clamping?
        return Kd * std::fabs(dot(inDir.normalize(), normal.normalize()))/pi;
    }

    RGBColor LambertianMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
    {
        return emission->getColor(texPoint);

    }
    Material::SampleReflectance LambertianMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
    {
        return Material::SampleReflectance();
    }
    Material::Sampling LambertianMaterial::useSampling() const
    {
        return Material::Sampling::SAMPLING_NOT_NEEDED;
    }
}


