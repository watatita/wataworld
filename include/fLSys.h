#ifndef FLSYS_H
#define FLSYS_H

#include <irrlicht.h>
#define _MAX_AXIOM_LENGHT_  0xffff

using namespace irr;

class fLSys
{
    public:
        fLSys();
        virtual ~fLSys();

        void lRegisterSymbol(char symbol,char next[64]);
        void lUnRegisterSymbol(char symbol);
        void lSetStart(char startSymbol[64]);
        void lGenerateLSystem(u32 countLoop);
        u32  lGetAxiomCount();
        char lGetAxiom(u32 index);

    protected:
    private:
        char lAxiomSuccessor[_MAX_AXIOM_LENGHT_];   //generated axiom
        char lAxiomPredecessor[_MAX_AXIOM_LENGHT_];
        char lReplace[27][64];
        bool lSymbolRegistered[27];
        u32 lAxSuccessorCount;

        s32 lCharToIndex(char symbol);
        void lAddAxiomSuccessor(char symbol);
        void lSwap_axiom();
        void lReset_axiom_successor();
        void lReset_axiom_predecessor();

};

#endif // FLSYS_H
