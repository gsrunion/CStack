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

static int hasRoom(Stack* this) {
    return (this->data + this->itemSize)) >= this->end;
}

static int hasItems(Stack* this) {
    return (this->data - this->itemSize) <= this->beg;
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

    if(!hasRoom(this)) {
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

    if(!hasItems(this)) {
        return STACK_EMPTY;
    }

    this->data -= this->itemSize;
    memcpy(dest, this->data, this->itemSize);
    return STACK_SUCCESS;
}

Stack_Result Stack_Destroy(Stack* this) {
    if(!isStack(this)) {
        return STACK_UNRECOGNIZED;
    }
    
    free(this->data);
    free(this);
    return STACK_SUCCESS;
}
