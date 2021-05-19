#ifndef _TOKEN_H
#define _TOKEN_H

typedef enum pattern pattern;

enum pattern{
        variable,
        number,
        operator_
};

typedef struct {
        pattern type; // 0 - variable, 1 - number, 2 - operator
        char var[100];
        double num;
        char oper;
}token;

#endif