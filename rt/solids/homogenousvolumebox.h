#ifndef CG1RAYTRACER_HOMOGENOUSVOLUMEBOX_SOLID_HEADER
#define CG1RAYTRACER_HOMOGENOUSVOLUMEBOX_SOLID_HEADER

#include "solid_volume.h"
#include <rt/intersection.h>
#include <rt/bbox.h>
#include <core/color.h>

namespace rt {


class HomogenousVolumeBox : public SolidVolume{
public:


    HomogenousVolumeBox(const float &sig_at,const float &sig_os,const float &sig_em,const BBox bounds):sig_at(sig_at),sig_os(sig_os),sig_em(sig_em),bounds(bounds){}

   // virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
    virtual RGBColor sigma_at(const Point &p, const Vector &v, const RGBColor &col) const;
    virtual RGBColor sigma_os(const Point &p, const Vector &v, const RGBColor &col) const;
    virtual RGBColor sigma_em(const Point &p, const Vector &v) const;
    virtual RGBColor sigma_ph(const Point &p, const Vector &v1,const Vector &v2, const RGBColor &col) const;
    virtual BBox bound() const;
    virtual bool inside_check(const Point &p) const;


    float sig_at;
    float sig_os;
    float sig_em;
    BBox bounds;


};

}

#endif // HOMOGENOUSVOLUME

