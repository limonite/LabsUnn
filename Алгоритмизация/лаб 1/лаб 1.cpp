#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<locale.h>
#include"stack.h"

// приоритеты операций в обратной польской записи
int prior(char a)
{
	switch (a)
	{
	case '*':
		return 3;
	case '/':
		return 3;
	case '-':
		return 2;
	case '+':
		return 2;
	case '(':
		return 1;
	default: return 10;
	}
}

//проверка на число
int num(char a) {
	if ((a == '(') || (a == ')') || (a == '+') || (a == '-') || (a == '/') || (a == '*') || (a == '\0') || (a == ' ')) return 0;
	else return 1;
}


int main() {
	int top = -1; // вершина стека stack
	int topres = -1;//вершина стека res
	int ftop = -1;//вершина стека fstack
	char stack[20] = { '\0' };// стек для скобок
	char res[70] = { '\0' };// результат в польской записи
	char str[30] = { '\0' };//входная строка
	float fstack[20] = { 0 };//стек для вычисления значения
	FILE* f = fopen("input.txt", "rt"); 

	setlocale(LC_ALL, "Russian");

	//считывание выражения с файла
	fscanf(f, "%s", str);
	fclose(f);
	FILE* k = fopen("output.txt", "w+");
	printf_s("Исходное выражение: %s\n", str);
	fprintf_s(k,"Исходное выражение: %s\n", str);
	// проверка на корректность расстановки скобок, переполнение стека
	for (int i = 0; str[i] != '\0'; i++)
	{
		switch (str[i]) {
		case '(':
			if (!is_full(top)) push(stack, &top, '(');
			else {
				printf_s("Стек переполнен\n");
				fprintf_s(k,"Стек переполнен\n", str);
				fclose(k);
				exit(0);
			}
			break;
		case ')':
			if (!is_empty(top)) pop(stack, &top);
			else {
				printf_s("Выражение некорректно\n");
				fprintf_s(k,"Выражение некорректно\n");
				fclose(k);
				exit(0);
			}
			break;
		}
	}
	if (is_empty(top)) {
		printf("Выражение корректно\n");
		fprintf(k,"Выражение корректно\n");
	}
	else {
		printf("Выражение некорректно\n");
		fprintf(k,"Выражение некорректно\n");
		fclose(k);
		exit(0);
	}

	// чистка стека
	for (int i = 0; i < 20; i++) stack[i] = '\0';
	clear(&top);

	// преобразование выражение в обратную польскую запись
	int i = 0;
	while (str[i]!='\0') {
		if (num(str[i])) {
			push(res, &topres, str[i]);
			for(i=i+1;num(str[i]);i++) push(res, &topres, str[i]);
			push(res, &topres, ' ');
			continue;
		}
		else {
			if (str[i] == '(') {
				push(stack, &top, str[i]);
				i++;
				continue;
			}
			else if (str[i] == ')') {
				while (peek(stack,top) != '(') {
					push(res, &topres, pop(stack, &top));
					push(res, &topres, ' ');
				}
				pop(stack, &top);
				i++;
				continue;
			}
			else {
				if (is_empty(top)) {
					push(stack, &top, str[i]);
					i++;
					continue;
				}
				else {
					if (prior(str[i]) > prior(peek(stack, top))) {
						push(stack, &top, str[i]);
						i++;
						continue;
					}
					else {
						while ((prior(peek(stack,top))>=prior(str[i]))&&(!is_empty(top))) {
							push(res, &topres, pop(stack, &top));
							push(res, &topres, ' ');
						}
						push(stack, &top, str[i]);
						i++;
						continue;
					}
				}
			}
		}
	}
	while (!is_empty(top)) {
		push(res, &topres, pop(stack, &top));
		push(res, &topres, ' ');
	}
	printf_s("Обратная польская запись: %s\n", res);
	fprintf_s(k,"Обратная польская запись: %s\n", res);

	//вычисление занчения
	i = 0;
	char dop[10] = { '\0' };//строка для преобразования типов
	int j;//счётчик
	float a, b;// два числа(для бинарных операций)
	while (res[i]!='\0') {
		if (num(res[i])) {
			for (j = 0; j < 10; j++) dop[j] = '\0';
			dop[0] = res[i];
			for (j = 1; num(res[i + j]); j++) dop[j] = res[i + j];
			fpush(fstack, &ftop, atof(dop));
			i = i + j;
		}
		else {
			switch (res[i]) {
			case '+':
				b = fpop(fstack, &ftop);
				a = fpop(fstack, &ftop);
				fpush(fstack, &ftop, (a + b));
				break;
			case '-':
				b = fpop(fstack, &ftop);
				a = fpop(fstack, &ftop);
				fpush(fstack, &ftop, (a - b));
				break;
			case '*':
				b = fpop(fstack, &ftop);
				a = fpop(fstack, &ftop);
				fpush(fstack, &ftop, (a * b));
				break;
			case '/':
				b = fpop(fstack, &ftop);
				a = fpop(fstack, &ftop);
				fpush(fstack, &ftop, a / b);
				break;
			default:
				break;
			}
		}
		i++;
	}
	printf_s("Результат: %-10.2f\n", fpeek(fstack, ftop));
	fprintf_s(k,"Результат: %-10.2f\n", fpeek(fstack, ftop));
	fclose(k);
}