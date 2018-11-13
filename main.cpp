#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
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

#define FOPEN_ERR -1

//-----------------------------------------------------------------------------------------------------

struct cpu_t
{
    elem_t reg[REG_MAX];
    Stack stk;
    elem_t RAM[20];
    int RPC;
};

//-----------------------------------------------------------------------------------------------------

char * text_reading(FILE *file, long * FileSize);
int cpu_load(cpu_t *pCPU, char * pcode);
int cpu_exec(cpu_t *pCPU);
int cpu_dtor(cpu_t *pCPU);

//-----------------------------------------------------------------------------------------------------

int main()
{
    cpu_t theCPU;
    cpu_exec( &theCPU );

    FILE *fin;

    if((fin = fopen("/Users/andreyandriyaynen/CLionProjects/assembler/cmake-build-debug/output.txt", "r")) == nullptr)
        return FOPEN_ERR;


    long  filesize;
    char * arr = text_reading(fin, &filesize);
    fclose(fin);

    char *code = arr;

    cpu_load( &theCPU, code );

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
    for (int i = 0; i < 20; ++i)
        pCPU->RAM[i] = 0;
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

//-----------------------------------------------------------------------------------------------------

int cpu_load(cpu_t *pCPU, char * pcode)
{
    pCPU->RPC = 0;
    while (pcode[pCPU->RPC] != CMD_END)
    {
        #define CMD_DEF(name, code)     \
            case CMD_##name:            \
            {                           \
                code;                   \
                break;                  \
            }


        switch (pcode[pCPU->RPC])
        {
            #include "commands/commands.h"
        }

        #undef CMD_DEF

        pCPU->RPC++;

        StackDump(&pCPU->stk);
    }
}