#ifndef CG1RAYTRACER_PRIMMOD_INSTANCE_HEADER
#define CG1RAYTRACER_PRIMMOD_INSTANCE_HEADER

#include <rt/primitive.h>
#include <core/assert.h>
#include <core/matrix.h>
#include <core/float4.h>

namespace rt {

class Instance : public Primitive {
public:

    Primitive* Content;
    Matrix T;           //Final transformation matrix on Ray
    Material* material;

    Instance(Primitive* content);
    Primitive* content();

    void reset(); //reset transformation back to identity
    void translate(const Vector& t);
    void rotate(const Vector& axis, float angle);
    void scale(float scale);
    void scale(const Vector& scale);

    //Primitive virtual class functions
    BBox getBounds() const;
    Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
    void setMaterial(Material* m) { NOT_IMPLEMENTED; }
    void setCoordMapper(CoordMapper* cm) { NOT_IMPLEMENTED; }
    float getArea() const { NOT_IMPLEMENTED; }

};

}

#endif
