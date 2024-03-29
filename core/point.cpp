
#include <cmath>
#include <algorithm>
#include "vector.h"
#include "point.h"

namespace rt {
	
	Vector Point::operator-(const Point& b) const
	{
		return(Vector(this->x - b.x, this->y - b.y, this->z - b.z));
	}

	Point::Point(const Float4& f4)
	{
		this->x = f4.x/f4.w;
		this->y = f4.y/f4.w;
		this->z = f4.z/f4.w;
	};

	Point Point::operator+(const Point& b) const
	{
		return Point(this->x + b.x, this->y + b.y, this->z + b.z);
	}

	bool Point::operator==(const Point& b) const
	{
		return((this->x == b.x) && (this->y == b.y) && (this->z == b.z));
	}

	bool Point::operator!=(const Point& b) const
	{
		return((this->x != b.x) || (this->y != b.y) || (this->z != b.z));
	}

	Point operator*(float scalar, const Point& b){
		return(Point(scalar*b.x, scalar*b.y, scalar*b.z));
	}

	Point operator*(const Point& a, float scalar){
		return(Point(scalar*a.x, scalar*a.y, scalar*a.z));
	}

	Point min(const Point& a, const Point& b){
		return(Point(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)));
	}

	Point max(const Point& a, const Point& b){
		return(Point(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z)));
	}

        Point Relpoint(const Point& a,const Point& b)
        {
            return Point(a.x-b.x,a.y-b.y,a.z-b.z);
        }

        Point Point::operator/(float b) const{
            return Point(this->x/b,this->y/b,this->z/b);
        }


} 
