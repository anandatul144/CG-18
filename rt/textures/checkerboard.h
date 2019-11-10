#ifndef CG1RAYTRACER_TEXTURES_CHECKERBOARD_HEADER
#define CG1RAYTRACER_TEXTURES_CHECKERBOARD_HEADER

#include <core/vector.h>

#include <rt/textures/texture.h>
#include <core/color.h>
#include <core/assert.h>

namespace rt {

    class CheckerboardTexture : public Texture {
    public:
        RGBColor white;
        RGBColor black;
        CheckerboardTexture(const RGBColor& white, const RGBColor& black):white(white),black(black){}
        virtual RGBColor getColor(const Point& coord);
        virtual RGBColor getColorDX(const Point& coord){NOT_IMPLEMENTED;}
        virtual RGBColor getColorDY(const Point& coord){NOT_IMPLEMENTED;}

    };

}

#endif
