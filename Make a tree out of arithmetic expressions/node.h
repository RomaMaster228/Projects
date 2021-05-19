#ifndef _NODE_H
#define _NODE_H
#include "token.h"

typedef struct node node;

struct node{
        token t;
        struct node* left;
        struct node* right;
};

#endif