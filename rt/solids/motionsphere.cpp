#include "motionsphere.h"
#include <core/random.h>

namespace rt
{

Intersection MotionSphere::intersect(const Ray& ray, float previousBestDistance) const{

 Point center_t= center + blurDir.normalize()*random()*0.03;
 float distance=-1;
 Vector normal;
 Point local= Point(0,0,0);
 float t1,t2;
 float dx= ray.d.x; float dy=ray.d.y; float dz=ray.d.z;
 float ox=ray.o.x; float oy=ray.o.y; float oz=ray.o.z;
 float cx=center_t.x;float cy=center_t.y;float cz=center_t.z;

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
            local= Relpoint(ray.o+ray.d*t1,center_t);
            normal=(ray.getPoint(t1)-center_t).normalize();
            return Intersection(distance, ray,this, normal, local);

          }
         if(t1>t2 && t2<0 && t1<previousBestDistance)
            {distance=t1;
            local= Relpoint(ray.o+t1*ray.d,center_t);
            normal=(ray.getPoint(t1)-center_t).normalize();
         return Intersection(distance, ray,this, normal, local);}
     }
     if(t2>0)
     {
         if(t2<=t1 && t2<previousBestDistance)
            { distance=t2;
             local= Relpoint(ray.o+t2*ray.d,center_t);
             normal=(ray.getPoint(t2)-center_t).normalize();
              return Intersection(distance, ray,this, normal, local);
         }
         if(t2>t1 && t1<0 && t2<previousBestDistance)
            {distance=t2;
             local= Relpoint(ray.o+t2*ray.d,center_t);
             normal=(ray.getPoint(t2)-center_t).normalize();
             return Intersection(distance, ray,this, normal, local);
         }
     }

 }


return Intersection::failure();

//Incorrent values of return object. You have to call a = Intersect(float, Ray, solid, vector)

}
}
