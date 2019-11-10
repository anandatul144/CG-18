//renderer.cpp
#include "renderer.h"
#include <core/image.h>
#include <core/julia.h>
#include <cmath>
#include <rt/integrators/integrator.h>
#include <stdio.h>
#include <core/random.h>
#include<core/color.h>
#include <iostream>
#include <omp.h>




using namespace rt;

float a1computeWeight(float fx, float fy, const Point& c, float div);
RGBColor a1computeColor(uint x, uint y, uint width, uint height);


float a2computeWeight(float fx, float fy, const Point& c, float div);
RGBColor a2computeColor(const Ray& r);

namespace rt {
	

    void Renderer::test_render1(Image& img)
        {

		for(uint i = 0; i<img.height(); i++){
			for(uint j = 0; j<img.width(); j++){
                                img(j,i)=a1computeColor(j,i, img.width(), img.height());
			}
		}

	}


    void Renderer::test_render2(Image& img)
    {
    float AspectRatio= img.width()/img.height();
    float NDCx,NDCy;

    for(uint i = 0; i<img.height(); i++)
    {
        for(uint j = 0; j<img.width(); j++)
        {
           NDCx=(2*((float)j+0.5f)/img.width()) - 1;
           NDCy=(2*((float)i+0.5f)/img.height()) - 1;

           img(j,i)= a2computeColor(this->cam->getPrimaryRay(NDCx,NDCy));
        }
    }

    }

    void Renderer::render(Image& img)
    {

        float AspectRatio= img.width()/img.height();
        float NDCx,NDCy;
        #pragma omp parallel for
        for(uint i = 0; i<img.height(); i++)
        {
            #pragma omp parallel for
            for(uint j = 0; j<img.width(); j++)
            {

                if(samples>1)
                {
                    img(j,i)=RGBColor(0.0f,0.0f,0.0f);
                    for(int k=0;k<samples;k++)
                    {
                        NDCx=-((2*((float)j+random()+0.5f)/img.width()) - 1);
                        NDCy=-((2*((float)i+random()+0.5f)/img.height()) - 1);
                        img(j,i)= img(j,i) + integrator->getRadiance(this->cam->getPrimaryRay(NDCx,NDCy))/samples;

                    }
                }

                else
                {

                   NDCx=-((2*((float)j+0.5f)/img.width()) - 1);
                   NDCy=-((2*((float)i+0.5f)/img.height()) - 1);
                   img(j,i)= integrator->getRadiance(this->cam->getPrimaryRay(NDCx,NDCy));
                }


            }
            printf("%d \n",i);

        }

        }

    void Renderer::setSamples(uint samples)
    {
        this->samples=samples;
    }


}


