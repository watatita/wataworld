#ifndef FMAPGEN_H
#define FMAPGEN_H

#include <irrlicht.h>

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

    protected:
    private:

        u8 TextureLayer[16][128][128];
};

#endif // FMAPGEN_H
