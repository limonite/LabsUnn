#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<locale.h>
#include<iostream>

typedef struct bintree {
	int num;
	bintree* right;
	bintree* left;
}bintree;

typedef struct stack {
	bintree* sNode;
	int size;
	stack* next;
	stack* prev;
}stack;

stack* createStack(bintree* node) {
	stack* tmp = (stack*)malloc(sizeof(stack));
	tmp->sNode = node;
	tmp->size = 1;
	tmp->prev = NULL;
	tmp->next = NULL;
	return tmp;
}

stack* push(stack* top, bintree* node) {
	if (top == NULL) return createStack(node);
	else {
		stack* tmp = (stack*)malloc(sizeof(stack));
		tmp->sNode = node;
		tmp->size = top->size + 1;
		tmp->prev = top;
		tmp->next = NULL;
		top->next = tmp;
		return tmp;
	}
}

bintree* peek(stack* top) {
	return top->sNode;
}

void clearStack(stack** top) {
	free((*top)->next);
	((*top)->next) = NULL;
}

stack* pop(stack* top) {
	if (top == NULL) {
		printf_s("Стек пуст!");
		exit(0);
	}
	if (top->prev == NULL) {
		free(top);
		top = NULL;
		return top;
	}
	top = top->prev;
	clearStack(&top);
	return top;
}

void noRecPrintPre(bintree* node) {
	stack* top=createStack(node);

	while (top != NULL) {
		if(node->right) {
			top = push(top,node->right);
		}
		if (node->left) {
			printf_s("%d ", node->num);
			node=node->left;
		}
		else {
			printf_s("%d ", node->num);
			node = peek(top);
			top = pop(top);
		}
	}
}

bintree* createNode(int n) {
	bintree *tmp=(bintree*)malloc(sizeof(bintree));
	tmp->num = n;
	tmp->right = NULL;
	tmp->left = NULL;
	return tmp;
}

bintree* addElement(bintree* node, int n) {
	if (node == NULL) return createNode(n);
	if (node->num > n) node->left = addElement(node->left, n);
	else if (node->num < n) node->right = addElement(node->right, n);
	return node;
}

void printTree(bintree* node) {
	static int n = 0;
	if (!node) return;
	n++;
	printTree(node->right);
	printf_s("(Уровень %d) %d\n", n, node->num); 
	printTree(node->left);
	n--;
}

void printPre(bintree* node) {
	if (!node) return;
	printf_s("%d ", node->num);
	printPre(node->left);
	printPre(node->right);
}

void printIn(bintree* node) {
	if (!node) return;
	printIn(node->left);
	printf_s("%d ", node->num);
	printIn(node->right);
}

void printPost(bintree* node) {
	if (!node) return;
	printPost(node->right);
	printPost(node->left);
	printf_s("%d ", node->num);
}

int height(bintree* node) {
	int heightLeft = 0;
	int heightRight = 0;
	if (node == NULL) return 0;
	if (node->left != NULL) heightLeft = 1;
	else heightLeft = 0;
	if (node->right != NULL) heightRight = 1;
	else heightRight = 0;
	if (node->left) heightLeft += height(node->left);
	if (node->right) heightRight += height(node->right);
	if (heightLeft > heightRight) return heightLeft;
	else return heightRight;
}

int leaf(bintree* node) {
	int n;
	if (node == NULL) return 0;
	if ((node->left == NULL) && (node->right == NULL)) n = 1;
	else n = 0;
	if (node->left) n += leaf(node->left);
	if (node->right) n += leaf(node->right);
	return n;
}

void deleteTree(bintree** node) {
	if (*node) {
		deleteTree(&((*node)->left));
		deleteTree(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}


int main(void) {
	setlocale(LC_ALL, "Russian");
	FILE* f = fopen("input.txt", "r+");

	bintree* root = NULL;

	char choice = 0;
	int n;
	char clear;

	if (f == NULL) {
		printf_s("Файл пуст!");
		exit(0);
	}
	fscanf(f, "%d", &n);
	root = createNode(n);
	while (!feof(f)) {
		fscanf(f, "%d", &n);
		addElement(root, n);
	}
	printTree(root);
	printf_s("\nВысота: %d, Кол-во листьев : %d\n", height(root) + 1, leaf(root));
	while (1) {
		printf_s("________________________\n");
		printf_s("Действия с сортирующим деревом:\n1. Прямой обход.\n2. Поперечный обход.\n3. Обратный обход\n4. Прямой обход (нерекурсивный)\n5. Удаление дерева\n(Для выхода нажмите 0)\nВаш выбор:  ");
		scanf_s("%c", &choice);
		getchar();
		printf_s("\n________________________\n");
		switch (choice) {
		case '1':
			printf_s("________________________\n");
			printf_s("Прямой обход : ");
			printPre(root);
			printf_s("\n________________________\n");
			break;
		case '2':
			printf_s("________________________\n");
			printf_s("Поперечный обход : ");
			printIn(root);
			printf_s("\n________________________\n");
			break;
		case '3':
			printf_s("________________________\n");
			printf_s("Обратный обход : ");
			printPost(root);
			printf_s("\n________________________\n");
			break;
		case '4':
			printf_s("________________________\n");
			printf_s("Прямой обход(не рекурсия) : ");
			noRecPrintPre(root);
			printf_s("\n________________________\n");
			break;
		case '5':
			printf_s("________________________\n");
			deleteTree(&root);
			printf_s("Дерево удаленно!");
			printf_s("\n________________________\n");
			break;
		default: exit(0);
		}
	}
}