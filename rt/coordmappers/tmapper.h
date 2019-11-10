#ifndef CG1RAYTRACER_COORDMAPPERS_TMAPPER_HEADER
#define CG1RAYTRACER_COORDMAPPERS_TMAPPER_HEADER

#include <core/point.h>
#include <core/vector.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/intersection.h>

namespace rt {

class TriangleMapper : public CoordMapper {
public:
    Point tv0,tv1,tv2;
    TriangleMapper(const Point& tv0, const Point& tv1, const Point& tv2):tv0(tv0),tv1(tv1),tv2(tv2){}
    TriangleMapper(Point ntv[3]):tv0(ntv[0]),tv1(ntv[1]),tv2(ntv[2]){}
    virtual Point getCoords(const Intersection& hit) const;

};

}



#endif
