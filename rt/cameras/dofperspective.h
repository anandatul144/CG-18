#ifndef CG1RAYTRACER_CAMERAS_DOFPERSPECTIVE_HEADER
#define CG1RAYTRACER_CAMERAS_DOFPERSPECTIVE_HEADER

#include <rt/cameras/camera.h>
#include<core/point.h>
#include<core/vector.h>

namespace rt {


class DOFPerspectiveCamera : public Camera {
public:
    DOFPerspectiveCamera(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float verticalOpeningAngle,
        float horizonalOpeningAngle,
        float focalDistance,
        float apertureRadius
    );

    virtual Ray getPrimaryRay(float x, float y) const;

private:
    Point center;
    Vector forward;
    Vector up;
    float verticalOpeningAngle;
    float horizontalOpeningAngle;
    float focalDistance;
    float apertureRadius;
};



}


#endif
