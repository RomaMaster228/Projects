#ifndef _VECTOR_H
#define _VECTOR_H

#include "token.h"
#include <stdbool.h>

typedef struct {
        token* data;
        int size;
} vector;

void Create(vector* v, int sizev);
void Destroy(vector* v);
bool Empty(vector* v);
int Size(vector* v);
void Insert(vector* v, int i, token el);
token Erase(vector* v, int i);
bool Resize(vector* v, int new_size);

#endif