//
// Created by Andrey Andriyaynen on 01/11/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

//-----------------------------------------------------------------------------------------------------
/**
 *
 * @param [in] pStack   pointer to stack
 *
 *
 * @return 1 if stack is clear, -1 if pointer is nullptr, -2 if pointer to data is nullptr,\
 * -3 if data is broken
 *
 */
int StackOk( const Stack * pStack )
{
    if ( pStack == nullptr )
        return -1;
    else if ( pStack->data == nullptr )
        return -2;
    else if (pStack->bcanary != POISON || pStack->ecanary != POISON || 0 > pStack->count ||\
                                                                pStack->count > pStack->size)
        return -3;
    else
        return 1;
}

//-----------------------------------------------------------------------------------------------------

int StackCtor( Stack* pStack, int StackSize ) //добавить здесь и в других функциях код возврата
{
    if ( pStack == nullptr )
        return 2;

    elem_t *buffer = (elem_t *) calloc(StackSize, sizeof(elem_t));

    if ( buffer == nullptr )
        return 1;

    pStack->bcanary = POISON;
    pStack->count = 0;
    pStack->data = buffer;
    pStack->size = StackSize;
    pStack->ecanary = POISON;
    return 0;
}
//-----------------------------------------------------------------------------------------------------


int StackDtor( Stack * pStack )
{
    if ( StackOk( pStack ) < 0 )
        return StackOk( pStack );

    free( pStack->data );
    pStack->size = 0;
    return 0;
}

//-----------------------------------------------------------------------------------------------------

int StackPush( Stack * pStack, elem_t val )
{
    if ( StackOk( pStack ) < 0 )
        return StackOk( pStack );

   // StackDump( pStack );

    if ( pStack->count < pStack->size )
    {
        pStack->data[ pStack->count++ ] = val;
        return 0;                                               //clear
    }

    if ( pStack->size > REALLOC_LIMIT )
    {
        pStack->data = (elem_t *) realloc( pStack->data, pStack->size * 1.5 );
        pStack->size = pStack->size * 1.5;
    }
    else
    {
        pStack->data = (elem_t *) realloc( pStack->data, pStack->size * 2 );
        pStack->size = pStack->size * 2;
    }
    if ( StackOk( pStack ) < 0)
        return StackOk( pStack );
    else
    {
        pStack->data[ pStack->count++ ] = val;
        return 0;
    }
}

//-----------------------------------------------------------------------------------------------------

int StackPop( Stack * pStack, elem_t * retData )
{
    if ( StackOk( pStack ) < 0 )
        return StackOk( pStack );

    if ( retData == nullptr )
        return 2;
    // let it sigsegv

   // StackDump( pStack );

    if ( !StackIsEmpty( pStack ) )
    {
        *retData = pStack->data[ --pStack->count ];
        pStack->data[ pStack->count] = STK_POISON;
        return 0; //clear
    }
    else
        return 1;  // stack is empty
    /// -1
}

//-----------------------------------------------------------------------------------------------------

int StackIsEmpty ( Stack * pStack )
{
    if ( StackOk( pStack ) < 0)
        return StackOk( pStack );

    if ( pStack->count > 0 )
        return 0;

    return 1;
}

//-----------------------------------------------------------------------------------------------------

int StackTop( Stack * pStack, elem_t * retData )
{
    if ( StackOk( pStack ) < 0 )
        return StackOk( pStack );

    if ( retData == nullptr )
        return 3;

    if ( !StackIsEmpty( pStack ) )
    {
        * retData = pStack->data[ pStack->count - 1 ];
        return 0; //clear
    }

    return 1; // couldn't return stack top
}