#include "queue.h"

const int POOL_LEN = 100;

void Create_q(queue* q) {
        q->first = 0;
        q->size = 0;
}

bool Empty_q(queue* q) {
        return q->size == 0;
}

int Size_q(queue* q) {
        return q->size;
}

void Destroy_q(queue* q) {
        q->size = 0;
}

bool Push_q(queue* q, token el) {
        if (q->size >= POOL_LEN) {
                return false;
        }
        q->data[(q->first + q->size) % POOL_LEN] = el;
        q->size++;
        return true;
}

token Pop_q(queue* q) {
        token temp = q->data[q->first];
        q->first++;
        q->first %= POOL_LEN;
        q->size--;
        return temp;
}

token Pop_back(queue* q) {
        token temp = q->data[q->size - 1];
        q->size--;
        return temp;
}