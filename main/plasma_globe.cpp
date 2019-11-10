
#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>
#include <iostream>


#include <rt/cameras/perspective.h>

#include <rt/solids/sphere.h>
#include <rt/solids/disc.h>
#include <rt/solids/quad.h>
#include <rt/solids/plasma.h>
#include <rt/solids/glowsphere.h>
#include <rt/groups/simplegroup.h>
#include <rt/textures/constant.h>
#include <rt/materials/dummy.h>
//#include <rt/materials/glass.h>
#include <rt/materials/fuzzymirror.h>
#include <rt/materials/lambertian.h>
#include <rt/materials/phong.h>
#include <rt/materials/mirror.h>
#include <rt/lights/pointlight.h>
#include <rt/lights/spotlight.h>
#include <random>

std::default_random_engine generator1;
std::normal_distribution<float> distribution1(0,0.04f);

#include <rt/integrators/raytrace.h>
#include <rt/integrators/recraytrace.h>
#include <rt/integrators/volumeintegrator.h>

using namespace rt;

namespace {

void renderball(float scale, const char* filename) {
    Image img(400, 400);
    World world;
    SimpleGroup* scene = new SimpleGroup();
    world.scene = scene;
    DummyMaterial* mat = new DummyMaterial();


      PerspectiveCamera cam(Point(0*scale, 0*scale, -900*scale), Vector(0, 0, 1), Vector(0, 1, 0), 0.686f, 0.686f);


    Sphere *outer = new Sphere(Point(0.f,0.f,0.f)*scale,300.f*scale,nullptr,mat);
    Sphere *inner=new Sphere(Point(0.f,0.f,0.f)*scale,80.f*scale,nullptr,mat);

    scene -> add(inner);


    world.light.push_back(new PointLight(Point(500.0f*scale,0.f,0.f),RGBColor::rep(500000.0f*scale*scale)));
    world.light.push_back(new PointLight(Point(0.f,500.0f*scale,0.f),RGBColor::rep(500000.0f*scale*scale)));

    int count=80;
    for (int i=0;i<count;i++)
        world.solidVols.push_back(new Plasma(outer,inner,RGBColor(0.35f+distribution1(generator1),0.22f+distribution1(generator1),0.4f+distribution1(generator1)),RGBColor(0.16f+distribution1(generator1),0.035f+distribution1(generator1),0.43f+distribution1(generator1)),RGBColor(0.12f,0.f,0.04f),(200.f*scale))); //blue,violet,pink in order

    world.solidVols.push_back(new glowSphere(outer,RGBColor(0.002f,0.0f,0.0007f),(200.f*scale)));
    printf("total number of volume objects: %d\n",world.solidVols.size());


    VolumeIntegrator integrator(&world,1.f*scale);

    Renderer engine(&cam, &integrator);

    engine.render(img);
    img.writePNG(filename);

}
}






void a_plasma_globe() {
    renderball(1.f, "plamsa_globe.png");

}

