#include "striangle.h"
#include <stdio.h>

namespace rt {


SmoothTriangle::SmoothTriangle( Point vertices[3], Vector normals[3], CoordMapper* texMapper, Material* material ):Triangle(vertices[0],vertices[1],vertices[2],texMapper,material)
{	
    this->n1 = normals[0];
    this->n2 = normals[1];
    this->n3 = normals[2];            
}

SmoothTriangle::SmoothTriangle( const Point& P1, const Point& P2, const Point& P3, const Vector& n1, const Vector& n2, const Vector& n3, CoordMapper* texMapper, Material* material ) : Triangle(P1,P2,P3,texMapper,material)

{
    this->n1 = n1;
    this->n2 = n2;
    this->n3 = n3;
} 



Intersection SmoothTriangle::intersect(const Ray& ray, float previousBestDistance) const {
    Vector v12 = (P2 - P1);
    Vector v13 = (P3 - P1);
    Vector s1 = cross(ray.d, v13);

    float denominator = dot(s1, v12);
    if (denominator == 0) {
        return Intersection::failure();
    }
    float inv_den = 1.f / denominator;

    Vector dir = ray.o - P1;
    float b1 = dot(dir, s1) * inv_den;
    if (b1 < 0 || b1 > 1)
        return Intersection::failure();
    Vector s2 = cross(dir, v12);
    float b2 = dot(ray.d, s2) * inv_den;
    if (b2 < 0.0 || b1 + b2 > 1.0) {
        return Intersection::failure();
    }
    float t = dot(v13, s2) * inv_den;
    if (t > previousBestDistance || t < 0) {
        return Intersection::failure();
    }
    float b3 = 1 - b1 - b2;
    Vector barynormal = n1 * b3 + n2 * b1 + n3 * b2;
    return Intersection(t, ray, this, barynormal, Point(b1, b2, b3));


}



}
