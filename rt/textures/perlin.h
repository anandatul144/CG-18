#ifndef CG1RAYTRACER_TEXTURES_PERLIN_HEADER
#define CG1RAYTRACER_TEXTURES_PERLIN_HEADER

#include <core/vector.h>

#include <rt/textures/texture.h>
#include <core/color.h>
#include <core/scalar.h>
#include <core/assert.h>
#include <iostream>
#include <vector>


namespace rt {

    class PerlinTexture : public Texture {
    public:
        RGBColor white;
        RGBColor black;
        std::vector<float> amp;
        std::vector<float> freq;
        float noiseval;
        PerlinTexture(const RGBColor& white, const RGBColor& black):white(white),black(black){noiseval=0;}
        void addOctave(float amplitude, float frequency);
        virtual RGBColor getColor(const Point& coord);
        virtual RGBColor getColorDX(const Point& coord){NOT_IMPLEMENTED;}
        virtual RGBColor getColorDY(const Point& coord){NOT_IMPLEMENTED;}
    };

}

#endif
