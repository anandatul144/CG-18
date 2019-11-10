#include "flatmaterial.h"
#include <stdio.h>

namespace rt{

RGBColor FlatMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
{


  return RGBColor(0,0,0);
}

RGBColor FlatMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
{

    return this->texture->getColor(texPoint);

}


}
