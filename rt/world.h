#ifndef CG1RAYTRACER_WORLD_HEADER
#define CG1RAYTRACER_WORLD_HEADER

#include <rt/primitive.h>
#include <rt/solids/solid_volume.h>

namespace rt {
class Light;
class World {
public:
    Primitive* scene;
    typedef std::vector<SolidVolume*> solidVolumes;
    solidVolumes solidVols;

	typedef std::vector<Light*> LightVector;
    LightVector light;

};
}

#endif
