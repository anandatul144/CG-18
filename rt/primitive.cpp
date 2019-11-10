#ifndef CG1RAYTRACER_PRIMITIVE_HEADER
#define CG1RAYTRACER_PRIMITIVE_HEADER

#include "primitve.h"
#include <core/assert.h>


namespace rt {

	//Each of these functionalities are virtual and implemented in individual solids class.
	
	virtual BBox Primitive::getBounds() const =0;
    virtual Intersection Primitive::intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const =0;
    virtual void Primitive::setMaterial(Material* m) { NOT_IMPLEMENTED; }
    virtual void Primitive::setCoordMapper(CoordMapper* cm) { NOT_IMPLEMENTED; }
}