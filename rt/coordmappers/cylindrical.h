#ifndef CG1RAYTRACER_COORDMAPPERS_CYLINDRICAL_HEADER
#define CG1RAYTRACER_COORDMAPPERS_CYLINDRICAL_HEADER

#include <core/point.h>
#include <core/vector.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/intersection.h>

namespace rt {


class CylindricalCoordMapper : public CoordMapper {
public:
    Point origin;
    Vector lA,pA;
    CylindricalCoordMapper(const Point& origin, const Vector& longitudinalAxis, const Vector& polarAxis):origin(origin),lA(longitudinalAxis),pA(polarAxis){}
    virtual Point getCoords(const Intersection& hit) const;
};

}

#endif
