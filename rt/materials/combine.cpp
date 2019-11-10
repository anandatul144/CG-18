#include <rt/materials/combine.h>
#include <core/assert.h>
#include <rt/materials/material.h>
#include <rt/textures/texture.h>
#include <vector>
#include <bits/stdc++.h>


namespace rt {
    CombineMaterial::CombineMaterial() {};
    void CombineMaterial::add(Material* material, float weight)
    {
        layer layer1 = {material,weight};
        LayeredMaterials.push_back(layer1);
        
        //Assume that at most one of the combined materials requires sampling
        // So I guess we only compare the weights and use the one with max weight? not a combined texture

        std::sort(LayeredMaterials.begin(),LayeredMaterials.end(),compareWeights);
        //reverse sort layers on weight value
        Material::Sampling sampling = LayeredMaterials.begin()->material->useSampling();

    }
    
    RGBColor CombineMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
    {
        RGBColor color = RGBColor(0.0f,0.0f,0.0f);
        color = color + LayeredMaterials.begin()->weight * LayeredMaterials.begin()->material->getReflectance(texPoint,normal,outDir,inDir);
        return color;
    }
    
    RGBColor CombineMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
    {
        RGBColor color = RGBColor(0.0f,0.0f,0.0f);
        color = color + LayeredMaterials.begin()->weight * LayeredMaterials.begin()->material->getEmission(texPoint,normal,outDir);
        return color;
    }

    Material::SampleReflectance CombineMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
    {
        SampleReflectance sampleReflectance = LayeredMaterials.begin()->material->getSampleReflectance(texPoint, normal, outDir);
        sampleReflectance.reflectance = LayeredMaterials.begin()->weight * sampleReflectance.reflectance;

        return sampleReflectance;
    }
    Material::Sampling CombineMaterial::useSampling() const
    {
        return Material::Sampling::SAMPLING_NOT_NEEDED;
    }

    bool CombineMaterial::compareWeights(layer l1, layer l2) 
    {
        return (l1.weight > l2.weight);
        //reverse sort
    }
}
