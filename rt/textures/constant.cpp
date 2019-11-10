
#include "constant.h"

namespace rt {

RGBColor ConstantTexture::getColor(const Point& coord)
{
    return this->color;
}

}
