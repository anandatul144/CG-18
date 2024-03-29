#ifndef CG1RAYTRACER_BBOX_HEADER
#define CG1RAYTRACER_BBOX_HEADER

#include <utility>
#include <iostream>
#include <core/point.h>
#include <core/vector.h>
#include <core/macros.h>
#include <core/assert.h>
#include <iostream>
#include<core/scalar.h>

namespace rt {

class Ray;

class BBox {
public:
    Point min, max;

    BBox() {isEmpty=true;}
    BBox(const Point& min, const Point& max) : min(min), max(max) {isEmpty=false;}
    static BBox empty();
    static BBox full();

    void extend(const Point& point);
    void extend(const BBox& bbox);

    Vector diagonal() const { return max - min; }

    std::pair<float,float> intersect(const Ray& ray) const;

    Point centroidOfBBox() const;

    bool isUnbound();
    bool isEmpty;


};

int splitBox(const BBox& Bbox) ;  //get values using std::get<0>(data) and std::get<1>(data)

}


#endif
