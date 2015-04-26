#ifndef FMAPGEN_H
#define FMAPGEN_H

#include <irrlicht.h>
#include <fMathGenerator.h>
#include <fRandomGenDLA.h>
#include <fRandomGenWorley.h>

#define LAYER_WORLEY        1
#define LAYER_DLA           2
#define LAYER_MOUNTAIN      3
#define LAYER_LAND          4
#define LAYER_OCEAN_MASK    5
#define LAYER_WORLD_MAP     6
#define LAYER_HUMIDITY      7
#define LAYER_TEMPERATE     8
#define LAYER_BIOME         9
#define LAYER_TERRITORY     10
#define LAYER_POISSON_1     11
#define LAYER_POISSON_2     12
#define LAYER_POISSON_3     13
#define LAYER_ZOOM_1        14

#define _MAP_SIZE_  128
using namespace irr;
using namespace irr::core;
using namespace irr::video;
using namespace irr::scene;
using namespace irr::io;
using namespace irr::gui;

class fMapGen
{
    public:
        fMapGen();
        virtual ~fMapGen();
    //color conversion
        void createWorldMap(fMathGenerator* fmg,
                            fRandomGenDLA*  dla,
                            fRandomGenWorley* worley);
        u32 getMap(u32 x,u32 y,u32 layer);
        u32 getMap(IImage* img,u32 layer);

    protected:
    private:
        fMathGenerator* fmg;
        fRandomGenDLA*  dla;
        fRandomGenWorley* worley;

        u8 TextureLayer[16][_MAP_SIZE_][_MAP_SIZE_];
};

#endif // FMAPGEN_H
