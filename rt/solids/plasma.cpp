#include "plasma.h"
#include "math.h"
#include <iostream>
#include <random>

std::default_random_engine generator;
std::normal_distribution<float> distribution(0,0.05f);

namespace rt{



Plasma::Plasma(Sphere* outer, Sphere * inner,const RGBColor &col1, const RGBColor &col2,const RGBColor &col3,float scale) // scale should be inverse of radius
{
    this->outer=outer;
    this->inner=inner;
    this->center=inner->center;
    this->col1=col1;
    this->col2=col2;
    this->col3=col3;
    this->scale=scale;
    this->dir1=Vector(random(),random(),random()).normalize();
    this->dir2=Vector(random(),random(),random()).normalize();
    this->dir3=Vector(random(),random(),random()).normalize();
    coeff[0]=2.f*(random()+0.2f);
    coeff[1]=2.f*(random()+0.2f);
    coeff[2]=2.f*(random()+0.2f);
    coeff[3]=random();
    coeff[4]=random();
    coeff[5]=random()*pi*2; //phase for width
    coeff[6]=random()*pi*2; //phase for width
    width=(0.5f+random()/2.f)*0.02f*scale; //In terms of unit radius sphere
    float theta=random()*pi +0.9f; float phi=random()*pi*2 +0.9f;

    float noisetheta=distribution(generator);
    float noisephi=distribution(generator);


    innerP=inner->center+inner->radius*Vector(cos(phi)*sin(theta),sin(phi)*sin(theta),cos(theta)).normalize();
    outerP=outer->center+outer->radius*Vector(cos(phi+noisephi)*sin(theta+noisetheta),sin(phi+noisephi)*sin(theta+noisetheta),cos(theta+noisetheta)).normalize();
    float a1=random();float a2=random();float a3=random();
    float b1 =random();float b2 =random();float b3 =random();

    Vector norm=(innerP-outerP).normalize();
    float c1=(-norm.x*a1-norm.y*b1)/norm.z;
    float c2=(-norm.x*a2-norm.y*b2)/norm.z;
    float c3=(-norm.x*a3-norm.y*b3)/norm.z;
    this->dir1=Vector(a1,b1,c1).normalize();
    this->dir2=Vector(a2,b2,c2).normalize();
    this->dir3=Vector(a3,b3,c3).normalize();
    printf("Inner Point :%f %f %f\n",innerP.x,innerP.y,innerP.z);
    printf("Outer Point :%f %f %f\n",outerP.x,outerP.y,outerP.z);



}


RGBColor Plasma::sigma_ph(const Point &p, const Vector &v1,const Vector &v2, const RGBColor &col)const{return RGBColor::rep(0.0f);}
RGBColor Plasma::sigma_at(const Point &p, const Vector &v, const RGBColor &col)const{return RGBColor::rep(0.0f);}
RGBColor Plasma::sigma_os(const Point &p, const Vector &v, const RGBColor &col)const{return RGBColor::rep(0.0f);}


RGBColor Plasma::sigma_em(const Point &p, const Vector &v)const
{

    RGBColor cola;
    RGBColor colb;
    RGBColor colc;
    float t= dot((p-innerP),(outerP-innerP))/dot(outerP-innerP,outerP-innerP);
    Point proj= innerP + t*(outerP-innerP);
    float linelength= (outerP-innerP).length();
    float projlength= (proj-innerP).length();
    float factor=projlength/linelength;
    float offset_dist1= 0.3*coeff[1]*sin(2*pi*factor*0.5)*scale*0.01f;
    float offset_dist2= coeff[0]*sin(2*pi*factor)*scale*0.01f;
    float offset_dist3= 1.5*coeff[2]*sin(2*pi*factor*1.25)*scale*0.01f;
    Point curve_point= proj+offset_dist1*dir1+offset_dist2*dir2+offset_dist3*dir3;
    float dist=(p-curve_point).length();


    cola=20.f*(fabs(width-dist)/scale)*col1*exp(-75.0f*dist/scale)+7.f*(dist/scale)*col2*exp(-100.0f*fabs(width-dist)/scale);  //scale to unit radius sphere
    colb=(exp(-100*t)+exp(-100*(1-t)))*col3 - exp(-100*(1-t))*cola;
    return cola+colb;

}




BBox Plasma::bound()const{return BBox(Point(0,0,0), Point(1.f,1.f,1.f));}



bool Plasma::inside_check(const Point &p)const
{
 float t= dot((p-innerP),(outerP-innerP))/dot(outerP-innerP,outerP-innerP);
 if(t>=0 && t<=1)
 {
     if((p-center).length()>(outerP-center).length() || (p-center).length()<(innerP-center).length())
         return false;

     Point proj= innerP + t*(outerP-innerP);
     float linelength= (outerP-innerP).length();
     float projlength= (proj-innerP).length();
     float factor=projlength/linelength;
     float offset_dist1= 0.3*coeff[1]*sin(2*pi*factor*0.5)*scale*0.01f;
     float offset_dist2= coeff[0]*sin(2*pi*factor)*scale*0.01f;
     float offset_dist3= 1.5*coeff[2]*sin(2*pi*factor*1.25)*scale*0.01f;
     float offset_dist4=0.2f*exp(-40*t)+exp(-40*(1-t)); //end artifacts
     float width_change=(coeff[3]*sin(3.2*pi*t+coeff[6])+coeff[4]*sin(2.5*pi*t+coeff[5]))*width*0.3f;
     Point curve_point= proj+offset_dist1*dir1+offset_dist2*dir2+offset_dist3*dir3;

     if((p-curve_point).length()<width+offset_dist4*width*5+width_change)
         return true;
     else
         return false;
 }
 else
     return false;
}

}
