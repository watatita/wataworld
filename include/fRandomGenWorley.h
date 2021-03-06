#ifndef FRANDOMGENWORLEY_H
#define FRANDOMGENWORLEY_H

#include <irrlicht.h>
#define _IMG_WORLEY_SIZE_ 128

using namespace irr;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace irr::io;
using namespace irr::gui;

class fRandomGenWorley
{
    public:
        fRandomGenWorley();
        virtual ~fRandomGenWorley();
        //Worley function
        void worleyInitWorleyLayer();
        f32  worleyGetValue(u32 x,u32 y);
        f32  worleyGetDistance(f32 x,f32 y);
    protected:
    private:
        array<vector2df> worley_point;
        f32 img_worley[_IMG_WORLEY_SIZE_][_IMG_WORLEY_SIZE_];
};

#endif // FRANDOMGENWORLEY_H
