#ifndef CG1RAYTRACER_SOLIDS_SOLID_HEADER
#define CG1RAYTRACER_SOLIDS_SOLID_HEADER

#include <rt/primitive.h>
#include <rt/bbox.h>
#include <core/assert.h>
#include <core/float4.h>
#include <rt/materials/material.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/coordmappers/world.h>

namespace rt {

class Material;
class CoordMapper;

/*
A solid is a physical primitive that has material and can be textured
*/

/*static WorldMapper defaultMapper();


class Solid : public Primitive {
public:
	struct Sample {
        Point point;
        Vector normal;
    };

    Material* material ;
    //CoordMapper* texMapper = new WorldMapper();

    CoordMapper* texMapper;
    Solid();
    explicit Solid(CoordMapper* texMapper, Material* material):material(material)
    {
        if(texMapper) this->texMapper=texMapper;
        else
            this->texMapper = &rt::defaultMapper;
    }*/

    static WorldMapper defaultMapper(Float4(1.0f, 1.0f, 1.0f, 0.0f));
class Solid : public Primitive {
public:
    struct Sample {
        Point point;
        Vector normal;
    };
    Material* material;
    //CoordMapper* texMapper= WorldMapper(Float4(1.0f, 1.0f, 1.0f, 0.0f));
    CoordMapper* texMapper;
    explicit Solid(CoordMapper* texMapper, Material* material):material(material)
    {
        if(texMapper) 
            this->texMapper=texMapper; 
        else 
            this->texMapper = &rt::defaultMapper;
    }
    Solid();
	virtual Sample sample() const = 0;
    virtual float getArea() const {}
    virtual void setMaterial(Material* m){this->material=m;}
    virtual void setCoordMapper(CoordMapper* cm) {  texMapper = cm;}
};

}


#endif
