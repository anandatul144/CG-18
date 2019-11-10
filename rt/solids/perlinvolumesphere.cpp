#include "perlinvolumesphere.h"
#include <iostream>


namespace rt{

RGBColor PerlinVolumeSphere::sigma_at(const Point &p, const Vector &v, const RGBColor &col) const {
    RGBColor color=sig_at*perlinTex->getColor(p);

    return color;

}




RGBColor PerlinVolumeSphere::sigma_os(const Point &p, const Vector &v, const RGBColor &col) const{return RGBColor::rep(sig_os);}

RGBColor PerlinVolumeSphere::sigma_em(const Point &p, const Vector &v) const{return RGBColor::rep(sig_em);}
 RGBColor PerlinVolumeSphere::sigma_ph(const Point &p, const Vector &v1,const Vector &v2, const RGBColor &col) const{return RGBColor::rep(0.0f);}


 BBox PerlinVolumeSphere::bound() const
 {

     Point max= Point(center.x+radius,center.y+radius,center.z+radius);
     Point min= Point(center.x-radius,center.y-radius,center.z-radius);
     return BBox(min,max);
         //return BBox(max,min);
 }


 bool PerlinVolumeSphere::inside_check(const Point &p) const
 {
     if((p-center).length()<radius)
         return true;
     else
         return false;

 }
}


