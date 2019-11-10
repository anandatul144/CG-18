

#include "intersection.h"
#include <core/assert.h>
#include <iostream>


namespace rt{

	Intersection::Intersection(float distance, const Ray& ray, const Solid* solid, const Vector& normal, const Point& uv)
	{
			this -> ray = ray;
			this -> solid = solid;
			this -> distance = distance;
			this -> normal_V = normal;
			this -> localIP_P = uv;
                        this->intersection_b=true;


	}

        Point Intersection::hitPoint() const
	{
                return ray.getPoint(distance);
	}

	Vector Intersection::normal() const
	{
		return normal_V;
	}

	Point Intersection::local() const
	{
		return localIP_P;
	}


	Intersection::operator bool()
        {



            return this->intersection_b;

	}

        Intersection Intersection::failure(){
            Intersection a;
            a.intersection_b=false;
            return a;
        }


}
