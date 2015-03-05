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
        void lRegisterCondition(char startSymbol[64]);
        void lGenerateLSystem(u32 countLoop);
        void test();
    protected:
    private:

        unsigned char lAxiomPred[_AXIOM_PARAM_ALLOC_];
        unsigned char lAxiomSucc[_AXIOM_PARAM_ALLOC_];
        u32  axiomLenght;
        f32 temp_parameter_register[32];

        void process_Symbol_F(u32 paramcount,f32 x,f32 y, f32 z);
        s32 lCharToIndex(char symbol);

        struct ssymbol
        {
            u32  conditionRegisteredCount;
            bool isRegistered;
            char symbolCondition[16][32];
            char symbolSuccessor[16][255];
            s32  param[16];
            s32  paramCount;
        }lRegister[60];


        union VF32
        {
            float ii;
            unsigned char b[4];
        }var32;

};

#endif // FPARAMLSYS_H
