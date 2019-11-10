#include <rt/solids/triangle.h>
#include <rt/solids/infiniteplane.h>
#include <rt/intersection.h>
#include <rt/bbox.h>
#include <core/assert.h>


namespace rt {


Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3, CoordMapper* texMapper, Material* material) :
    Solid(texMapper, material), v1(v1), v2(v2), v3(v3){}

BBox Triangle::getBounds() const {
    Point pt1, pt2;
    pt1.x = min(v1.x, min(v2.x, v3.x));
    pt1.y = min(v1.y, min(v2.y, v3.y));
    pt1.z = min(v1.z, min(v2.z, v3.z));
    pt2.x = max(v1.x, max(v2.x, v3.x));
    pt2.y = max(v1.y, max(v2.y, v3.y));
    pt2.z = max(v1.z, max(v2.z, v3.z));
    return BBox(min(pt1, pt2), max(pt1, pt2));
}

Intersection Triangle::intersect(const Ray& ray, float previousBestDistance) const {

    Vector edge1 = (v2 - v1);
    Vector edge2 = (v3 - v1);
    Vector s1 = cross(ray.d, edge2);
    float denominator = dot(s1, edge1);
    if (denominator == 0) {
        return Intersection::failure();
    }
    float inv_den = 1.f / denominator;

    Vector dir = ray.o - v1;
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
    return Intersection(t, ray, this, cross(edge1, edge2).normalize(), Point(b1, b2, 1 - b1 - b2));
}


Point Triangle::sample() const {
    NOT_IMPLEMENTED;
}

float Triangle::getArea() const{
    return (0.5 * cross((v3 - v1), (v3 - v2)).length());
}

}
