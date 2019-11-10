#ifndef CG1RAYTRACER_COORDMAPPERS_SPHERICAL_HEADER
#define CG1RAYTRACER_COORDMAPPERS_SPHERICAL_HEADER

#include <core/point.h>
#include <core/vector.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/intersection.h>

namespace rt {

class SphericalCoordMapper : public CoordMapper {
public:
    Point origin;
    Vector z;
    Vector aR;
    SphericalCoordMapper();
    SphericalCoordMapper(const Point& origin, const Vector& zenith, const Vector& azimuthRef):origin(origin),z(zenith),aR(azimuthRef){}
    virtual Point getCoords(const Intersection& hit) const;
};

}

#endif
