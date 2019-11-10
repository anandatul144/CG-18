#include <cmath>
#include <iostream>
#include <algorithm>
#include "point.h"
#include "vector.h"


namespace rt
{

Vector::Vector(const Float4& f4)
{
	this->x = f4.x;
	this->y = f4.y;
	this->z = f4.z;
};

Vector operator*(float scalar, const Vector& b)
{
  return Vector(scalar*b.x,scalar*b.y,scalar*b.z);
}

Vector operator*(const Vector& a, float scalar)
{
 return Vector(scalar*a.x,scalar*a.y,scalar*a.z);
}

Vector operator/(const Vector& a, float scalar)
{
  return Vector(a.x/scalar,a.y/scalar,a.z/scalar);
}

Vector cross(const Vector& a, const Vector& b)

{
 return Vector(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

float dot(const Vector& a, const Vector& b)
{
    return (a.x*b.x+a.y*b.y+a.z*b.z);
}

Vector min(const Vector& a, const Vector& b)
{
 return Vector(std::min(a.x,b.x),std::min(a.y,b.y),std::min(a.z,b.z));

}

Vector max(const Vector& a, const Vector& b)
{
 return Vector(std::max(a.x,b.x),std::max(a.y,b.y),std::max(a.z,b.z));
}


Vector Vector::operator-() const
{
    return Vector(0-this->x,0-this->y,0-this->z);
}

float Vector::lensqr() const
{
 return (this->x*this->x+this->y*this->y+this->z*this->z);
}

Vector Vector::normalize() const
{
    float len=this->length();
    return Vector(this->x/len,this->y/len,this->z/len);
}

//Vector operator+(const Vector& a, const Vector& b)
//{
//    return Vector(a.x+b.x,a.y+b.y,a.z+b.z);
//}

float Vector::length() const
{
  return sqrt(this->x*this->x+this->y*this->y+this->z*this->z);
}

bool Vector::operator==(const Vector& b) const
{
 return ((this->x==b.x && this->y==b.y && this->z==b.z));
}

bool Vector::operator!=(const Vector& b) const
{
 return (!(this->x==b.x && this->y==b.y && this->z==b.z));

}


Vector Vector::operator+(const Vector& b) const
{
 return Vector(this->x+b.x,this->y+b.y,this->z+b.z);
}

Vector Vector::operator-(const Vector& b) const
{
 return Vector(this->x-b.x,this->y-b.y,this->z-b.z);
}




Point operator+(const Point& a, const Vector& b)
{
 return Point(a.x+b.x,a.y+b.y,a.z+b.z);
}

Point operator+(const Vector& a, const Point& b)
{
 return Point(a.x+b.x,a.y+b.y,a.z+b.z);
}

Point operator-(const Point& a, const Vector& b)
{
 return Point(a.x-b.x,a.y-b.y,a.z-b.z);
}




}
