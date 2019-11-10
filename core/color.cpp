#include <cmath>
#include <iostream>
//#include <algorithm>
//#include "point.h"
#include "color.h"



namespace rt{

RGBColor operator*(float scalar, const RGBColor& b)
{
 return RGBColor(b.r*scalar,b.g*scalar,b.b*scalar);
}

RGBColor operator*(const RGBColor& a, float scalar)
{
    return RGBColor(a.r*scalar,a.g*scalar,a.b*scalar);
}

RGBColor operator/(const RGBColor& a, float scalar)
{
    return RGBColor(a.r/scalar,a.g/scalar,a.b/scalar);
}

RGBColor RGBColor::operator+(const RGBColor& c) const
{
    return RGBColor(this->r+c.r,this->g+c.g,this->b+c.b);
}


RGBColor RGBColor::operator-(const RGBColor& c) const
{
 return RGBColor(this->r-c.r,this->g-c.g,this->b-c.b);
}

RGBColor RGBColor::operator*(const RGBColor& c) const
{
 return RGBColor(this->r*c.r,this->g*c.g,this->b*c.b);
}

bool RGBColor::operator==(const RGBColor& b) const
{
    return (this->r==b.r && this->g==b.g && this->b==b.b);
}

bool RGBColor::operator!=(const RGBColor& b) const
{
    return !(this->r==b.r && this->g==b.g && this->b==b.b);
}


RGBColor RGBColor::clamp() const
{
   // return RGBColor(round(this->r),round(this->g),round(this->b));

	return RGBColor(std::fmax(std::fmin(this->r, 1),0),std::fmax(std::fmin(this->g, 1),0),std::fmax(std::fmin(this->b, 1),0));
}



}
