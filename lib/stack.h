//
// Created by Andrey Andriyaynen on 01/11/2018.
//

#ifndef STACK_STACK_H
#define STACK_STACK_H

//-----------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------------------------------------------------------------

#define POISON 0xBEDA
#define STK_POISON 0XDEADBEEF
#define STK_CANARY_PROT true
#define DEBUG true

//-----------------------------------------------------------------------------------------------------

typedef long elem_t; // uint64_t или size_t

//-----------------------------------------------------------------------------------------------------

struct Stack
{
    int bcanary;
    size_t size;
    size_t count;
    elem_t * data;
    int ecanary;
};
//-----------------------------------------------------------------------------------------------------

int StackOk( const Stack * pStack );
int StackCtor( Stack * pStack, int StackSize );
int StackDtor( Stack * pStack );
int StackPush( Stack * pStack, elem_t val );
int StackPop( Stack * pStack, elem_t * retData );
int StackIsEmpty ( Stack * pStack );
int StackTop( Stack * pStack, elem_t * retData );
void UnitTests( Stack * pStack );
int StackDump( Stack * pStack );

//-----------------------------------------------------------------------------------------------------

#endif //STACK_STACK_H
