#include "fTreeGenSys.h"
using namespace irr;

using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace irr::io;
using namespace irr::gui;

fTreeGenSys::fTreeGenSys()
{
    //ctor
}

fTreeGenSys::~fTreeGenSys()
{
    //dtor
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void fTreeGenSys::lRegisterSymbol(char symbol,char next[64])
{
    s32 index=lCharToIndex(symbol);
    //quit if symbol is invalid
    if(index==NULL)
    {
        return;
    }

    for(u32 i=0;i<64;i++)
    {
        lReplace[index][i]=0;
    }
    for(u32 i=0;i<strlen(next);i++)
    {
        lReplace[index][i]=next[i];
    }
    lSymbolRegistered[index]=true;
}

void fTreeGenSys::lUnRegisterSymbol(char symbol)
{
    s32 index=lCharToIndex(symbol);
    if(index==NULL)
    {
        return;
    }
    for(u32 i=0;i<64;i++)
    {
        lReplace[index][i]=0;
    }
    lSymbolRegistered[index]=false;
}

void fTreeGenSys::lSetStart(char startSymbol[64])
{
    for(u32 i=0;i<strlen(startSymbol);i++)
    {
        lAxiomPredecessor[i]=startSymbol[i];
    }
}

void fTreeGenSys::lSetAngle(f32 degree)
{
    lAngleIncrement=degree;
}

void fTreeGenSys::lGenerateLSystem(u32 countLoop)
{
    for(u32 nloop=0;nloop<countLoop;nloop++)
    {
        u32 n=0;
        while(lAxiomPredecessor[n]!=0)
        {
            s32 index=lCharToIndex(lAxiomPredecessor[n]);
            if(index!=NULL) //is symbol is valid
            {
                if(lSymbolRegistered[index])    //is registered?
                {
                    u32 m=0;
                    while(lReplace[index][m]!=0)
                    {
                        lAddAxiomSuccessor(lReplace[index][m]);
                        m++;
                    }
                }
            }
            else
            {
                lAddAxiomSuccessor(lAxiomPredecessor[n]);
            }
            n++;
        }
        lSwap_axiom();
        lReset_axiom_successor();
    }
}

/**
    private
*/

s32 fTreeGenSys::lCharToIndex(char symbol)
{
    switch(symbol)
    {
    case 'A': return 1;break;
    case 'B': return 2;break;
    case 'C': return 3;break;
    case 'D': return 4;break;
    case 'E': return 5;break;
    case 'F': return 6;break;
    case 'G': return 7;break;
    case 'H': return 8;break;
    case 'I': return 9;break;
    case 'J': return 10;break;
    case 'K': return 11;break;
    case 'L': return 12;break;
    case 'M': return 13;break;
    case 'N': return 14;break;
    case 'O': return 15;break;
    case 'P': return 16;break;
    case 'Q': return 17;break;
    case 'R': return 18;break;
    case 'S': return 19;break;
    case 'T': return 20;break;
    case 'U': return 21;break;
    case 'V': return 22;break;
    case 'W': return 23;break;
    case 'X': return 24;break;
    case 'Y': return 25;break;
    case 'Z': return 26;break;
//    case '[',']','+','-','&','^','\\','/': return NULL;break;
    default: return NULL;break;//invalid symbol
    }
}


void fTreeGenSys::lAddAxiomSuccessor(char symbol)
{
    lAxiomSuccessor[lAxSuccessorCount]=symbol;
    lAxSuccessorCount++;
}

void fTreeGenSys::lSwap_axiom()
{
    for(u32 i=0;i<_MAX_AXIOM_LENGHT_;i++)
    {
        lAxiomPredecessor[i]=0;
    }
    for(u32 i=0;i<lAxSuccessorCount;i++)
    {
        lAxiomPredecessor[i]=lAxiomSuccessor[i];
    }
}

void fTreeGenSys::lReset_axiom_successor()
{
    lAxSuccessorCount=0;
}

void fTreeGenSys::lReset_axiom_predecessor()
{
    for(u32 i=0;i<_MAX_AXIOM_LENGHT_;i++)
    {
        lAxiomPredecessor[i]=0;
    }
}



