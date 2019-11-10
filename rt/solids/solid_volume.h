#ifndef CG1RAYTRACER_SOLIDVOLUME_SOLID_HEADER
#define CG1RAYTRACER_SOLIDVOLUME_SOLID_HEADER

#include <rt/primitive.h>
#include <rt/bbox.h>
#include <rt/materials/material.h>
#include <core/point.h>
#include <core/color.h>
#include <core/vector.h>
#include <core/assert.h>
#include <rt/intersection.h>


namespace rt {


class SolidVolume {
public:




    SolidVolume(){}
    virtual RGBColor sigma_at(const Point &p, const Vector &v, const RGBColor &col) const=0;
    virtual RGBColor sigma_os(const Point &p, const Vector &v, const RGBColor &col) const=0;
    virtual RGBColor sigma_em(const Point &p, const Vector &v) const=0;
    virtual RGBColor sigma_ph(const Point &p, const Vector &v1,const Vector &v2, const RGBColor &col) const=0;
    virtual BBox bound() const=0;
    virtual bool inside_check(const Point &p) const=0;






};

}


#endif
