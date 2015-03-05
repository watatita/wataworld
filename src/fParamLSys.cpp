#include "fParamLSys.h"

fParamLSys::fParamLSys()
{
    //ctor

    for(u32 i=0;i<_AXIOM_PARAM_ALLOC_;i++)
    {
        lAxiomPred[i]='\0';
        lAxiomSucc[i]='\0';
    }
    axiomLenght=0;
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

void lSetStart(const char* startSymbol)
{
    s32 lenght=strlen(startSymbol);
    for(u32 i=0;i<lenght;i++)
    {
        char lAxiomPred[i]=startSymbol[i];
    }
}

void lRegisterCondition(const char* startSymbol)
{

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

bool fParamLSys::lCheckSyntax(const char* axiomString)
{
    s32  lenght=strlen(axiomString);
    s8   scopeTester=0;
    bool symbolWithScopeFlag=false;
    for(u32 i=0;i<lenght;i++)
    {
        if(axiomString[i]==' ')
        {
            printf("error: <SPACE> is forbidden!\n");
            return false;
        }

        if((axiomString[i]>='A')&&(axiomString[i]<='Z'))
        {
            symbolWithScopeFlag=true;
        }
        if((axiomString[i]=='\\')||
           (axiomString[i]=='/') ||
           (axiomString[i]=='+') ||
           (axiomString[i]=='-') ||
           (axiomString[i]=='&') ||
           (axiomString[i]=='^') )
        {
            symbolWithScopeFlag=true;
        }

        if(symbolWithScopeFlag)
        {
            if(axiomString[i]=='(')
            {
                scopeTester++;
                symbolWithScopeFlag=false;
            }else
            {
                printf("error: symbol without scope!\n");
                return false;
            }
        }

        if(axiomString[i]==')')
        {
            scopeTester--;
        }
    }

    if(symbolWithScopeFlag)
    {
        printf("error: symbol without scope!\n");
        return false;
    }
    if(scopeTester!=0)
    {
        printf("error: scope unmatched!\n");
        return false;
    }

    return true;
}

