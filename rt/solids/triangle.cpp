
#include "triangle.h"
#include <core/random.h> 


namespace rt {



    float Triangle::getArea() const{
        return area;
    }

    Triangle::Triangle(const Point& P1, const Point& P2, const Point& P3, CoordMapper* texMapper, Material* material) :
        P1(P1), P2(P2), P3(P3),Solid(texMapper, material)
    {
        Vector v12 = P2 - P1;
        Vector v13 = P3 - P1;
        this->normal = cross(v12, v13).normalize();
        this->area = cross(v12,v13).length()/2;
    }

    Triangle::Triangle(Point vertices[3], CoordMapper* texMapper, Material* material) : Solid(texMapper, material)
    {
        this->P1 = vertices[0];
        this->P2 = vertices[1];
        this->P3 = vertices[2];

        Vector v12 = P2 - P1;
        Vector v13 = P3 - P1;
        this->normal = cross(v12, v13).normalize();
        this->area = cross(v12,v13).length()/2;
    }

    BBox Triangle::getBounds() const {
        Point pt1, pt2;
        pt1.x = min(P1.x, min(P2.x, P3.x));
        pt1.y = min(P1.y, min(P2.y, P3.y));
        pt1.z = min(P1.z, min(P2.z, P3.z));
        pt2.x = max(P1.x, max(P2.x, P3.x));
        pt2.y = max(P1.y, max(P2.y, P3.y));
        pt2.z = max(P1.z, max(P2.z, P3.z));
        return BBox(min(pt1, pt2), max(pt1, pt2));
    }

    Intersection Triangle::intersect(const Ray& ray, float previousBestDistance) const {

        Vector edge1 = (P2 - P1);
        Vector edge2 = (P3 - P1);
        Vector s1 = cross(ray.d, edge2);
        float denominator = dot(s1, edge1);
        if (denominator == 0) {
            return Intersection::failure();
        }
        float inv_den = 1.f / denominator;

        Vector dir = ray.o - P1;
        float b1 = dot(dir, s1) * inv_den;
        if (b1 < 0 || b1 > 1)
            return Intersection::failure();
        Vector s2 = cross(dir, edge1);
        float b2 = dot(ray.d, s2) * inv_den;
        if (b2 < 0.0 || b1 + b2 > 1.0) {
            return Intersection::failure();
        }
        float t = dot(edge2, s2) * inv_den;
        if (t > previousBestDistance || t < 0) {
            return Intersection::failure();
        }
        return Intersection(t, ray, this, cross(edge1, edge2).normalize(), bary(ray.getPoint(t)));
    }



    float areaTri(Vector a,Vector b)
    {
        return (cross(a,b).length())/2;
    }

    Point Triangle::bary(Point hitpoint) const {
        Point hitP=hitpoint;
        float bary1=areaTri(hitP-P2,hitP-P3)/areaTri(P1-P2,P1-P3);
        float bary2=areaTri(hitP-P3,hitP-P1)/areaTri(P2-P3,P2-P1);
        float bary3=areaTri(hitP-P1,hitP-P2)/areaTri(P3-P1,P3-P2);
        return Point(bary1,bary2,bary3);

    }

    Solid::Sample Triangle::sample() const
    {

        float r1 = random()/0.33f;
        float r2 = random()/0.33;
        float r3 = (1-r1)-r2;
        Point randomPoint = ((r1*P1 + r2 * P2 + r3*P3));

        Solid::Sample smpl_Tr;
        smpl_Tr.point = randomPoint;
        smpl_Tr.normal = this->normal;

        return smpl_Tr;

    }

}

