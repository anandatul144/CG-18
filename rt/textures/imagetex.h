#ifndef CG1RAYTRACER_TEXTURES_IMAGETEX_HEADER
#define CG1RAYTRACER_TEXTURES_IMAGETEX_HEADER

#include <core/vector.h>
#include <core/image.h>
#include <rt/textures/texture.h>
#include <core/assert.h>

namespace rt {

class ImageTexture : public Texture {
public:

    enum BorderHandlingType {
        CLAMP,
        MIRROR,
        REPEAT
    };

    enum InterpolationType {
        NEAREST,
        BILINEAR
    };

    Image image;
    BorderHandlingType bh;
    InterpolationType i;

    ImageTexture();
    ImageTexture(const Image& image, BorderHandlingType bh=REPEAT, InterpolationType i=BILINEAR):image(image),i(i),bh(bh){}
    ImageTexture(const std::string& filename, BorderHandlingType bh=REPEAT, InterpolationType i=BILINEAR):i(i),bh(bh){this->image.readPNG(filename);}
    virtual RGBColor getColor(const Point& coord);
    virtual RGBColor getColorDX(const Point& coord){NOT_IMPLEMENTED;}
    virtual RGBColor getColorDY(const Point& coord){NOT_IMPLEMENTED;}
    float texmod(float x,int i);
};

}

#endif
