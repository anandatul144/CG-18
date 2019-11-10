
#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>
#include <iostream>

#include <rt/solids/homogenousvolumebox.h>
#include <rt/solids/homogenousvolumesphere.h>
#include <rt/solids/perlinvolumesphere.h>

#include <rt/cameras/perspective.h>
#include <rt/solids/quad.h>
#include <rt/solids/sphere.h>
#include <rt/groups/simplegroup.h>
#include <rt/materials/dummy.h>

#include <rt/lights/pointlight.h>
#include <rt/lights/spotlight.h>
#include <rt/lights/directional.h>
#include <rt/lights/projectivelight.h>

#include <rt/integrators/raytrace.h>
#include <rt/integrators/volumeintegrator.h>

using namespace rt;

namespace {
void makeBox(Group* scene, const Point& aaa, const Vector& forward, const Vector& left, const Vector& up, CoordMapper* texMapper, Material* material) {
    scene->add(new Quad(aaa, forward, left, texMapper, material));
    scene->add(new Quad(aaa, forward, up, texMapper, material));
    scene->add(new Quad(aaa, left, up, texMapper, material));
    Point bbb = aaa + forward + left + up;
    scene->add(new Quad(bbb, -forward, -left, texMapper, material));
    scene->add(new Quad(bbb, -forward, -up, texMapper, material));
    scene->add(new Quad(bbb, -left, -up, texMapper, material));
}

void renderCornellboxA(float scale, const char* filename) {
    Image img(400, 400);
    World world;
    SimpleGroup* scene = new SimpleGroup();
    world.scene = scene;

    PerspectiveCamera cam(Point(250*scale, 250*scale, -800*scale), Vector(0, 0, 1), Vector(0, 1, 0), 0.686f, 0.686f);

    DummyMaterial* mat = new DummyMaterial();

    scene->add(new Quad(Point(000.f,000.f,000.f)*scale, Vector(550.f,000.f,000.f)*scale, Vector(000.f,000.f,560.f)*scale, nullptr, mat)); //floor
    scene->add(new Quad(Point(550.f,550.f,000.f)*scale, Vector(-550.f,000.f,000.f)*scale, Vector(000.f,000.f,560.f)*scale, nullptr, mat)); //ceiling
    scene->add(new Quad(Point(000.f,000.f,560.f)*scale, Vector(550.f,000.f,000.f)*scale, Vector(000.f,550.f,000.f)*scale, nullptr, mat)); //back wall
    scene->add(new Quad(Point(000.f,000.f,000.f)*scale, Vector(000.f,000.f,560.f)*scale, Vector(000.f,550.f,000.f)*scale, nullptr, mat)); //right wall
    scene->add(new Quad(Point(550.f,550.f,000.f)*scale, Vector(000.f,000.f,560.f)*scale, Vector(000.f,-550.f,000.f)*scale, nullptr, mat)); //left wall
    scene->add(new Sphere(Point(250.f,250.f,200.f)*scale,200.f*scale,nullptr,mat));
    //short box
    //makeBox(scene, Point(082.f, 000.1f, 225.f)*scale, Vector(158.f, 000.f, 047.f)*scale, Vector(048.f, 000.f, -160.f)*scale, Vector(000.f, 165.f, 000.f)*scale, nullptr, mat);

    //tall box
    //makeBox(scene, Point(265.f, 000.1f, 296.f)*scale, Vector(158.f, 000.f, -049.f)*scale, Vector(049.f, 000.f, 160.f)*scale, Vector(000.f, 330.f, 000.f)*scale, nullptr, mat);

    //point light
    //white
    world.light.push_back(new PointLight(Point(288*scale,529.99f*scale,279.5f*scale),RGBColor::rep(40000.0f*scale*scale)));
    //red
    world.light.push_back(new PointLight(Point(490*scale,329.99f*scale,279.5f*scale),RGBColor(60000.0f*scale*scale,0,0)));
    //green
    world.light.push_back(new PointLight(Point(40*scale,329.99f*scale,279.5f*scale),RGBColor(0,60000.0f*scale*scale,0)));


    //volume boxes
    //world.solidVols.push_back(new HomogenousVolumeBox(3.5f,0.f,0.0f, BBox(Point(100.f, 100.1f, 100.f)*scale,Point(250.f, 250.1f, 250.f)*scale )));
    //world.solidVols.push_back(new HomogenousVolumeSphere(3.0f,1.0f,1.0f,Point(250.f, 250.1f, 250.f)*scale,100.0f*scale ));

    //world.solidVols.push_back(new PerlinVolumeSphere(1.5f,0.f,0.f,Point(250.f, 250.1f, 250.f)*scale,150.0f*scale ));


    VolumeIntegrator integrator(&world,5.f*scale);

    Renderer engine(&cam, &integrator);
    engine.render(img);
    img.writePNG(filename);
}
}






void a_lighting_volume() {
    renderCornellboxA(0.001f, "volume_render_primary.png");
    //renderCornellboxB(0.001f, "volume_render_ambient.png");


}

