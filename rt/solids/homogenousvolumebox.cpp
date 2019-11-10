#include "homogenousvolumebox.h"

namespace rt {

    RGBColor HomogenousVolumeBox::sigma_at(const Point &p, const Vector &v, const RGBColor &col) const {return RGBColor::rep(sig_at);}
     RGBColor HomogenousVolumeBox::sigma_os(const Point &p, const Vector &v, const RGBColor &col) const{return RGBColor::rep(sig_os);}
    RGBColor HomogenousVolumeBox::sigma_em(const Point &p, const Vector &v) const{return RGBColor::rep(sig_em);}
     RGBColor HomogenousVolumeBox::sigma_ph(const Point &p, const Vector &v1,const Vector &v2, const RGBColor &col) const{return RGBColor::rep(0.0f);}
      BBox HomogenousVolumeBox::bound()const{return bounds;}


      bool HomogenousVolumeBox::inside_check(const Point &p) const{
          if(bounds.min.x<=p.x && bounds.min.y<=p.y && bounds.min.z<=p.z)
              if(bounds.max.x>=p.x && bounds.max.y>=p.y && bounds.max.z>=p.z)
                return true;

              else
              return false;
          else
              return false;
      }




}


