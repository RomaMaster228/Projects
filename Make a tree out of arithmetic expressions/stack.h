#ifndef _STACK_H
#define _STACK_H

#include "vector.h"

typedef struct {
        int size;
        vector arr;
} stack;

void Create_s(stack* s);
void Destroy_s(stack* s);
bool Empty_s(stack* s);
int Size_s(stack* s);
bool Push_s(stack* s, token el);
token Pop_s(stack* s);
#endif