#include <rt/materials/mirror.h>
#include <core/assert.h>
#include <math.h>
#include <algorithm>


namespace rt{
	MirrorMaterial::MirrorMaterial(float eta, float kappa)
	{
		this->eta = eta;
		this-> kappa = kappa;
	}
    RGBColor MirrorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
    {
    	float costheta = dot(inDir, normal);
        if(costheta < 0 ) {
            costheta = -costheta;
        }
        float coeff = powf(this->eta,2) + powf(this->kappa,2);
        float r_parallel = (coeff * powf(costheta,2) - 2 * eta * costheta + 1)/(coeff * powf(costheta,2) + 2 * eta * costheta + 1);
        float r_perp = (coeff - 2 * eta * costheta + powf(costheta,2))/(coeff + 2 * eta * costheta + powf(costheta,2));
        float fr = 0.5 * (r_parallel + r_perp);
        return RGBColor::rep(fr);
    }
    RGBColor MirrorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
    {

        return RGBColor (0.0f, 0.0f, 0.0f);


    }

    Material::SampleReflectance MirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const{
        float eta_kappa_sqr = (eta*eta) + (kappa*kappa);
        float two_eta = 2 * eta;
        Vector ref_dir = -outDir + (2 * dot(outDir.normalize(), normal.normalize()) * normal);
        ref_dir = ref_dir.normalize();

        float cos_i = dot(ref_dir, normal.normalize());
        float cos_i_sq = cos_i * cos_i;
        float two_n_cos_theta = two_eta * cos_i;

        float r_perp = (eta_kappa_sqr) - (two_n_cos_theta)+ cos_i_sq;
        r_perp = r_perp / ((eta_kappa_sqr) + (two_n_cos_theta)+cos_i_sq);

        float r_para = ((eta_kappa_sqr) * cos_i_sq) - (two_n_cos_theta) + 1;
        r_para = r_para / (((eta_kappa_sqr) * cos_i_sq) + (two_n_cos_theta) + 1);

        return SampleReflectance(ref_dir, RGBColor::rep(0.5f * (r_para + r_perp)) );
    }



//    Material::SampleReflectance MirrorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const
//    {
//    	Vector dir = 2 * dot(outDir, normal) * normal - outDir;
//    	RGBColor color = getReflectance(texPoint, normal, outDir, dir);
//    	return SampleReflectance(dir, color);
//    }
    Material::Sampling MirrorMaterial::useSampling() const
    {
        return Material::Sampling::SAMPLING_ALL;
    }
}
