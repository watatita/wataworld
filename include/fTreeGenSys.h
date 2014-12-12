#ifndef FTREEGENSYS_H
#define FTREEGENSYS_H


class fTreeGenSys
{
    public:
        fTreeGenSys();
        virtual ~fTreeGenSys();
    protected:
    private:
};

#endif // FTREEGENSYS_H


/*
====================================================
                L-SYSTEM TEST
====================================================


#include <irrlicht.h>

using namespace irr;

using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace irr::io;
using namespace irr::gui;


array<char> l_sys;
array<char> l_gen;
array<position2di> lstack;
array<f32> lstkangle;
array<f32> bRatioStack;
array<position2di> ln;
array<position2di> ln2;
position2di activepos;

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

    const char* ltran="F[-X]F[+X]FX ";
    l_sys.push_back('X');

    u8 plantVariant;
    rand();//rand();
    for(u32 tloop=0;tloop<4;tloop++)
    {
        for(u32 i=0;i<l_sys.size();i++)
        {
            switch(l_sys[i])
            {
                case 'X':
                    for(u32 j=0;j<16;j++)
                    {
                        if(ltran[j]==' ') break;
                        l_gen.push_back(ltran[j]);
                    }
                    break;
                case 'F':
                    plantVariant=rand()%3;
                    switch(plantVariant)
                    {
                    case 0:
                        l_gen.push_back('F');
                        l_gen.push_back('F');
                        break;
                    case 1:
                        l_gen.push_back('F');
                        l_gen.push_back('[');
                        l_gen.push_back('F');
                        l_gen.push_back(']');
                        break;
                    case 2:
                        l_gen.push_back('F');
                        l_gen.push_back('[');
                        l_gen.push_back('-');
                        l_gen.push_back('F');
                        l_gen.push_back(']');
                        break;
                    };

                    break;
                default:
                    l_gen.push_back(l_sys[i]);
                    break;
            }
        };
        l_sys.swap(l_gen);
        l_gen.clear();
    }

    for(u32 i=0;i<l_sys.size();i++)
    {
        printf("%c",l_sys[i]);
    }
    printf("\n");

    activepos.X=128;
    activepos.Y=256;
    f32 angle=0;
    f32 activeratio=1;
    for(u32 i=0;i<l_sys.size();i++)
    {
        switch(l_sys[i])
        {
        case '-':
            angle+=30*3.14*0.0055;
            break;
        case '+':
            angle-=30*3.14*0.0055;
            break;
        case '[':
            lstack.push_back(activepos);
            lstkangle.push_back(angle);
//            bRatioStack.push_back(activeratio);
//            activeratio=activeratio*0.8;
            break;
        case ']':
            activepos.X=lstack[lstack.size()-1].X;
            activepos.Y=lstack[lstack.size()-1].Y;
            angle=lstkangle[lstkangle.size()-1];
//            activeratio=bRatioStack[bRatioStack.size()-1];
            lstack.erase(lstack.size()-1);
            lstkangle.erase(lstkangle.size()-1);
//            bRatioStack.erase(bRatioStack.size()-1);
            break;
        case 'X':

            break;
        case 'F':
            ln.push_back(activepos);
            f32 xn=cos(angle)*5;
            f32 yn=sin(angle)*5;
            activepos.X+=xn;
            activepos.Y+=yn;
            ln2.push_back(activepos);
            break;
        }
    }
//    printf("\n%d",l_sys.size());
    while(device->run())
    {

        driver->beginScene(true, true, SColor(0,200,200,200));

        smgr->drawAll();
        guienv->drawAll();
        for(u32 i=0;i<ln.size();i++)
        {
            driver->draw2DLine(ln[i],ln2[i],SColor(0xff,0xff,0xff,0xff));
        }

        driver->endScene();
    }

    device->drop();

    return 0;
}

*/
