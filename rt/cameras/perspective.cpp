#include"perspective.h"




namespace rt{

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const
{

    float yinv = y;

    float camx = x*tan(this->horizontalOpeningAngle/2);
    float camy = yinv*tan(this->verticalOpeningAngle/2);

    Vector x_vec = cross(this->up.normalize(),this->forward.normalize());
    Vector x_vecnorm = (x_vec.normalize())*camx;

    Vector y_vec=cross(this->forward,x_vec);
    Vector y_vecnorm = y_vec.normalize()*(camy);

    Vector rayvec1= this->forward.normalize() + y_vecnorm +x_vecnorm;
    Vector rayvecnorm=rayvec1.normalize();

    return Ray(this->center,rayvecnorm);

}

}
