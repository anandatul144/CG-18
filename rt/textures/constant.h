#ifndef CG1RAYTRACER_TEXTURES_CONSTANT_HEADER
#define CG1RAYTRACER_TEXTURES_CONSTANT_HEADER

#include <core/vector.h>

#include <rt/textures/texture.h>
#include <core/color.h>
#include <core/assert.h>

namespace rt {

class ConstantTexture : public Texture {
public:

    ConstantTexture();
    ConstantTexture(const RGBColor& color):color(color){}
    virtual RGBColor getColor(const Point& coord);
    virtual RGBColor getColorDX(const Point& coord){NOT_IMPLEMENTED;}
    virtual RGBColor getColorDY(const Point& coord){NOT_IMPLEMENTED;}
private:
	RGBColor color;
};

}

#endif
