#include "Stack.h"

#include <string.h>

// used for runtime type saftey checks
static const char* const TOKEN = "$tack";

typedef struct Stack {
    void*  beg;
    void*  data;
    void*  end;
    size_t itemSize;
    const char* token;
} Stack;

static int isStack(Stack* this) {
    return (this->token == TOKEN);
}

Stack* Stack_Create(size_t count, size_t itemSize) {
    Stack* this    = calloc(1, sizeof(Stack));
    this->data     = calloc(1, count * itemSize);
    this->beg      = this->data;
    this->end      = this->data + count * itemSize;
    this->token    = TOKEN;
    this->itemSize = itemSize;
    return this;
}

Stack_Result Stack_Push(Stack* this, void* src) {
    if(!isStack(this)) {
        return STACK_UNRECOGNIZED;
    }

    if((this->data + this->itemSize) >= this->end) {
        return STACK_FULL;
    }

    memcpy(this->data, src, this->itemSize);
    this->data += this->itemSize;
    return STACK_SUCCESS;
}

Stack_Result Stack_Pop(Stack* this, void* dest) {
    if(!isStack(this)) {
        return STACK_UNRECOGNIZED;
    }

    if(isStack(this) && (this->data - this->itemSize) <= this->beg) {
        return STACK_EMPTY;
    }

    this->data -= this->itemSize;
    memcpy(dest, this->data, this->itemSize);
    return STACK_SUCCESS;
}

Stack_Result Stack_Destroy(Stack* this) {
    if(isStack(this)) {
        free(this->data);
        free(this);
        return STACK_SUCCESS;
    }
    return STACK_UNRECOGNIZED;
}
