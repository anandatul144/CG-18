#include <rt/materials/fuzzymirror.h>
#include <core/scalar.h>
#include <core/random.h>
#include <algorithm>

namespace rt {

/*FuzzyMirrorMaterial(float eta, float kappa, float fuzzyangle);
    virtual RGBColor getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const;
    virtual RGBColor getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual SampleReflectance getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const;
    virtual Sampling useSampling() const;*/


FuzzyMirrorMaterial::FuzzyMirrorMaterial(float eta, float kappa, float fuzzyangle)
{
	this -> eta = eta;
	this -> kappa = kappa;
	this -> fuzzyangle = fuzzyangle;
}

RGBColor FuzzyMirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
        float costheta = dot(inDir, normal);
        if(costheta < 0 ) {
            costheta = -costheta;
        }
        float coeff = pow(this->eta,2) + pow(this->kappa,2);
        float r_parallel = (coeff * pow(costheta,2) - 2 * eta * costheta + 1)/(coeff * pow(costheta,2) + 2 * eta * costheta + 1);
        float r_perp = (coeff - 2 * eta * costheta + pow(costheta,2))/(coeff + 2 * eta * costheta + pow(costheta,2));
        float fr = 0.5 * (r_parallel + r_perp);
        return RGBColor::rep(fr);
}

RGBColor FuzzyMirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return RGBColor::rep(0.f);
}

Material::SampleReflectance FuzzyMirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    	//Spanning Vectors X and Y
        Vector indirection =  - outDir + 2*(dot(normal, outDir)*normal);

        //Radius of Circle (between unit distance of the hitpoint)
        float r = tan(this->fuzzyangle);
        float random1, random2;
        random1 = rt::random();
        random2 = 1 - random1;
        float x = random1 * r * cos(2*pi*random2);
        float y = random1 * r * sin(2*pi*random2);

        Point midPoint_Circle = texPoint + indirection.normalize();
        Vector indirection_perturbation = Point(midPoint_Circle.x + x, midPoint_Circle.y + y , midPoint_Circle.z) - texPoint;
        Material::SampleReflectance sampleReflectance;

        if(dot(indirection_perturbation, normal) >= 0){
            sampleReflectance.direction = indirection_perturbation;
            sampleReflectance.reflectance = getReflectance(texPoint, normal, outDir, indirection_perturbation);
        }else{
            sampleReflectance.direction = indirection ;
            sampleReflectance.reflectance = getReflectance(texPoint, normal, outDir, indirection);
        }
        return  sampleReflectance;

}

Material::Sampling FuzzyMirrorMaterial::useSampling() const {
   return Material::SAMPLING_ALL;
}

}
