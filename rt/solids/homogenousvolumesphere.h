#ifndef HOMOGENOUSVOLUMESPHERE_H
#define HOMOGENOUSVOLUMESPHERE_H

#include "solid_volume.h"
#include <rt/intersection.h>
#include <rt/bbox.h>
#include <core/color.h>
#include <core/point.h>
#include <core/vector.h>

namespace rt {


class HomogenousVolumeSphere: public SolidVolume
{
public:
    HomogenousVolumeSphere(const float &sig_at,const float &sig_os,const float &sig_em,const Point &center, const float radius):sig_at(sig_at),sig_os(sig_os),sig_em(sig_em),center(center),radius(radius){}
    virtual RGBColor sigma_at(const Point &p, const Vector &v, const RGBColor &col) const;
    virtual RGBColor sigma_os(const Point &p, const Vector &v, const RGBColor &col) const;
    virtual RGBColor sigma_em(const Point &p, const Vector &v) const;
    virtual RGBColor sigma_ph(const Point &p, const Vector &v1,const Vector &v2, const RGBColor &col) const;
    virtual BBox bound() const;
    virtual bool inside_check(const Point &p) const;


    Point center;
    float radius;
    float sig_at;
    float sig_os;
    float sig_em;


};

}
#endif // HOMOGENOUSVOLUMESPHERE_H
