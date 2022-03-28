#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<locale.h>

int main(void) {
	setlocale(LC_ALL, "Russian");

	int quant = 0;//кол-во процессов
	int* p = NULL;//массив времени выполнения процессов
	int* id = NULL;//номер процесса
	int* pr1 = NULL;//1-й прецессор
	int* id1 = NULL;//номер процесса(1-й процессор)
	int* id2 = NULL;//номер процесса(2-й процессор)
	int top1 = -1;//вершина id1
	int* pr2 = NULL;//2-й прецессор
	int top2 = -1;//вершина id2
	int sum1=0, sum2 = 0;//суммарное время для 1-го и 2-го процессора

	printf_s("Введите кол-во процессов: ");
	scanf_s("%d", &quant);
	p = (int*)malloc(sizeof(int) * quant);//выделяем память для записи времени процессов
	pr1 = (int*)malloc(sizeof(int) * quant);
	pr2 = (int*)malloc(sizeof(int) * quant);
	id = (int*)malloc(sizeof(int) * quant);
	id1 = (int*)malloc(sizeof(int) * quant);
	id2 = (int*)malloc(sizeof(int) * quant);
	printf_s("\n____________\n");

	// заполняем массив времени выполнения процесса
	for (int i = 0; i < quant; i++) {
		printf_s("Введите время выполнения %d-го процесса: ", i + 1);
		scanf_s("%d", &p[i]);
		id[i] = i + 1;
	}
	printf_s("\n____________\n");

	// сортируем масси по убыванию
	int k = 0;// для сортировки
	int m = 0;
	for (int i = 0; i < quant; i++) {
		for (int j = i + 1; j < quant; j++) {
			if (p[i] < p[j]) {
				k = p[i]; m = id[i];
				p[i] = p[j]; id[i] = id[j];
				p[j] = k; id[j] = m;
			}
		}
	}

	// распределяем процессы по процессорам и пошагово выводим информацию
	for (int i = 0; i < quant; i++) {
		printf_s("\n____________\n");
		if ((p[i] + sum1) <= sum2) {
			sum1 += p[i];
			top1++;
			id1[top1] = id[i];
		}
		else {
			sum2 += p[i];
			top2++;
			id2[top2] = id[i];
		}
		printf_s("Шаг №%d\n", i + 1);
		printf_s("Процессор 1: ");
		for (int i = 0; i <= top1; i++) {
			printf_s("%-4d", id1[i]);
		}
		printf_s("| Сумма: %d\n", sum1);
		printf_s("Процессор 2: ");
		for (int i = 0; i <= top2; i++) {
			printf_s("%-4d", id2[i]);
		}
		printf_s("| Сумма: %d", sum2);
		printf_s("\n____________\n");
	}
}