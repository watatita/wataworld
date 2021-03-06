
#include <irrlicht.h>
#include <fMathGenerator.h>
#include <fTextureCreator.h>
#include <fRandomGenDLA.h>
#include <fRandomGenWorley.h>
#include <fMapGen.h>

#include <fParamLSys.h>

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

    IImage* sky=driver->createImage(ECF_A8R8G8B8,dimension2d<u32>(128,128));
    IImage* water=driver->createImage(ECF_A8R8G8B8,dimension2d<u32>(128,128));
    IImage* sun=driver->createImage(ECF_A8R8G8B8,dimension2d<u32>(128,128));


    fMathGenerator mgen;
    fTextureCreator tkt(&mgen);
    tkt.createSkyTexture(sky);
    tkt.createWaterTexture(water);
    tkt.createSun(sun);

    ITexture* skytex=driver->addTexture("it's sky",sky);
    ITexture* watertex=driver->addTexture("it's water",water);
    ITexture* suntex=driver->addTexture("it's sun",sun);

    ISceneNode* celestialBody=smgr->addSkyDomeSceneNode(skytex);
    IAnimatedMesh* oceanmesh=smgr->addHillPlaneMesh("hilly",dimension2df(32,32),dimension2d<u32>(128,128)
                                                    ,0, 0,
                                                    core::dimension2d<f32>(0,0));
    ISceneNode* ocean=smgr->addWaterSurfaceSceneNode(oceanmesh,0.5,1024,2);
    ocean->setMaterialTexture(1,watertex);
    ocean->setMaterialTexture(0,watertex);
    ocean->setMaterialFlag(EMF_LIGHTING,false);
    ocean->setMaterialType(EMT_TRANSPARENT_REFLECTION_2_LAYER);

    ISceneNode* solar=smgr->addBillboardSceneNode(0,dimension2df(512,512));
    solar->setPosition(vector3df(100,100,100));
    solar->setMaterialTexture(0,suntex);
    solar->setMaterialFlag(EMF_LIGHTING,false);
    solar->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);

    ISceneNode* cam=smgr->addCameraSceneNodeFPS();
    smgr->setAmbientLight(SColorf(0.91,0.91,0.91,1));

    fMapGen mapg(driver);
    mapg.createWorldMap();
    IImage* worldLayout=mapg.getImage(LAYER_DLA);


//    IImage* worldLayout=driver->createImage(ECF_A8R8G8B8,dimension2d<u32>(4096,4096));
//    IImage* worldLayout=driver->createImage(ECF_R8G8B8,dimension2d<u32>(4096,4096));
//    for(u32 j=0;j<4096;j++)
//    {
//        for(u32 i=0;i<4096;i++)
//        {
//            u32 c=(u32) mapg.scaleImage(i,j,33);
//            if(c<40) c=0;
//            worldLayout->setPixel(i,j,SColor(0xff,c,c,c));
//        }
//    }
    driver->writeImageToFile(worldLayout,"map.png");

//    IImage* worleyImg=driver->createImage(ECF_A8R8G8B8,dimension2d<u32>(_MAP_SIZE_,_MAP_SIZE_));
//    IImage* dlaImg=driver->createImage(ECF_A8R8G8B8,dimension2d<u32>(_MAP_SIZE_,_MAP_SIZE_));
//    IImage* worldImg=driver->createImage(ECF_A8R8G8B8,dimension2d<u32>(_MAP_SIZE_,_MAP_SIZE_));


//    ITexture* worleyTxt=driver->addTexture("ww",mapg.getImage(LAYER_WORLEY));
//    ITexture* dlaTxt=driver->addTexture("dla",dlaImg);
//    ITexture* worldTxt=driver->addTexture("dla",mapg.getImage(LAYER_WORLD_MAP));

//    IAnimatedMesh* ground=smgr->addTerrainMesh(" ",mapg.getImage(LAYER_WORLD_MAP),mapg.getImage(LAYER_WORLD_MAP),dimension2df(32,32),512);
//    ISceneNode* terra=smgr->addAnimatedMeshSceneNode(ground);
//    terra->setMaterialFlag(EMF_LIGHTING,false);
//    terra->setPosition(vector3df(-2048,-64,-2048));
//
//
//    while(device->run())
//    {
//        driver->beginScene(true, true, SColor(0,200,200,200));
//
//        smgr->drawAll();
//        guienv->drawAll();
//        driver->draw2DImage(worleyTxt,position2di(0,480-128));
////        driver->draw2DImage(dlaTxt,position2di(128,480-128));
//        driver->draw2DImage(worldTxt,position2di(256,480-128));
//
//        driver->endScene();
//    }


    device->drop();

    return 0;
}

