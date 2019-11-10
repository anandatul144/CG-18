#include "interpolate.h"
#include "assert.h"

namespace rt {

    template <typename T>
    T lerp(const T& px0, const T& px1, float xPoint)
    {
        return (px0*xPoint + (1-xPoint)*px1);

    }

    template <typename T>
    T lerpbar(const T& a, const T& b, const T& c, float aWeight, float bWeight)
    {
        return (a*aWeight + b*bWeight +c*(1-aWeight-bWeight));
    }

    template <typename T>
    T lerp2d(const T& px0y0, const T& px1y0, const T& px0y1, const T& px1y1, float xWeight, float yWeight)
    {
        T pxy0= xWeight*px0y0 +(1-xWeight)*px1y0;
        T pxy1= xWeight*px0y1 +(1-xWeight)*px1y1;

        T pxyx= yWeight*pxy0 + (1-yWeight)*pxy1;
        return pxyx;
    }

    template <typename T>
    T lerp3d(const T& px0y0z0, const T& px1y0z0, const T& px0y1z0, const T& px1y1z0,
        const T& px0y0z1, const T& px1y0z1, const T& px0y1z1, const T& px1y1z1,
        float xPoint, float yPoint, float zPoint) {
        T y0z0 = lerp(px0y0z0, px1y0z0, xPoint);
        T y0z1 = lerp(px0y0z1, px1y0z1, xPoint);
        T y1z0 = lerp(px0y1z0, px1y1z0, xPoint);
        T y1z1 = lerp(px0y1z1, px1y1z1, xPoint);

        T ans= lerp2d(y0z0, y1z0, y0z1, y1z1, yPoint, zPoint);

        return ans;
    }

}

