
#include <irrlicht.h>

using namespace irr;

using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace irr::io;
using namespace irr::gui;

int main(int argc, char** argv)
{

    IrrlichtDevice *device =
        createDevice(EDT_OPENGL, dimension2d<u32>(640, 480), 16,
            false, false, false, 0);

    device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");


    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();


    guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
        rect<int>(10,10,200,22), true);


    smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

    while(device->run())
    {
        driver->beginScene(true, true, SColor(0,200,200,200));

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }


    device->drop();

    return 0;
}

