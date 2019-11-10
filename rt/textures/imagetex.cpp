#include "imagetex.h"
#include <cmath>
#include <core/interpolate.h>
#include<iostream>


namespace rt {


float ImageTexture::texmod(float x, int control)
{
    switch(bh)
    {
        case (CLAMP): if (x<0)
                return 0;
                else if (x>control)
                return control;
                else
                return x;
            break;
        case (MIRROR): if (x<0)
                return (-fmod(x,control));
                else if (x>control)
                return fmod(x,control);
                else
                return x;


            break;
        case (REPEAT):if (x<0)
            return (-fmod(x,control));
            else if (x>control)
            return fmod(x,control);
            else
            return x;


            break;

    }
}

RGBColor ImageTexture::getColor(const Point& coord)
{
    float x =(coord.x)*image.width();
    float y=(coord.y)*image.height();
    float tmpx,tmpy;

    float xp=this->texmod(x,(image.width()-1));
    float yp=this->texmod(y,(image.height()-1));

    float x0=this->texmod(floor(x),(image.width()-1));
    float x1=this->texmod(ceil(x),(image.width()-1));
    float y0=this->texmod(floor(y),(image.height()-1));
    float y1=this->texmod(ceil(y),(image.height()-1));

    switch(i)
    {
        case (NEAREST):y=round(yp+0.49);
               x=round(xp+0.49);
               return image(x,y);
            break;
        case (BILINEAR):
               return lerp2d(image(x0,y0),image(x1,y0),image(x0,y1),image(x1,y1),fabs(xp-x0),fabs(yp-y0));
//                      y=round(yp+0.49);
//                       x=round(xp+0.49);
//                       return image(x,y);
             break;
    }


}
}
