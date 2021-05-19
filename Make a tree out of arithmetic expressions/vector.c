#include "vector.h"
#include <stdlib.h>

void Create(vector* v, int sizev) {
        v->size = sizev;
        v->data = (token*)malloc(sizeof(token) * sizev);
}

void Destroy(vector* v) {
        v->size = 0;
        free(v->data);
}

bool Empty(vector* v) {
        return v->size == 0;
}

int Size(vector* v) {
        return v->size;
}

void Insert(vector* v, int i, token el) {
        if ((i >= 0) && (i < v->size)) {
                v->data[i] = el;
        }
}

token Erase(vector* v, int i) {
        return v->data[i];
}

bool Resize(vector* v, int new_size) {
        token* n = (token*)realloc(v->data, sizeof(token) * new_size);
        if (n != NULL) {
                v->size = new_size;
                v->data = n;
                return true;
        }
        else {
                return false;
        }
}