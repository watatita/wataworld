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

    for(u32 i=0;i<30;i++)
    {
        lRegister[i].conditionRegisteredCount=0;
        lRegister[i].isRegistered=false;
        lRegister[i].paramCount=0;
        for(u32 j=0;j<16;j++)
        {
            for(u32 k=0;k<32;k++)
            {
                lRegister[i].symbolCondition[j][k]=0;
            }
            for(u32 k=0;k<128;k++)
            {
                lRegister[i].symbolSuccessor[j][k]=0;
            }
        }
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


void fParamLSys::lRegisterCondition(const char* startSymbol)
{
    s32 lenght=strlen(startSymbol);
    s32 n=0;
    s32 index=-1;

    if((startSymbol[n]>='A')&&(startSymbol[n]<='Z'))
    {
        index=lCharToIndex(startSymbol[n]);
    }
    if(index==-1)
    {
        printf("failed to register\n");
        return;
    }

    u32 condCount=lRegister[index].conditionRegisteredCount;
    while(true)
    {
        if((startSymbol[n]!='-')&&(startSymbol[n+1]!='>'))
        {
            break;
        }
        lRegister[index].symbolCondition[condCount][n]=startSymbol[n];
        n++;
    }
    n+=2;
    s32 nOffset=n;
    n=0;
    while(startSymbol[n+nOffset]!='\0')
    {
        lRegister[index].symbolSuccessor[condCount][n]=startSymbol[n+nOffset];
    }
    lRegister[index].isRegistered=true;
    lRegister[index].conditionRegisteredCount++;
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
void fParamLSys::lSetStart(const char* startSymbol)
{
    s32 lenght=strlen(startSymbol);
    for(u32 i=0;i<lenght;i++)
    {
        char lAxiomPred[i]=startSymbol[i];
    }
}

void fParamLSys::lProcessSymbol(char tSymbol,u32 paramcount,f32 x,f32 y, f32 z)
{
    s32 index=lCharToIndex(tSymbol);
    if(index==NULL)
    {
        printf("error conversion symbol\n");
        return;
    }
    u32 ii=0;

    while(lRegister[index].symbolCondition[ii][n]!=':')
    {

        switch(lRegister[index].symbolCondition[ii][n])
        {
            case '(':
        }
    }

}

bool fParamLSys::lCheckSyntax(const char* axiomString)
{
    s32  lenght=strlen(axiomString);
    s8   scopeTester=0;
    bool symbolWithScopeFlag=false;
    for(u32 i=0;i<lenght;i++)
    {

//        if((axiomString[i]>='A')&&(axiomString[i]<='Z'))
//        {
//            symbolWithScopeFlag=true;
//        }
//        if((axiomString[i]=='\\')||(axiomString[i]=='/') ||
//           (axiomString[i]=='+') ||(axiomString[i]=='-') ||
//           (axiomString[i]=='&') ||(axiomString[i]=='^') )
//        {
//            symbolWithScopeFlag=true;
//        }

//        if(symbolWithScopeFlag)
//        {
//            if(axiomString[i]=='(')
//            {
//                scopeTester++;
//                symbolWithScopeFlag=false;
//            }else
//            {
//                printf("error: symbol without scope!\n");
//                return false;
//            }
//        }
        if(axiomString[i]=='(')
        {
            scopeTester++;
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

s32 fParamLSys::lCharToIndex(char symbol)
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

