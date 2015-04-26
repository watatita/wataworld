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
    worley->worleyInitWorleyLayer();
    dla->dlaCreateDLA(64,64,50);

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
                          fmg->PerlinNoise(i,j,4)/4+0.875);
            if(c<0) c=0;
            if(c>0xff) c=0xff;
            TextureLayer[LAYER_WORLD_MAP][i][j]=c;
            TextureLayer[LAYER_WORLEY][i][j]=w*0xff;
            s32 wc=w*0xff;
            if(c<40){ c=0;}else{c=40;}
            MapGenImage[LAYER_WORLD_MAP]->setPixel(i,j,SColor(0xff,c,c,c));
            MapGenImage[LAYER_WORLEY]->setPixel(i,j,SColor(0xff,wc,wc,wc));
        }
    }
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
