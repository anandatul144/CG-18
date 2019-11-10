#include"orthographic.h"


namespace rt{


Ray OrthographicCamera::getPrimaryRay(float x, float y) const
{

    //Vector negup = Vector(0,0,0)-this->up; //inverting y direction for camera


	Vector right = cross(forward,up);


	Vector y_up = cross(right,forward);


    float camx = x;
    float camy = y;

    Vector xVec = right.normalize() * x * scaleX / 2;
    Vector yVec = y_up.normalize() * y *scaleY / 2;

    Point rayPoint(0,0,0);

    rayPoint = this -> center + xVec + yVec;

    return Ray(rayPoint, forward.normalize());

/**

    Vector xvec = cross(negup.normalize(),this->forward.normalize());
    Vector xvecnorm = (xvec.normalize())*camx;

    Vector yvec = (negup.normalize())*camy;

    Vector rayvec1= this->forward.normalize() + yvec +xvecnorm;
    Vector rayvecnorm=rayvec1.normalize();

    return Ray(Point(this->center.x+xvecnorm.x+yvec.x ,this->center.y+xvecnorm.y+yvec.y,this->center.z+xvecnorm.z+yvec.z),rayvecnorm);
**/
}

}
