#include "checkerboard.h"
#include <math.h>
#include <stdio.h>

namespace rt {
RGBColor CheckerboardTexture::getColor(const Point& coord)
{
 float x= (coord.x) - (float)floor(coord.x);
 float y= (coord.y)- (float)floor(coord.y);
 float z= (coord.z)- (float)floor(coord.z);
 if(x>=0.5)
 {
     if(y>=0.5)
     {
         if(z>=0.5)
         return white;
         else
             return black;
     }
     else
     {
         if(z>=0.5)
         return black;
         else
             return white;

     }
 }
     else
 {
     if(y>=0.5)
     {
         if(z>=0.5)
         return black;
         else
             return white;

     }
     else
     {
         if(z>=0.5)
         return white;
         else
             return black;

     }
 }
}


}
