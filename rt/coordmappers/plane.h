#ifndef CG1RAYTRACER_COORDMAPPERS_PLANE_HEADER
#define CG1RAYTRACER_COORDMAPPERS_PLANE_HEADER

#include <core/vector.h>
#include <core/point.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/intersection.h>


namespace rt {



class PlaneCoordMapper : public CoordMapper{
public:
    Vector e1,e2;
    PlaneCoordMapper(const Vector& e1, const Vector& e2):e1(e1),e2(e2){}
    virtual Point getCoords(const Intersection& hit) const;
};

}

#endif
