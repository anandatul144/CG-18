#ifndef PLASMA_H
#define PLASMA_H

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

namespace rt{
class Plasma: public SolidVolume
{
public:
    Plasma(){}
    Plasma(Sphere* outer, Sphere * inner, const RGBColor &col1, const RGBColor &col2,const RGBColor &col3,float scale);

    virtual RGBColor sigma_at(const Point &p, const Vector &v, const RGBColor &col)const ;
    virtual RGBColor sigma_os(const Point &p, const Vector &v, const RGBColor &col)const ;
    virtual RGBColor sigma_em(const Point &p, const Vector &v)const ;
    virtual RGBColor sigma_ph(const Point &p, const Vector &v1,const Vector &v2, const RGBColor &col)const ;
    virtual BBox bound()const ;
    virtual bool inside_check(const Point &p)const;
\
    Vector dir1;
    Vector dir2;
    Vector dir3;
    RGBColor col1;
    RGBColor col2;
    RGBColor col3;
    Sphere* outer;
    Sphere* inner;
    float coeff[7];
    float width;
    float scale;
    Point innerP;
    Point center;
    Point outerP;

};

}
#endif // PLASMA_

