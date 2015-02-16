#include "fMapGen.h"

using namespace irr;
using namespace irr::core;
using namespace irr::video;
using namespace irr::scene;
using namespace irr::io;
using namespace irr::gui;

fMapGen::fMapGen()
{
    //ctor
}

fMapGen::~fMapGen()
{
    //dtor
}

void fMapGen::createWorldMap(fMathGenerator* fmg,
                             fRandomGenDLA*  dla,
                             fRandomGenWorley* worley)
{
    worley->worleyInitWorleyLayer();
    dla->dlaCreateDLA(64,64,50);

    for(u32 j=0;j<128;j++)
    {
        for(u32 i=0;i<128;i++)
        {
            TextureLayer[LAYER_DLA][i][j]=dla->getImage(i,j)*0xff;
        }
    }

    for(u32 j=0;j<128;j++)
    {
        for(u32 i=0;i<128;i++)
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
        }
    }
}

u32 fMapGen::getMap(u32 x,u32 y,u32 layer)
{

}

u32 fMapGen::getMap(IImage* img,u32 layer)
{
    for(u32 j=0;j<128;j++)
    {
        for(u32 i=0;i<128;i++)
        {
            s32 c=(u32) TextureLayer[layer][i][j];
            img->setPixel(i,j,SColor(0xff,c,c,c));
        }
    }
}
