#include "stack_node.h"

const int POOL_HERE = 100;

void Create_snode(stack_node* s) {
        s->size = 0;
}

bool Empty_snode(stack_node* s) {
        return s->size == 0;
}

int Size_snode(stack_node* s) {
        return s->size;
}

bool Push_snode(stack_node* s, node* t) {
        if (s->size >= POOL_HERE) {
                return false;
        }
        s->data[s->size] = t;
        s->size++;
        return true;
}

node* Pop_snode(stack_node* s) {
        node* tmp = s->data[s->size - 1];
        s->size--;
        return tmp;
}