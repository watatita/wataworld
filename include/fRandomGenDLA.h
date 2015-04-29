#ifndef FRANDOMGENDLA_H
#define FRANDOMGENDLA_H

#include <irrlicht.h>
#define _IMAGE_DLA_SIZE_    128

using namespace irr;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace irr::io;
using namespace irr::gui;

class fRandomGenDLA
{
    public:
        fRandomGenDLA();
        virtual ~fRandomGenDLA();
        //DLA function
        bool dlaHasNeighbour(vector2df test_point);
        void dlaResetDLA();
        void dlaCreateDLA(u32 x,u32 y,f32 radius);
        bool dlaIsOutOfPosition(vector2df test_point,vector2df center,f32 radius);
        void setPixel(int x, int y);
        void plotLine(int x0, int y0, int x1, int y1);

        void dlaCreateMountain();

        f32 getImage(u32 x,u32 y);


    protected:
    private:

        f32 img_dla[_IMAGE_DLA_SIZE_][_IMAGE_DLA_SIZE_];

        void gauss_process(s32 radius);
        void initGaussTable(s32 radius);
        void resetGauss();

        f32 getGaussTable(s32 x,s32 y);

        f32 gaussTable[64][64];
        f32 gaussSum;
        u32 gaussRadius;

        f32 gauss_srcs_vector[256][256];
        f32 gauss_proc_vector[256][256];

        array<vector2df> diffuse_point;


};

#endif // FRANDOMGENDLA_H
