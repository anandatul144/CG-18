#ifndef CG1RAYTRACER_RENDERER_HEADER
#define CG1RAYTRACER_RENDERER_HEADER

#include <core/scalar.h>
#include <rt/cameras/camera.h>
#include <rt/cameras/perspective.h>
#include <rt/ray.h>

namespace rt {

class Image;
class Camera;
class Integrator;

class Renderer {
public:
        Renderer(){samples=1;}
    Renderer(Camera* cam, Integrator* integrator): cam(cam), integrator(integrator){samples=1;}
    void setSamples(uint samples);
    void render(Image& img);
    void test_render1(Image& img);
    void test_render2(Image& img);
private:
    Camera* cam;
    Integrator* integrator;
    uint samples;
};

}

#endif
