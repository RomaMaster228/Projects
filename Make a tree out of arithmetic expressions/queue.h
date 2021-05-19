#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdbool.h>
#include "token.h"

typedef struct {
        token data[100];
        int first;
        int size;
} queue;

void Create_q(queue* q);
bool Empty_q(queue* q);
int Size_q(queue* q);
void Destroy_q(queue* q);
bool Push_q(queue* q, token el);
token Pop_q(queue* q);
token Pop_back(queue* q);

#endif