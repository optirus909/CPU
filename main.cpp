#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include "lib/stack.h"
#include "lib/stack_debug.h"

//-----------------------------------------------------------------------------------------------------

#define CMD_DEF(name, code)\
    CMD_##name,

enum CMD_NUM
{
#include "../CPU/commands/commands.h"
    CMD_DEF(MAX,)
};
#undef CMD_DEF

#define REG_DEF(name)\
    REG_##name,

enum REG_NUM
{
#include "../CPU/commands/reg_codes.h"
    REG_DEF(MAX)
};
#undef REG_DEF

//-----------------------------------------------------------------------------------------------------

struct cpu_t
{
    elem_t reg[REG_MAX];
    Stack stk;
    int RPC;
};

//-----------------------------------------------------------------------------------------------------

int cpu_load(cpu_t *pCPU, char * pcode);
int cpu_exec(cpu_t *pCPU);
int cpu_dtor(cpu_t *pCPU);

//-----------------------------------------------------------------------------------------------------

int main()
{
    cpu_t theCPU;
    cpu_exec( &theCPU );

    for (int i = 0; i < REG_MAX; ++i)
        printf("%lg\n", theCPU.reg[i]);

    cpu_dtor( &theCPU );

    return 0;
}

//-----------------------------------------------------------------------------------------------------

int cpu_exec(cpu_t *pCPU)
{
    StackCtor(&pCPU->stk, 10);
    pCPU->RPC = 0;
    for (int i = 0; i < REG_MAX; ++i)
        pCPU->reg[i] = 0;
    return 0;
}

//-----------------------------------------------------------------------------------------------------

int cpu_dtor(cpu_t *pCPU)
{
    StackDtor(&pCPU->stk);
    for (int i = 0; i < REG_MAX; ++i)
        pCPU->reg[i] = 0;
    return 0;
}

//-----------------------------------------------------------------------------------------------------

char * text_reading(FILE *file, long * FileSize)
{
    fseek(file, 0, SEEK_END);
    *FileSize = ftell(file);
    rewind(file);
    char * buffer = (char *) calloc(*FileSize, sizeof(char));
    fread(buffer, sizeof(char *), *FileSize, file);

    return buffer;
}