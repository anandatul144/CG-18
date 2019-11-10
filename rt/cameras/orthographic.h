#ifndef CG1RAYTRACER_CAMERAS_ORTHOGRAPHIC_HEADER
#define CG1RAYTRACER_CAMERAS_ORTHOGRAPHIC_HEADER

#include <rt/cameras/camera.h>
#include <core/vector.h>
#include <core/point.h>
#include <rt/ray.h>

namespace rt {

class OrthographicCamera : public Camera {
public:

    Point center;
    Vector forward;
    Vector up;
    Vector right;
    float scaleX, scaleY;
    OrthographicCamera(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float scaleX,
        float scaleY
        ):center(center), forward(forward), up(up), scaleX(scaleX), scaleY(scaleY) {
    }

    virtual Ray getPrimaryRay(float x, float y) const;
};

}


#endif
