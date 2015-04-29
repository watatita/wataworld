#include "fMapGen.h"

using namespace irr;
using namespace irr::core;
using namespace irr::video;
using namespace irr::scene;
using namespace irr::io;
using namespace irr::gui;

fMapGen::fMapGen()
{

}

fMapGen::fMapGen(IVideoDriver* driver)
{
    //ctor
    fmg     =new fMathGenerator();
    dla     =new fRandomGenDLA();
    worley  =new fRandomGenWorley();

    for(u32 i=0;i<16;i++)
    {
        MapGenImage[i]=driver->createImage(ECF_A8R8G8B8,dimension2d<u32>(_MAP_SIZE_,_MAP_SIZE_));
    }
}

fMapGen::~fMapGen()
{
    //dtor

}

void fMapGen::createWorldMap()
{
    dla->dlaCreateMountain();
    for(u32 j=0;j<_MAP_SIZE_;j++)
    {
        for(u32 i=0;i<_MAP_SIZE_;i++)
        {
            s32 c=dla->getImage(i,j)*0xff;
            if(c>0xff) c=0xff;
            MapGenImage[LAYER_DLA]->setPixel(i,j,SColor(0xff,c,c,c));
        }
    }

    /*
    worley->worleyInitWorleyLayer();

    for(u32 j=0;j<_MAP_SIZE_;j++)
    {
        for(u32 i=0;i<_MAP_SIZE_;i++)
        {
            TextureLayer[LAYER_DLA][i][j]=dla->getImage(i,j)*0xff;
        }
    }

    for(u32 j=0;j<_MAP_SIZE_;j++)
    {
        for(u32 i=0;i<_MAP_SIZE_;i++)
        {
            f32 w=worley->worleyGetValue(i,j);
            s32 c=(u32) 0x80*w*fmg->GradientFrame(i,j)*
                         (fmg->PerlinNoise(i,j,16)+
                          fmg->PerlinNoise(i,j,8)/2+
                          fmg->PerlinNoise(i,j,4)/4+
                          fmg->PerlinNoise(i,j,2)/8+0.875);
            if(c<0) c=0;
            if(c>0xff) c=0xff;
            TextureLayer[LAYER_WORLD_MAP][i][j]=c;
            TextureLayer[LAYER_WORLEY][i][j]=w*0xff;
            s32 wc=w*0xff;
            if(c<40){ c=0;}else{c=40;}
            MapGenImage[LAYER_WORLD_MAP]->setPixel(i,j,SColor(0xff,c,c,c));
            MapGenImage[LAYER_WORLEY]->setPixel(i,j,SColor(0xff,wc,wc,wc));
        }
    }*/
}

IImage* fMapGen::getImage(u32 layer)
{
    return MapGenImage[layer];
}

u32 fMapGen::getMap(u32 x,u32 y,u32 layer)
{

}

u32 fMapGen::getMap(IImage* img,u32 layer)
{
    for(u32 j=0;j<_MAP_SIZE_;j++)
    {
        for(u32 i=0;i<_MAP_SIZE_;i++)
        {
            s32 c=(u32) TextureLayer[layer][i][j];
            img->setPixel(i,j,SColor(0xff,c,c,c));
        }
    }
}

f32 fMapGen::scaleImage(f32 x, f32 y,f32 scale)
{

    f32 cx=x/scale;
    f32 cy=y/scale;

    s32 ix=(s32)cx;
    s32 iy=(s32)cy;
    s32 ix2=ix+1;
    s32 iy2=iy+1;
    f32 frac_x=cx-ix;
    f32 frac_y=cy-iy;

    f32 u0=TextureLayer[LAYER_WORLD_MAP] [ix] [iy];
    f32 u1=TextureLayer[LAYER_WORLD_MAP][ix2] [iy];
    f32 u2=TextureLayer[LAYER_WORLD_MAP] [ix][iy2];
    f32 u3=TextureLayer[LAYER_WORLD_MAP][ix2][iy2];

    f32 Sx   = 3*(frac_x*frac_x) - 2*(frac_x*frac_x*frac_x);
    f32 u0_1 = u0 + Sx*(u1-u0);
    f32 u2_3 = u2 + Sx*(u3-u2);

    f32 Sy     = 3*(frac_y*frac_y) - 2*(frac_y*frac_y*frac_y);
    f32 u01_23 = u0_1 + Sy*(u2_3-u0_1);

    return u01_23;
}
