#ifndef CG1RAYTRACER_COORDMAPPERS_WORLD_HEADER
#define CG1RAYTRACER_COORDMAPPERS_WORLD_HEADER

#include <core/vector.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/intersection.h>

namespace rt {

class EnvironmentMapper : public CoordMapper {
public:

    EnvironmentMapper();
    virtual Point getCoords(const Intersection& hit) const;
};

}

#endif
