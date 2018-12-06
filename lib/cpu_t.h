//
// Created by Andrey Andriyaynen on 06/12/2018.
//

#ifndef CPU_CPU_T_H
#define CPU_CPU_T_H

//-----------------------------------------------------------------------------------------------------

#include "stack.h"
#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "stack.h"

//-----------------------------------------------------------------------------------------------------

typedef long num_t;
typedef long label_t;

//-----------------------------------------------------------------------------------------------------

#define CMD_DEF(name, code)\
    CMD_##name,

enum CMD_NUM
{
#include "/Users/andreyandriyaynen/CLionProjects/CPU/commands/commands.h"
    CMD_DEF(MAX,)
};
#undef CMD_DEF

#define REG_DEF(name)\
    REG_##name,

enum REG_NUM
{
#include "/Users/andreyandriyaynen/CLionProjects/CPU/commands/reg_codes.h"

    REG_DEF(MAX)
};
#undef REG_DEF

enum CONSTS
{
    RAM_SIZE = 10,
    STK_START_SIZE = 10
};

#define DEBUG true

//-----------------------------------------------------------------------------------------------------

struct cpu_t
{
    char * code;
    elem_t reg[REG_MAX];
    Stack stk;
    Stack retstk;
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

#endif //CPU_CPU_T_H
