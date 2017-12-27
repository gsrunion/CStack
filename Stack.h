#ifndef GENERIC_STACK_STACK_H
#define GENERIC_STACK_STACK_H

#include <stdlib.h>

typedef struct Stack Stack;

typedef enum Stack_Result {
    STACK_SUCCESS,
    STACK_UNRECOGNIZED,
    STACK_FULL,
    STACK_EMPTY,
} Stack_Result;

Stack*       Stack_Create (size_t count, size_t itemSize);
Stack_Result Stack_Push   (Stack* this, void* src);
Stack_Result Stack_Pop    (Stack* this, void* dest);
Stack_Result Stack_Destroy(Stack* this);

#endif
