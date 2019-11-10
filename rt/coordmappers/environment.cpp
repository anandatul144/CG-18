#include "environment.h"

namespace rt{

Point EnvironmentMapper::getCoords(const Intersection& hit) const
{

// printf("EnvironmentMapper ran \n");
 return Point(hit.ray.d.x,hit.ray.d.y,hit.ray.d.z);
}

}
