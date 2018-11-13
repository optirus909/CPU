//
// Created by Andrey Andriyaynen on 01/11/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "stack_debug.h"


//-----------------------------------------------------------------------------------------------------

#define UNITTEST(what, op, ref)                                                                     \
    {                                                                                               \
    int result = (what);                                                                            \
    if (result op (ref))                                                                            \
        printf("# [passed] " # what "\n\n");                                                                 \
    else                                                                                            \
        printf("# " # what " is %d, but true is " #op " %d, line %d\n\n", result, (ref), __LINE__);                      \
    }                                                                                               \
//-----------------------------------------------------------------------------------------------------

void UnitTests( Stack * pStack )
{
    elem_t pop = 0, top = 0;
    StackPush( pStack, 22 );
    UNITTEST(StackPush(pStack, 22), ==, 0);
    UNITTEST(StackPop(pStack, &pop), ==, 0);
    UNITTEST(pop , == , 22)
    UNITTEST(StackPush(pStack, 1122), ==, 0);
    UNITTEST(StackPush(pStack, 1122), ==, 0);
    UNITTEST(StackIsEmpty(pStack), ==, 0);
    UNITTEST(StackTop(pStack, &top), ==, 0);
    UNITTEST(StackTop(nullptr, &top), ==, -1);
    UNITTEST(StackTop(pStack, nullptr), ==, 3);
    if(!StackTop(pStack, &top))
    {
        UNITTEST(StackTop(pStack, &top), ==, 0);
        UNITTEST(top, ==, 1122);
    }
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------

int StackDump( Stack * pStack )
{
    if ( StackOk(pStack) < 0 )
    {

        printf( "\n# Stack [%p] (!! ERROR !!)\n", pStack );
        switch ( StackOk(pStack) )
        {
            case -1:
                printf( "# {!! nullptr !!}\n" );
                break;
            case -2:
                printf( "# {!! nullptr to data !!}\n" );
                break;
            case -3:
                printf( "# {!! data was broken !!}\n" );
                break;

            default:
                printf( "# {StackOk Error}\n" );
        }
    } else {
        printf( "\n# Stack [%p] (OK)\n", pStack );
        printf( "# {\n# size = %d\n# count = %d\n# data[%d][%p]\n#      {\n", pStack->size, pStack->count, pStack->size, pStack->data );

        for ( int i = 0; i < pStack->size; i++ )
        {
            if ( i < pStack->count )
                printf( "#       *[%d]: %d\n", i, pStack->data[i] );
            else
            if ( pStack->data[i] == STK_POISON)
                printf( "#        [%d]: %d (STK_POISON)\n", i, pStack->data[i] );
            else
                printf( "#        [%d]: %d (TRASH)\n", i, pStack->data[i] );
        }
        printf( "#      }\n"
                        "# }\n\n" );
    }
}