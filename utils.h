#ifndef __MAP_H__
#define __MAP_H__

namespace Map
{
    void ShowImageLayer(tmx_map*,tmx_layer*,SDL_Renderer*,int,int);
}


namespace Physics{
    void SetPhysicBody(b2World&,float,float,float,float);
    int MeterToPixel(float);
    float PixelToMeter(int);
    b2Body* CreateDynamicBody(b2World&,float,float,float,float);
}
#endif