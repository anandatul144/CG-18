#ifndef PERLINVOLUMESPHERE_H
#define PERLINVOLUMESPHERE_H

#include "solid_volume.h"
#include <rt/intersection.h>
#include <rt/bbox.h>
#include <core/color.h>
#include <core/point.h>
#include <core/vector.h>
#include <rt/textures/perlin.h>

namespace rt {
class PerlinVolumeSphere: public SolidVolume
{
public:
    PerlinVolumeSphere(const float &sig_at,const float &sig_os,const float &sig_em,const Point &center, const float radius):sig_at(sig_at),sig_os(sig_os),sig_em(sig_em),center(center),radius(radius){
        perlinTex->addOctave(0.5f, 5.0f);
        perlinTex->addOctave(0.25f, 10.0f);
        perlinTex->addOctave(0.125f, 20.0f);
        perlinTex->addOctave(0.125f, 40.0f);
    }
    virtual RGBColor sigma_at(const Point &p, const Vector &v, const RGBColor &col) const;
    virtual RGBColor sigma_os(const Point &p, const Vector &v, const RGBColor &col) const;
    virtual RGBColor sigma_em(const Point &p, const Vector &v) const;
    virtual RGBColor sigma_ph(const Point &p, const Vector &v1,const Vector &v2, const RGBColor &col) const;
    virtual BBox bound() const;
    virtual bool inside_check(const Point &p) const;


    PerlinTexture* perlinTex = new PerlinTexture(RGBColor(2.0f,2.0f,2.0f), RGBColor(0.0f,0.0f,0.0f));

    Point center;
    float radius;
    float sig_at;
    float sig_os;
    float sig_em;


};
}

#endif // PERLINVOLUMESPHERE_H
