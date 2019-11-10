#ifndef CG1RAYTRACER_EFFECTS_MOTION_BLUR_SPHERE
#define CG1RAYTRACER_EFFECTS_MOTION_BLUR_SPHERE

#include <rt/solids/sphere.h>
#include<core/point.h>
#include<core/vector.h>
#include<rt/intersection.h>

namespace rt {

class CoordMapper;
class Material;

class MotionSphere : public Sphere  {
public:
    MotionSphere(const Point& center, float radius, CoordMapper* texMapper, Material* material,Vector blurDir):Sphere(center,radius,texMapper,material),blurDir(blurDir){}
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
private:
    Vector blurDir; //Direction of blur

};



}


#endif
