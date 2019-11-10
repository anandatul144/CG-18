#ifndef GLOWSPHERE_H
#define GLOWSPHERE_H

#include <rt/primitive.h>
#include <rt/bbox.h>
#include <rt/materials/material.h>
#include <core/point.h>
#include <core/color.h>
#include <core/vector.h>
#include <core/assert.h>
#include <core/random.h>
#include <rt/solids/sphere.h>
#include <rt/solids/solid_volume.h>

namespace rt {


class glowSphere : public SolidVolume
{
public:
    glowSphere(){}
    glowSphere(Sphere* inner,const RGBColor &col,float scale):inner(inner),scale(scale),col(col){}
    virtual RGBColor sigma_at(const Point &p, const Vector &v, const RGBColor &col)const ;
    virtual RGBColor sigma_os(const Point &p, const Vector &v, const RGBColor &col)const ;
    virtual RGBColor sigma_em(const Point &p, const Vector &v)const ;
    virtual RGBColor sigma_ph(const Point &p, const Vector &v1,const Vector &v2, const RGBColor &col)const ;
    virtual BBox bound()const ;
    virtual bool inside_check(const Point &p)const;

    Sphere* inner;
    float width;
    float scale;
    RGBColor col;

};

}

#endif // GLOWSPHERE_H
