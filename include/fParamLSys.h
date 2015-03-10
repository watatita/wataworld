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
        void lSetStart(const char* startSymbol);
        void lRegisterCondition(const char* startSymbol);
        void lGenerateLSystem(u32 countLoop);
        bool lCheckSyntax(const char* axiomString);
        void test();
    protected:
    private:

        char lAxiomPred[_AXIOM_PARAM_ALLOC_];
        char lAxiomSucc[_AXIOM_PARAM_ALLOC_];
        u32  axiomLenght;
        f32 temp_parameter_register[32];

        void lProcessSymbol(char tSymbol,u32 paramcount,f32 x,f32 y, f32 z);
        s32  lCharToIndex(char symbol);

        struct ssymbol
        {
            u32  conditionRegisteredCount;
            bool isRegistered;
            char symbolCondition[16][32];
            char symbolSuccessor[16][128];
            f32  param[4];
            u32  paramCount;
        }lRegister[30];


        union VF32
        {
            float ii;
            unsigned char b[4];
        }var32;

};

#endif // FPARAMLSYS_H
