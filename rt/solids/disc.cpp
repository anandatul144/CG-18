#include "disc.h"
#include <iostream>

namespace rt{

BBox Disc::getBounds() const
{
    Vector rand=cross(Vector(center.x,center.y,center.z),normal).normalize();

    float diag=radius*sqrt(2);
    Point max= center + diag*rand;
    Point min= center - diag*rand;
    return BBox(max,min);


/*    Point max= Point(center.x+radius,center.y+radius,center.z+radius);
    Point min= Point(center.x-radius,center.y-radius,center.z-radius);
    return BBox(min,max);
*/
}

float Disc::getArea() const{

    return (pi*radius*radius);
}

Intersection Disc::intersect(const Ray& ray, float previousBestDistance) const{


 Point local=Point(0,0,0);
 float t;
 float dx= ray.d.x; float dy=ray.d.y; float dz=ray.d.z;
 float ox=ray.o.x; float oy=ray.o.y; float oz=ray.o.z;
 float cx=center.x;float cy=center.y;float cz=center.z;
 float nx=normal.x;float ny=normal.y;float nz=normal.z;


 t=((-ox)*nx+(-oy)*ny+(-oz)*nz)/(dx*nx+dy*ny+dz*nz);


 float dist= Vector(ox+t*dx-cx,oy+t*dy-cy,oz+t*dz-cz).length();
 if(dist>radius || t>previousBestDistance)
         return Intersection::failure();
 else
 {
     local=Relpoint(ray.o+t*ray.d,center);
     if(t<previousBestDistance)
     return Intersection(t, ray,this, normal, local);
}


return Intersection::failure();
}

}
