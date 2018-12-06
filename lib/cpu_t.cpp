//
// Created by Andrey Andriyaynen on 06/12/2018.
//


#include "cpu_t.h"

//-----------------------------------------------------------------------------------------------------

int cpu_exec(cpu_t *pCPU, char * code)
{
    StackCtor(&pCPU->stk, STK_START_SIZE);
    StackCtor(&pCPU->retstk, STK_START_SIZE);
    pCPU->RPC = 0;
    pCPU->code = code;
    for (int i = 0; i < REG_MAX; ++i)
        pCPU->reg[i] = -1;
    for (int i = 0; i < RAM_SIZE; ++i)
        pCPU->RAM[i] = -1;
    return 0;
}

//-----------------------------------------------------------------------------------------------------

int cpu_dtor(cpu_t *pCPU)
{
    StackDtor(&pCPU->stk);
    StackDtor(&pCPU->retstk);
    for (int i = 0; i < REG_MAX; ++i)
        pCPU->reg[i] = NAN;
    for (int i = 0; i < RAM_SIZE; ++i)
        pCPU->RAM[i] = NAN;
    free(pCPU->code);
    return 0;
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
                printf(# name ": data: a = %ld, b = %ld\n", a, b);      \
                if (a op b)                                             \
                {                                                       \
                    char * num = &pCPU->code[pCPU->RPC + 1];            \
                    char * end;                                         \
                    label_t val = strtol(num, &end, 10);                \
                    printf("new pc = %ld\n", val);                      \
                    pCPU->RPC = val - 1;                                \
                }                                                       \
            }

        switch (pCPU->code[pCPU->RPC])
        {
            #include "/Users/andreyandriyaynen/CLionProjects/CPU/commands/commands.h"
        }

        #undef JUMP
        #undef CMD_DEF

        pCPU->RPC++;

    }
}

//-----------------------------------------------------------------------------------------------------

int cpu_dump(cpu_t *pCPU)
{
    if (!DEBUG)
        return 1;

    printf( "\n# CPU [%p] (OK)\n", pCPU );
    printf("# REG count = %d\n", REG_MAX);
    printf("# RPC = %ld\n", pCPU->RPC);
    printf("# REG[%d][%p]\n", REG_MAX, pCPU->reg);
    printf("#      {\n");
    for (int j = 0; j < REG_MAX; ++j)
        printf("#        reg[%d] = %ld\n", j, pCPU->reg[j]);
    printf("#      }\n");
    printf( "# RAM size = %d\n", RAM_SIZE);
    printf("# RAM[%d][%p]\n#      {\n", RAM_SIZE, pCPU->RAM);

    for ( int i = 0; i < RAM_SIZE; i++ )
        printf( "#        [%d]: %ld\n", i, pCPU->RAM[i] );

    printf( "#      }\n"
                    "# }\n\n" );

    return 0;
}
