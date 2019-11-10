#ifndef CG1RAYTRACER_COORDMAPPERS_WORLD_HEADER
#define CG1RAYTRACER_COORDMAPPERS_WORLD_HEADER

#include <core/vector.h>
#include <core/float4.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/intersection.h>

namespace rt {

class WorldMapper : public CoordMapper {
public:

    Float4 scale;

    WorldMapper(){scale=Float4(1.0f,1.0f,1.0f,1.0f);}
    explicit WorldMapper(const Float4& scale):scale(scale){}
    virtual Point getCoords(const Intersection& hit) const;
};

}

#endif
