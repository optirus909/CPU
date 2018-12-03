//
// Created by Andrey Andriyaynen on 01/11/2018.
//

#ifndef STACK_STACK_DEBUG_H
#define STACK_STACK_DEBUG_H

//-----------------------------------------------------------------------------------------------------
#ifndef STACK_STACK_H
#define STACK_STACK_H

typedef uint64_t elem_t; // uint64_t или size_t

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

#endif// STACK_STACK_H

void UnitTests( Stack * pStack );
int StackDump( Stack * pStack );

#endif// STACK_STACK_DEBUG_H
