//
// Created by Andrey Andriyaynen on 01/11/2018.
//

#ifndef STACK_STACK_H
#define STACK_STACK_H

//-----------------------------------------------------------------------------------------------------

#define REALLOC_LIMIT  1024
#define POISON 0xBEDA
#define STK_POISON 0XDEADBEEF

//-----------------------------------------------------------------------------------------------------

typedef uint64_t elem_t; // uint64_t или size_t

//-----------------------------------------------------------------------------------------------------

struct Stack
{
    int bcanary;
    size_t size;                    ///TODO check this type
    size_t count;                   ///and this
    elem_t * data;                  ///and this
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

//-----------------------------------------------------------------------------------------------------

#endif //STACK_STACK_H
