#include "quad.h"
#include <iostream>
#include <core/interpolate.h>
#include <core/random.h>
#include <iostream>

namespace rt {

        Quad::Quad(const Point& p1, const Vector& span1, const Vector& span2, CoordMapper* texMapper, Material* material):Solid(texMapper, material)
	{
		this -> P1 = p1;
		this -> span1 = span1;
		this -> span2 = span2;
	}

    BBox Quad::getBounds() const
    {
        Point min=P1;
        Point max=P1;
        std::vector<Point> pts;
        pts.push_back(P1 + span1);
        pts.push_back(P1 + span2);
        pts.push_back(P1 + span1 + span2);
        for(auto i:pts)
        {
            if(i.x<min.x) min.x=i.x;
            if(i.y<min.y) min.y=i.y;
            if(i.z<min.z) min.z=i.z;
            if(i.x>max.x) max.x=i.x;
            if(i.y<max.y) max.y=i.y;
            if(i.z<max.z) max.z=i.z;
        }
        return BBox(min,max);
    }
    
    Intersection Quad::intersect(const Ray& ray, float previousBestDistance) const
    {
    	

    	Point P2 = P1 + span1;
        Point P4 = P1 + span2;
        Point P3 = P1 + span1 + span2;
        Point centroid =  (P1 +P2 + P3 + P4)/4;
        Vector normal = cross(span1,span2).normalize();
    
        InfinitePlane Quad_IP = InfinitePlane(P1, normal, nullptr,nullptr);
        Intersection intersection_IP = Quad_IP.intersect(ray,previousBestDistance);

    	if(intersection_IP)		//calling intersection.bool() for intersetion of ray and IF
    	{
    		Point P = intersection_IP.hitPoint();
                //Vector normal_P_23= cross(P3-P2, int_P - P2);
    		//float u = (normal_P_23)

                float t1 = dot(cross(P2-P1, P-P1).normalize(),normal);
                if(t1 < 0)
    			return Intersection::failure();

                float t2 = dot(cross(P3-P2, P-P2).normalize(), normal);
                if(t2 < 0)
                        return Intersection::failure();

                float t3 = dot(cross(P4-P3, P-P3).normalize(), normal);
                if (t3 < 0)
    			return Intersection::failure();

                float t4 = dot(cross(P1-P4, P-P4).normalize(), normal);
                if (t4 < 0 || intersection_IP.distance>previousBestDistance)
    			return Intersection::failure();

                return Intersection((P - ray.o).length(),ray,this,normal,Relpoint(P,centroid));

    	}
        return Intersection::failure();
    }


	Solid::Sample Quad::sample() const { 
        //Rand1 Ran2
        //V1 * R1, V2 * R2
        //Point Rand = V1R1 V2R2
        Solid::Sample smpl_Qd;
        float r1=random();
        if(r1>0.5f)
        smpl_Qd.point = lerpbar(P1, P1 + span1, P1 + span2, random(), random());
        else
        smpl_Qd.point = lerpbar(P1+ span1+ span2, P1 + span1, P1 + span2, random(), random());
        smpl_Qd.normal = cross(span1, span2).normalize();

        return smpl_Qd;

     }
    float Quad::getArea() const{ return cross(span1,span2).length();	}
}
