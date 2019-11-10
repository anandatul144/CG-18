#include <rt/materials/phong.h>
#include <core/assert.h>
#include <rt/materials/material.h>
#include <rt/textures/texture.h>    
#include <math.h>



namespace rt{

	PhongMaterial::PhongMaterial(Texture* specular, float exponent)
	{
		this->specular = specular;
		this->exponent = exponent;
	}
    RGBColor PhongMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
    {
    	//Reflcection = 2(Normal⋅Light)Normal−Li.
    	//
    	auto R = (2 * normal * dot(normal,inDir) - inDir).normalize();
    	if (dot(R, normal) < 0 || dot(inDir, normal) < 0)
    		return RGBColor(0,0,0);
    	//Spcular = dot(R,ray.d)
    	auto Spec = dot(R,outDir.normalize());
    	//I = K *(spec . R)**e
    	//getColor from texture.h
    	auto Phong_R = specular->getColor(texPoint) * powf(Spec,exponent);
    	return Phong_R;

    }
    RGBColor PhongMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
    {

    	return RGBColor(0.0f, 0.0f, 0.0f);


    }
    Material::SampleReflectance PhongMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
    {
    	return SampleReflectance(); 
    }
    Material::Sampling PhongMaterial::useSampling() const
    {
    	return Material::Sampling::SAMPLING_NOT_NEEDED;
    }

}
