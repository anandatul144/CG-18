
#include "dummy.h"
#include <iostream>
#include<cmath>

namespace rt {

RGBColor DummyMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const
{

  float cos=(dot(inDir.normalize(),normal.normalize()));
  return RGBColor(cos,cos,cos);
}

RGBColor DummyMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const
{

    return RGBColor(0,0,0);



}


}
