//
// Created by Andrey Andriyaynen on 01/11/2018.
//


#include "stack.h"

//-----------------------------------------------------------------------------------------------------

#define UNITTEST(what, op, ref)                                                                     \
    {                                                                                               \
    int result = (what);                                                                            \
    if (result op (ref))                                                                            \
        printf("# [passed] " # what "\n\n");                                                        \
    else                                                                                            \
        printf("# " # what " is %d, but true is " #op " %d, line %d\n\n", result, (ref), __LINE__); \
    }

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
    else
    {
        if(STK_CANARY_PROT)
        {
            if (pStack->bcanary != POISON || pStack->ecanary != POISON || 0 > pStack->count ||
                pStack->count > pStack->size)
                return -3;
        }
        if (0 > pStack->count || pStack->count > pStack->size)
            return -3;
    }

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

    pStack->data = (elem_t *) realloc( pStack->data, pStack->size * 2 );
    pStack->size = pStack->size * 2;

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

int StackDump( Stack * pStack )
{
    if (!DEBUG)
        return 1;

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
                printf( "#       *[%d]: %ld\n", i, pStack->data[i] );
            else
            if ( pStack->data[i] == STK_POISON)
                printf( "#        [%d]: %ld (STK_POISON)\n", i, pStack->data[i] );
            else
                printf( "#        [%d]: %ld (TRASH)\n", i, pStack->data[i] );
        }
        printf( "#      }\n"
                        "# }\n\n" );
    }

    return 0;
}