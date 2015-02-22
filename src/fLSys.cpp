#include "fLSys.h"

fLSys::fLSys()
{
    //ctor
    lAxSuccessorCount=0;
}

fLSys::~fLSys()
{
    //dtor
}


/** @brief (one liner)
  *
  * (documentation goes here)
  */
void fLSys::lRegisterSymbol(char symbol,char next[64])
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

void fLSys::lUnRegisterSymbol(char symbol)
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

void fLSys::lSetStart(char startSymbol[64])
{
    for(u32 i=0;i<strlen(startSymbol);i++)
    {
        lAxiomPredecessor[i]=startSymbol[i];
    }
}


void fLSys::lGenerateLSystem(u32 countLoop)
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
u32  fLSys::lGetAxiomCount()
{
    return strlen(lAxiomPredecessor);
}

char fLSys::lGetAxiom(u32 index)
{
    return lAxiomPredecessor[index];
}

/**
    private
*/

s32 fLSys::lCharToIndex(char symbol)
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


void fLSys::lAddAxiomSuccessor(char symbol)
{
//    printf("%c",symbol);
    lAxiomSuccessor[lAxSuccessorCount]=symbol;
    lAxSuccessorCount++;
}

void fLSys::lSwap_axiom()
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

void fLSys::lReset_axiom_successor()
{
    lAxSuccessorCount=0;
}

void fLSys::lReset_axiom_predecessor()
{
    for(u32 i=0;i<_MAX_AXIOM_LENGHT_;i++)
    {
        lAxiomPredecessor[i]=0;
    }
}
