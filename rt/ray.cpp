#include <cmath>
#include "ray.h"
#include <core/point.h>
#include <core/vector.h>

namespace rt{

Point Ray::getPoint(float distance) const{

    return (this->o + distance*this->d);

}

}
