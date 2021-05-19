#include "stack.h"

const int POOL_SIZE = 100;

void Create_s(stack* s) {
        s->size = 0;
        Create(&s->arr, POOL_SIZE);
}

void Destroy_s(stack* s) {
        Destroy(&s->arr);
}

bool Empty_s(stack* s) {
        return s->size == 0;
}

int Size_s(stack* s) {
        return s->size;
}

bool Push_s(stack* s, token el) {
        if (s->size >= Size(&s->arr)) {
                if (Resize(&s->arr, s->size * 2)) {
                        Insert(&s->arr, s->size, el);
                        return true;
                }
                else {
                        return false;
                }
        }
        else {
                Insert(&s->arr, s->size, el);
                s->size++;
                return true;
        }
}

token Pop_s(stack* s) {
        token temp;
        temp = Erase(&s->arr, s->size - 1);
        s->size--;
        return temp;
}