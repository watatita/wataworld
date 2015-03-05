#include "fParamLSys.h"

fParamLSys::fParamLSys()
{
    //ctor
    axiomLenght=0;
    char nn[]={'F',2, 0x41,0xa0,0,0,  0x41,0x70,0,0};
    axiomLenght=10;
    for(u32 i=0;i<axiomLenght;i++)
    {
        lAxiomPred[i]=nn[i];
    }
}

fParamLSys::~fParamLSys()
{
    //dtor
}
/** @brief (one liner)
  *
  * (documentation goes here)
  */
void fParamLSys::test()
{
    u32 n=0;
    while(n<axiomLenght)
    {
        switch(lAxiomPred[n])
        {
        case '[':
            printf("[");n++;break;
        case ']':
            printf("]");n++;break;
        case 'F':
            char symbol=lAxiomPred[n];
            n++;
            printf("%c",symbol);
            unsigned int t_paramcount=lAxiomPred[n];
            n++;
            printf("(%d)",t_paramcount);
            printf("(");
            for(u32 i=0;i<t_paramcount;i++)
            {
                var32.b[3]=lAxiomPred[n];n++;
                var32.b[2]=lAxiomPred[n];n++;
                var32.b[1]=lAxiomPred[n];n++;
                var32.b[0]=lAxiomPred[n];n++;
                printf("%f,",var32.ii);
            }
            printf(")");
            break;
        }
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void fParamLSys::lGenerateLSystem(u32 countLoop)
{

}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void fParamLSys::lSetStart(char startSymbol[64])
{

}

void fParamLSys::process_Symbol_F(u32 paramcount,f32 x,f32 y, f32 z)
{
    lRegister[0].
}

