#include "glowsphere.h"

namespace rt {

RGBColor glowSphere::sigma_ph(const Point &p, const Vector &v1,const Vector &v2, const RGBColor &col)const{return RGBColor::rep(0.0f);}
RGBColor glowSphere::sigma_at(const Point &p, const Vector &v, const RGBColor &col)const{return RGBColor::rep(0.0f);}
RGBColor glowSphere::sigma_os(const Point &p, const Vector &v, const RGBColor &col)const{return RGBColor::rep(0.0f);}
BBox glowSphere::bound()const{return BBox(Point(0,0,0), Point(1.f,1.f,1.f));}


RGBColor glowSphere::sigma_em(const Point &p, const Vector &v)const
{
return col;
}

bool glowSphere::inside_check(const Point &p)const
{
  float dist= (p-inner->center).length();
  if(abs(dist-inner->radius)<0.03f)
      return true;
  else
      return false;
}




}
