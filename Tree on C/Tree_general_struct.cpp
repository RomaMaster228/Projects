#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

const int POOL = 1000;

typedef enum pets{
	cats,
	dogs,
	parrots,
	fish,
	humsters
} pets;

typedef struct node node;

struct node {
	pets val;
	struct node* next_bro;
	struct node* first_child;
};

bool check(char* c, pets* p) {
	if (strcmp(c, "cats") == 0) {
		*p = cats;
		return true;
	}
	else if (strcmp(c, "dogs") == 0) {
		*p = dogs;
		return true;
	}
	else if (strcmp(c, "parrots") == 0) {
		*p = parrots;
		return true;
	}
	else if (strcmp(c, "fish") == 0) {
		*p = fish;
		return true;
	}
	else if (strcmp(c, "humsters") == 0) {
		*p = humsters;
		return true;
	}
	else {
		printf("Некорректный ввод! \n");
		return false;
	}
}

node* create_tree() {
	char word[POOL];
	printf("Введите корень дерева: ");
	scanf("%s", word);
	pets v;
	if (check(word, &v)) {
		node* tree = (node*)malloc(sizeof(node));
		tree->val = v;
		tree->first_child = NULL;
		tree->next_bro = NULL;
		return tree;
	}
	else {
		printf("Дерево не создано!\n");
	}
}


bool add(node** t, pets val, char* path) {
	if ((*path != '\0') && (*t == NULL)) {
		return false;
	}
	if (*path == 'c') {
		return add(&(*t)->first_child, val, path + 1);
	}
	else if (*path == 'b') {
		return add(&(*t)->next_bro, val, path + 1);
	}
	else if (*path == '\0') {
		node* tmp = (node*)malloc(sizeof(node));
		tmp->val = val;
		tmp->first_child = NULL;
		tmp->next_bro = *t;
		*t = tmp;
		return true;
	}
	else {
		return false;
	}
}

void scan_tree(node* t) { //termination command
	int n;
	printf("Введите количество вершин: ");
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		char com[POOL];
		char word[POOL];
		printf("Введите пару домашнее животное, команда: ");
		scanf("%s%s", word, com);
		pets p;
		if (check(word, &p)) {
			if (!add(&t, p, com)) {
				printf("Вставка не случилась \n");
			}
		}
		else {
			printf("Узел не был создан!");
		}
	}
}

void print_dfs(node* t) {
	if (t == NULL) {
		return;
	}
	print_dfs(t->first_child);
	printf("%d ", t->val);
	print_dfs(t->next_bro);
}

typedef struct {
	node* data[1000];
	int first;
	int size;
} queue;

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

void Destroy(queue* q) {
	q->size = 0;
}

bool Push_q(queue* q, node* el) {
	if (q->size >= POOL) {
		return false;
	}
	q->data[(q->first + q->size) % POOL] = el;
	q->size++;
	return true;
}

node* Pop_q(queue* q) {
	node* temp = q->data[q->first];
	q->first++;
	q->first %= POOL;
	q->size--;
	return temp;
}

void print_bfs(node* t) {
	if (t == NULL) {
		return;
	}
	printf("%d\n", t->val);
	queue q;
	Create_q(&q);
	if (t->first_child == NULL) {
		return;
	}
	Push_q(&q, t->first_child);
	int arr[POOL];
	arr[0] = 0;
	int lvl = 1;
	arr[lvl] = 0;
	arr[lvl + 1] = 0;
	while (!Empty_q(&q)) {
		node* bro = Pop_q(&q);
		while (bro != NULL) {
			if (bro->first_child != NULL) {
				Push_q(&q, bro->first_child);
				arr[lvl + 1]++;
			}
			printf("%d ", bro->val);
			if (arr[lvl] != 0) {
				arr[lvl]--;
			}
			bro = bro->next_bro;
		}
		if (arr[lvl] == 0) {
			printf("\n");
			lvl++;
			arr[lvl + 1] = 0;
		}
	}
	Destroy(&q);
}

void tree_degree(node* t) {
	if (t == NULL) {
		return;
	}
	queue q;
	Create_q(&q);
	if (t->first_child == NULL) {
		return;
	}
	Push_q(&q, t->first_child);
	int cnt = 0;
	int max = 0;
	while (!Empty_q(&q)) {
		int k = 0;
		node* bro = Pop_q(&q);
		while (bro != NULL) {
			k++;
			if (bro->first_child != NULL) {
				Push_q(&q, bro->first_child);
			}
			bro = bro->next_bro;
		}
		if (max < k) {
			max = k;
			cnt = 0;
		}
		if (k == max) {
			cnt++;
		}
	}
	printf("Степень дерева: %d \n", max);
	printf("Количество вершин дерева с равными дереву степенями: %d \n", cnt);
	Destroy(&q);
}

node** find(node** t, char* path) {
	if ((*path != '\0') && (*t == NULL)) {
		return NULL;
	}
	else if (*path == 'c') {
		return find(&(*t)->first_child, path + 1);
	}
	else if (*path == 'b') {
		return find(&(*t)->next_bro, path + 1);
	}
	else if (*path == '\0') {
		return t;
	}
	else {
		return NULL;
	}
}

pets remove_left(node** t) {
	if ((*t)->first_child != NULL) {
		return remove_left(&(*t)->first_child);
	}
	else {
		pets p = (*t)->val;
		node* a = (*t)->next_bro;
		free(*t);
		*t = a;
		return p;
	}
}

void remove_node(node** t) {
	if (t == NULL) {
		return;
	}
	if ((*t)->first_child == NULL) {
		node* a = (*t)->next_bro;
		free(*t);
		*t = a;
	}
	else if ((*t)->next_bro == NULL ) {
		node* a = (*t)->first_child;
		free(*t);
		*t = a;
	}
	else {
		pets p = remove_left(&(*t)->next_bro);
		(*t)->val = p;
	}
}


int main() {
	setlocale(LC_ALL, "rus");
	node* t = NULL;
	t = create_tree();
	scan_tree(t);
	print_bfs(t);
	tree_degree(t);
	char com[POOL];
	printf("Введите путь к элементу, который хотите удалить: ");
	scanf("%s", com);
	remove_node(find(&t, com));
	print_bfs(t);
	return 0;
}