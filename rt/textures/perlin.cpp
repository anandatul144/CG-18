#include <rt/textures/perlin.h>
#include <core/point.h>
#include <core/interpolate.h>
#include <core/scalar.h>
#include <cmath>
#include <iostream>

namespace rt {

namespace {

    /* returns a value in range -1 to 1 */
    float noise(int x, int y, int z) {
        int n = x + y * 57 + z * 997;
        n = (n<<13) ^ n;
        return ( 1.0f - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
    }

}

void PerlinTexture::addOctave(float amplitude, float frequency)
{
 amp.push_back(amplitude);
 freq.push_back(frequency);
}

RGBColor PerlinTexture::getColor(const Point& coord)
{
    float noise_val = 0.0f;
    for(int i = 0; i < freq.size(); ++i){
        Point coord_new = coord * freq.at(i);
        float noise_ = 0.0f;


        int lu = floor(coord_new.x);
        int lv = floor(coord_new.y);
        int lw = floor(coord_new.z);
        float fu = coord_new.x - lu;
        float fv = coord_new.y - lv;
        float fw = coord_new.z - lw;



        float p1 = noise(lu, lv, lw);
        float p2 = noise(lu + 1, lv, lw);
        float p3 = noise(lu, lv + 1, lw);
        float p4 = noise(lu + 1, lv + 1, lw);
        float p5 = noise(lu, lv, lw + 1);
        float p6 = noise(lu + 1, lv, lw + 1);
        float p7 = noise(lu , lv + 1, lw + 1);
        float p8 = noise(lu + 1, lv + 1, lw + 1);
        noise_ = lerp3d(p1,p2,p3,p4,p5,p6,p7,p8, fu, fv, fw) * amp.at(i);
        noise_val += fabs(noise_);

    }

    return lerp(black,white,noise_val);
}


}
