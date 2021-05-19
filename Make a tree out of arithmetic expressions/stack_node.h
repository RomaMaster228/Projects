#ifndef _STACK_NODE_H
#define _STACK_NODE_H
#include "node.h"
#include <stdbool.h>

typedef struct {
        int size;
        node* data[100];
} stack_node;

void Create_snode(stack_node* s);
bool Empty_snode(stack_node* s);
int Size_snode(stack_node* s);
bool Push_snode(stack_node* s, node* t);
node* Pop_snode(stack_node* s);

#endif