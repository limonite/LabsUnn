//для char
#include <stdio.h>
#include<conio.h>
#include<stdlib.h>
int is_full(int top) {
	if (top > 18) return 1;
	else return 0;
}
int is_empty(int top) {
	if (top > -1) return 0;
	else return 1;
}
void push(char* stack, int* top, char value) {
	if (is_full(*top)) {
		printf_s("\nСтек переполнен\n");
		exit(0);
	}
	(*top)++;
	stack[(*top)] = value;
}
char pop(char* stack, int* top) {
	if (is_empty(*top)) {
		printf_s("\nСтек пуст\n");
		exit(0);
	}
	(*top)--;
	return stack[(*top) + 1];
}
char peek(char* stack, int top) {
	return stack[top];
}
void clear(int* top) {
	(*top) = -1;
}

//для float
void fpush(float* stack, int* top, float value) {
	(*top)++;
	stack[(*top)] = value;
}
float fpop(float* stack, int* top) {
	(*top)--;
	return stack[(*top) + 1];
}
float fpeek(float* stack, int top) {
	return stack[top];
}