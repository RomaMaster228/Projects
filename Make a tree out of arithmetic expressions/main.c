#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "queue.h"
#include "stack.h"
#include "stack_node.h"

void error() {
        printf("Incorrect input!");
}

bool is_br(int c) {
        if (c == '(' || c == ')') {
                return true;
        }
        else {
                return false;
        }
}

bool is_letter(int c) {
        if (c >= 'a' && c <= 'z') {
                return true;
        }
        else if (c >= 'A' && c <= 'Z') {
                return true;
        }
        else {
                return false;
        }
}

bool is_num(int c) {
        if (c >= '0' && c <= '9') {
                return true;
        }
        else {
                return false;
        }
}

bool is_operator(int c) {
        if (c == '+' || c == '-' || c == '/' || c == '*' || c == '~' || c == '^') {
                return true;
        }
        else {
                return false;
        }
}

bool read_token(queue* q) {
        int cnt = 0;
        while (true) {
                token t;
                int c = getchar();
                if (c == '\n'){
                        break;
                }
                if (c == EOF) {
                        break;
                }
                if (c != ' ' && c != '\t') {
                        if (c == ')' && cnt == 0) {
                                error();
                                return false;
                        }
                        if (c == '-') {
                                if (cnt == 0) {
                                        t.type = operator_;
                                        t.oper = '~';
                                        Push_q(&(*q), t);
                                }
                                else {
                                        token tmp = Pop_back(&(*q));
                                        Push_q(&(*q), tmp);
                                        if (tmp.type == operator_ && (is_operator(tmp.oper) || tmp.oper == '(')) {
                                                t.type = operator_;
                                                t.oper = '~';
                                                Push_q(&(*q), t);
                                        }
                                        else {
                                                t.type = operator_;
                                                t.oper = c;
                                                Push_q(&(*q), t);
                                        }
                                }
                        }
                        else if (is_operator(c) || is_br(c)) {
                                t.type = operator_;
                                t.oper = c;
                                Push_q(&(*q), t);
                        }
                        else if (is_num(c)) {
                                ungetc(c, stdin);
                                double num;
                                scanf("%lf", &num);
                                t.type = number;
                                t.num = num;
                                Push_q(&(*q), t);
                        }
                        else if (is_letter(c) || c == '_') {
                                int pos = 0;
                                t.type = variable;
                                while (is_letter(c) || is_num(c) || c == '_') {
                                        t.var[pos] = c;
                                        pos++;
                                        c = getchar();
                                }
                                t.var[pos] = '\0';
                                Push_q(&(*q), t);
                                ungetc(c, stdin);
                        }
                        else {
                                error();
                                return false;
                        }
                        cnt++;
                }
        }
        return true;
}

void print_expression(queue q1) {
        while (!Empty_q(&q1)) {
                token t = Pop_q(&q1);
                if (t.type == variable) {
                        printf("%s ", t.var);
                }
                if (t.type == number) {
                        printf("%lf ", t.num);
                }
                if (t.type == operator_) {
                        printf("%c ", t.oper);
                }
        }
        printf("\n");
}

int priority(char c1) {
        if (c1 == '~') {
                return 3;
        }
        else if (c1 == '^') {
                return 2;
        }
        else if (c1 == '*' || c1 == '/') {
                return 1;
        }
        else if (c1 == '+' || c1 == '-'){
                return 0;
        }
        else {
                return -1;
        }
}

bool left_association(char c) {
        if (c == '+' || c == '-' || c == '*' || c == '/') {
                return true;
        }
        else {
                return false;
        }
}

