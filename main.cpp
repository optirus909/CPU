#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <zconf.h>
#include "lib/stack.h"
#include "lib/stack_debug.h"

//-----------------------------------------------------------------------------------------------------
/**
 * TODO jmp, call
 */
//-----------------------------------------------------------------------------------------------------

typedef long num_t;

//-----------------------------------------------------------------------------------------------------

#define CMD_DEF(name, code)\
    CMD_##name,

enum CMD_NUM
{
    #include "commands/commands.h"
    CMD_DEF(MAX,)
};
#undef CMD_DEF

#define REG_DEF(name)\
    REG_##name,

enum REG_NUM
{
    #include "commands/reg_codes.h"
    REG_DEF(MAX)
};
#undef REG_DEF

//-----------------------------------------------------------------------------------------------------

#define FOPEN_ERR -1
#define RAM_SIZE 3
#define STK_START_SIZE 10

//-----------------------------------------------------------------------------------------------------

struct cpu_t
{
    char * code;
    elem_t reg[REG_MAX];
    Stack stk;
    elem_t RAM[RAM_SIZE];
    long RPC;
};

//-----------------------------------------------------------------------------------------------------

char * text_reading(FILE *file, long * FileSize);
int cpu_exec(cpu_t *pCPU, char * code);
int cpu_load(cpu_t *pCPU);
int cpu_dtor(cpu_t *pCPU);
int cpu_dump(cpu_t *pCPU);
//-----------------------------------------------------------------------------------------------------

int main()
{
    FILE *fin;

    if((fin = fopen("/Users/andreyandriyaynen/CLionProjects/assembler/cmake-build-debug/output.txt", "r")) == nullptr)
        return FOPEN_ERR;
    long  filesize;
    char * arr = text_reading(fin, &filesize);
    fclose(fin);

    cpu_t theCPU;
    cpu_exec( &theCPU, arr );

    theCPU.code = arr;

    cpu_load( &theCPU );

    cpu_dtor( &theCPU );

    return 0;
}

//-----------------------------------------------------------------------------------------------------

int cpu_exec(cpu_t *pCPU, char * code)
{
    StackCtor(&pCPU->stk, STK_START_SIZE);
    pCPU->RPC = 0;
    pCPU->code = code;
    for (int i = 0; i < REG_MAX; ++i)
        pCPU->reg[i] = NAN;
    for (int i = 0; i < RAM_SIZE; ++i)
        pCPU->RAM[i] = NAN;
    return 0;
}

//-----------------------------------------------------------------------------------------------------

int cpu_dtor(cpu_t *pCPU)
{
    StackDtor(&pCPU->stk);
    for (int i = 0; i < REG_MAX; ++i)
        pCPU->reg[i] = NAN;
    for (int i = 0; i < RAM_SIZE; ++i)
        pCPU->RAM[i] = NAN;
    free(pCPU->code);
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

int cpu_load(cpu_t *pCPU)
{
    pCPU->RPC = 0;
    while (pCPU->code[pCPU->RPC] != CMD_END)
    {
        #define CMD_DEF(name, code)                                     \
            case CMD_##name:                                            \
            {                                                           \
                code;                                                   \
                break;                                                  \
            }

        #define JUMP(name, op)                                          \
            {                                                           \
                elem_t a = 0;                                           \
                elem_t b = 0;                                           \
                StackPop(&pCPU->stk, &a);                               \
                StackPop(&pCPU->stk, &b);                               \
                printf(# name ": data: a = %lg, b = %lg\n", a, b);      \
                if (a op b)                                             \
                {                                                       \
                    char * num = &pCPU->code[pCPU->RPC + 1];            \
                    char * end;                                         \
                    long val = strtol(num, &end, 10);                   \
                    printf("new pc = %ld\n", val);                      \
                    pCPU->RPC = val - 1;                                \
                }                                                       \
            }

        switch (pCPU->code[pCPU->RPC])
        {
            #include "commands/commands.h"
        }

        #undef JUMP
        #undef CMD_DEF

        sleep(1);

        pCPU->RPC++;

    }
}

//-----------------------------------------------------------------------------------------------------

int cpu_dump(cpu_t *pCPU)
{
    printf( "\n# CPU [%p] (OK)\n", pCPU );
    printf("# REG count = %d\n", REG_MAX);
    printf("# RPC = %lx\n", pCPU->RPC);
    printf("# REG[%d][%p]\n", REG_MAX, pCPU->reg);
    printf("#      {\n");
    for (int j = 0; j < REG_MAX; ++j)
        printf("#        reg[%d] = %lg\n", j, pCPU->reg[j]);
    printf("#      }\n");
    printf( "# RAM size = %d\n", RAM_SIZE);
    printf("# RAM[%d][%p]\n#      {\n", RAM_SIZE, pCPU->RAM);

    for ( int i = 0; i < RAM_SIZE; i++ )
        printf( "#        [%d]: %lg\n", i, pCPU->RAM[i] );

    printf( "#      }\n"
                    "# }\n\n" );
}