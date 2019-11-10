#include <rt/cameras/dofperspective.h>
#include <rt/ray.h>
#include <math.h>
#include <core/random.h>

namespace rt {

DOFPerspectiveCamera::DOFPerspectiveCamera( const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle, float focalDistance, float apertureRadius)
{
    this->center=center;
    this->forward=forward;
    this->up=up;
    this->verticalOpeningAngle=verticalOpeningAngle;
    this->horizontalOpeningAngle=horizontalOpeningAngle;
    this->focalDistance=focalDistance;
    this->apertureRadius=apertureRadius;

}

Ray DOFPerspectiveCamera::getPrimaryRay( float x, float y ) const {
    float yinv = y;

    float camx = x*tan(this->horizontalOpeningAngle/2);
    float camy = yinv*tan(this->verticalOpeningAngle/2);

    Vector x_vec = cross(this->up.normalize(),this->forward.normalize());
    Vector x_vecnorm = (x_vec.normalize())*camx;

    Vector y_vec=cross(this->forward,x_vec);
    Vector y_vecnorm = y_vec.normalize()*(camy);

    Vector rayvec1= this->forward.normalize() + y_vecnorm +x_vecnorm;
    Vector rayvecnorm=rayvec1.normalize();

    Point f_point= Ray(this->center,rayvecnorm).getPoint(this->focalDistance);
    float angle=random()*2*3.1416;
    float radius=random()*this->apertureRadius;
    Point center_t= this->center + x_vec*radius*angle + y_vec*radius*angle;

    return Ray(center_t,(f_point-center_t).normalize());
}

}
