#include "sphere.h"

namespace rt{

BBox Sphere::getBounds() const
{

    Point max= Point(center.x+radius,center.y+radius,center.z+radius);
    Point min= Point(center.x-radius,center.y-radius,center.z-radius);
    return BBox(min,max);
	//return BBox(max,min);
}

float Sphere::getArea() const{

    return (4*pi*radius*radius);
}

\
Intersection Sphere::intersect(const Ray& ray, float previousBestDistance) const{

 float distance=-1;
 Vector normal;
 Point local= Point(0,0,0);
 float t1,t2;
 float dx= ray.d.x; float dy=ray.d.y; float dz=ray.d.z;
 float ox=ray.o.x; float oy=ray.o.y; float oz=ray.o.z;
 float cx=center.x;float cy=center.y;float cz=center.z;

 float A = dx*dx+dy*dy+dz*dz;
 float B = 2*(dx*(ox-cx) +dy*(oy-cy)+dz*(oz-cz)) ;
 float C = (ox-cx)*(ox-cx) + (oy-cy)*(oy-cy)+ (oz-cz)*(oz-cz)- radius*radius;

 float dis=B*B-4*A*C;

 if (dis<0)
     return Intersection::failure();

 else
 {
     t1=(-B + sqrt(dis))/(2*A);
     t2=(-B - sqrt(dis))/(2*A);

     if(t1>0)
     {
         if(t1<=t2 && t1<previousBestDistance)
            { distance=t1;
            local= Relpoint(ray.o+ray.d*t1,center);
            normal=(ray.getPoint(t1)-center).normalize();
            return Intersection(distance, ray,this, normal, local);

          }
         if(t1>t2 && t2<0 && t1<previousBestDistance)
            {distance=t1;
            local= Relpoint(ray.o+t1*ray.d,center);
            normal=(ray.getPoint(t1)-center).normalize();
         return Intersection(distance, ray,this, normal, local);}
     }
     if(t2>0)
     {
         if(t2<=t1 && t2<previousBestDistance)
            { distance=t2;
             local= Relpoint(ray.o+t2*ray.d,center);
             normal=(ray.getPoint(t2)-center).normalize();
              return Intersection(distance, ray,this, normal, local);
         }
         if(t2>t1 && t1<0 && t2<previousBestDistance)
            {distance=t2;
             local= Relpoint(ray.o+t2*ray.d,center);
             normal=(ray.getPoint(t2)-center).normalize();
             return Intersection(distance, ray,this, normal, local);
         }
     }

 }


return Intersection::failure();

//Incorrent values of return object. You have to call a = Intersect(float, Ray, solid, vector)

}
}