bool toilet_deikstra(queue q1, queue* q2) {
        stack s;
        Create_s(&s);
        while (!Empty_q(&q1)) {
                token t = Pop_q(&q1);
                if (t.type == variable) {
                        Push_q(&(*q2), t);
                }
                if (t.type == number) {
                        Push_q(&(*q2), t);
                }
                if (t.type == operator_) {
                        if (!Empty_s(&s)) {
                                token tmp;
                                if (t.oper == ')') {
                                        tmp = Pop_s(&s);
                                        while (!Empty_s(&s)) {
                                                if (tmp.oper == '(') {
                                                        break;
                                                }
                                                Push_q(&(*q2), tmp);
                                                tmp = Pop_s(&s);
                                        }
                                        if (Empty_s(&s) && tmp.oper != '(') {
                                                error();
                                                return false;
                                        }
                                }
                                if (is_operator(t.oper)) {
                                        tmp = Pop_s(&s);
                                        int count = 0;
                                        if (tmp.oper != '(') {
                                                while (priority(t.oper) < priority(tmp.oper)) {
                                                        Push_q(&(*q2), tmp);
                                                        if (!Empty_s(&s)) {
                                                                tmp = Pop_s(&s);
                                                                if (tmp.oper == '(') {
                                                                        break;
                                                                }
                                                        }
                                                        else {
                                                                count++;
                                                                break;
                                                        }
                                                }
                                                while (priority(t.oper) == priority(tmp.oper)) {
                                                        if (left_association(tmp.oper)) {
                                                                Push_q(&(*q2), tmp);
                                                                if (!Empty_s(&s)) {
                                                                        tmp = Pop_s(&s);
                                                                        if (tmp.oper == '(') {
                                                                                break;
                                                                        }
                                                                }
                                                                else {
                                                                        count++;
                                                                        break;
                                                                }
                                                        }
                                                        else {
                                                                break;
                                                        }
                                                }
                                        }
                                        if (count == 0) {
                                                Push_s(&s, tmp);
                                        }
                                        Push_s(&s, t);
                                }
                                if (t.oper == '(') {
                                        Push_s(&s, t);
                                }
                        }
                        else {
                                Push_s(&s, t);
                        }
                }
        }
        while (!Empty_s(&s)) {
                token tmp = Pop_s(&s);
                if (tmp.oper == '(') {
                        error();
                        return false;
                }
                Push_q(&(*q2), tmp);
        }
        Destroy_s(&s);
        return true;
}

int how_many_operands(char c) {
        if (c == '~') {
                return 1;
        }
        else {
                return 2;
        }
}

void dfs(node* t) {
        if (t == NULL) {
                return;
        }
        dfs(t->left);
        if (t->t.type == variable) {
                printf("%s ", t->t.var);
        }
        if (t->t.type == number) {
                printf("%lf ", t->t.num);
        }
        if (t->t.type == operator_) {
                printf("%c ", t->t.oper);
        }
        dfs(t->right);
}

void search_for_const(node* t, int* cnt) {
        if (t == NULL) {
                return;
        }
        search_for_const(t->left, cnt);
        if (t->t.type == number) {
                if ((t->t.num - floor(t->t.num)) == 0) {
                        (*cnt)++;
                }
        }
        search_for_const(t->right, cnt);
}

node* make_tree(queue q) {
        stack_node s;
        Create_snode(&s);
        while (!Empty_q(&q)) {
                token t = Pop_q(&q);
                node* n = (node*)malloc(sizeof(node));
                n->left = NULL;
                n->right = NULL;
                n->t = t;
                if (t.type == variable || t.type == ) {
                        Push_snode(&s, n);
                }
                if (t.type == 2) {
                        int cnt = how_many_operands(t.oper);
                        if (cnt == 1) {
                                if (Empty_snode(&s)) {
                                        error();
                                        return NULL;
                                }
                                node* tmp = Pop_snode(&s);
                                n->right = tmp;
                        }
                        else {
                                if (Empty_snode(&s)) {
                                        error();
                                        return NULL;
                                }
                                node* tmp1 = Pop_snode(&s);
                                if (Empty_snode(&s)) {
                                        error();
                                        return NULL;
                                }
                                node* tmp2 = Pop_snode(&s);
                                n->right = tmp1;
                                n->left = tmp2;
                        }
                        Push_snode(&s, n);
                }
        }
        return Pop_snode(&s);
}

int main(){
        queue q1;
        Create_q(&q1);
        if (read_token(&q1)) {
                printf("Infix: ");
                print_expression(q1);
                queue postfix;
                Create_q(&postfix);
                if (toilet_deikstra(q1, &postfix)) {
                        printf("Postfix: ");
                        print_expression(postfix);
                }
                node* root = make_tree(postfix);
                if (root != NULL) {
                        printf("The current tree is: ");
                        dfs(root);
                        printf("\n");
                        int count = 0;
                        search_for_const(root, &count);
                        printf("Number of constant integer numbers: %d\n", count);
                }
        }
        return 0;
}