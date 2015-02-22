#ifndef FPARAMLSYS_H
#define FPARAMLSYS_H

#include <irrlicht.h>
#define _AXIOM_PARAM_ALLOC_  0xffff

using namespace irr;

class fParamLSys
{
    public:
        fParamLSys();
        virtual ~fParamLSys();
        void lSetStart(char startSymbol[64]);
        void lGenerateLSystem(u32 countLoop);
        void test();
    protected:
    private:

        unsigned char lAxiomPred[_AXIOM_PARAM_ALLOC_];
        unsigned char lAxiomSucc[_AXIOM_PARAM_ALLOC_];
        u32 axiomLenght;

        union VF32
        {
            float ii;
            unsigned char b[4];
        }var32;

};

#endif // FPARAMLSYS_H
