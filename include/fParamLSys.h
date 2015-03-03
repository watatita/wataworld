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

        bool check_condition(f32 val_1,char logic_op,f32 val_2);

        struct param_l_condition
        {
            char logic_op;
            f32  comp_value_1;
            f32  comp_value_2;
        };
        struct ssymbol
        {
            u32  conditionRegisteredCount;
            bool isRegistered;
            u8   symbolSuccessor[16][255];
            s32  param
        }lRegister[60];


        union VF32
        {
            float ii;
            unsigned char b[4];
        }var32;

};

#endif // FPARAMLSYS_H
