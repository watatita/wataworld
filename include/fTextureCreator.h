#ifndef FTEXTURECREATOR_H
#define FTEXTURECREATOR_H

#include <irrlicht.h>
#include <fMathGenerator.h>

using namespace irr;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace irr::io;
using namespace irr::gui;

SColor HSVtoRGB( float h, float s, float v );

class fTextureCreator
{
    public:
        fTextureCreator(fMathGenerator* t_mathgenerator);
        virtual ~fTextureCreator();
        void createSkyTexture(IImage* skyimage);
        void createWaterTexture(IImage* waterimage);
        void createSun(IImage* sunimage);
    protected:
    private:
        fMathGenerator* mgen;

        void gauss_process(s32 radius);
        void initGaussTable(s32 radius);
        void resetGauss();

        f32 getGaussTable(s32 x,s32 y);

        f32 gaussTable[64][64];
        f32 gaussSum;
        u32 gaussRadius;

        f32 gauss_srcs_vector[256][256];
        f32 gauss_proc_vector[256][256];
};

#endif // FTEXTURECREATOR_H
