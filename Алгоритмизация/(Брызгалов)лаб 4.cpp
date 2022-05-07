#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<locale.h>
#include<iostream>

typedef struct bintree {
	char sign;
	float num;
	bintree* right;
	bintree* left;
}bintree;



int prior(char a)
{
	switch (a)
	{
	case '*':
		return 2;
	case '/':
		return 2;
	case '-':
		return 1;
	case '+':
		return 1;
	default: return 10;
	}
}

bintree* createTree(int first, int last, char* arr) {
	bintree* tree = (bintree*)malloc(sizeof(bintree));
	int MinPrior = 10, i, k, prt;
	if (arr[first] == '\0') return NULL;
	if (first == last){
		tree->num = arr[first]-'0';
		tree->sign = NULL;
		tree->left = NULL;
		tree->right = NULL;
		return tree;
	}

	for (i = first; i < last; i++){
		prt = prior(arr[i]);
		if (prt <= MinPrior){
			MinPrior = prt;
			k = i;
		}
	}
	tree->sign = arr[k];
	tree->num = NULL;
	tree->left = createTree(first, k - 1, arr);
	tree->right = createTree(k + 1, last, arr);
	return tree;
}


void printPre(bintree* node) {
	if (!node) return;
	if (node->num != NULL)printf_s("%.0f ", node->num);
	if (node->sign != NULL)printf_s("%c ", node->sign);
	printPre(node->left);
	printPre(node->right);
}

void printIn(bintree* node) {
	if (!node) return;
	printIn(node->left);
	if (node->num != NULL)printf_s("%.0f ", node->num);
	if (node->sign != NULL)printf_s("%c ", node->sign);
	printIn(node->right);
}

void printPost(bintree* node) {
	if (!node) return;
	printPost(node->right);
	printPost(node->left);
	if (node->num != NULL)printf_s("%.0f ", node->num);
	if (node->sign != NULL)printf_s("%c ", node->sign);
}

float calcTree(bintree* tree)
{
	float num1, num2;
	if ((tree->left == NULL)&&(tree->right==NULL)) return tree->num;
	if(tree->left)num1 = calcTree(tree->left);
	if (tree->right)num2 = calcTree(tree->right);
	switch (tree->sign) { 
	case '+': return num1 + num2;
	case '-': return num1 - num2;
	case '*': return num1 * num2;
	case '/': return num1 / num2;
	}
}

int main(void) {
	setlocale(LC_ALL, "Russian");

	bintree* root = NULL;
	char str[50] = { '\0' };
	int size=0;
	FILE* f = fopen("input.txt", "r+");


	if (f == NULL) {
		printf_s("Файл пуст!");
		fclose(f);
		exit(0);
	}
	for (int i = 0; !feof(f); i++) {
		fscanf(f, "%c", &str[i]);
		size++;
	}
	fclose(f);
	printf_s("Выражение: %s\n", str);
	root=createTree(0, size, str);
	printf_s("Прямой обход: ");
	printPre(root);
	printf_s("\nПоперечный обход: ");
	printIn(root);
	printf_s("\nОбратный обход: ");
	printPost(root);
	printf_s("\nЗначение выражения: %f", calcTree(root));
}