#ifndef CG1RAYTRACER_CAMERAS_PERSPECTIVE_HEADER
#define CG1RAYTRACER_CAMERAS_PERSPECTIVE_HEADER

#include <rt/cameras/camera.h>
#include <core/vector.h>
#include <core/point.h>
#include <rt/ray.h>
#include <cmath>

namespace rt {

class PerspectiveCamera : public Camera {
public:


    Point center;
    Vector forward;
    Vector up;
    float verticalOpeningAngle;
    float horizontalOpeningAngle;

    PerspectiveCamera(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float verticalOpeningAngle,
        float horizontalOpeningAngle
        ) : center(center), forward(forward), up(up), verticalOpeningAngle(verticalOpeningAngle), horizontalOpeningAngle(horizontalOpeningAngle) {}

    virtual Ray getPrimaryRay(float x, float y) const;
};

}


#endif
