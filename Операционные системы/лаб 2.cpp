#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<locale.h>
#include<time.h>

int min(int* arr, int size);

int main(void) {
	setlocale(LC_ALL, "Russian");

	int quantOfpr;
	int check = 0;
	int* id = NULL;
	int* timeOfpr = NULL;
	int quantumOfTime;
	int remainTime=0;
	int procTime = 0;
	int allTime=0;
	char choice;
	int sumTime = 0;
	int procces;
	int iter = 0;
	int* result = NULL;
	int iR = 0;
	int minpr = _CRT_INT_MAX;
	FILE* f = fopen("input.txt", "r+");
	FILE* in = fopen("output.txt", "w+");

	printf_s("Выберете ввод данных:\n1. Ввести данные\n2. Считать данные с файла.\n3. Рандомизировать данные.\nВаш выбор: ");
	scanf("%c", &choice);
	printf_s("____________________\n");
	switch (choice) {
	case '1':
		printf_s("Введите кол-во процессов: ");
		scanf("%d", &quantOfpr);
		id = (int*)malloc(sizeof(int) * quantOfpr);
		timeOfpr = (int*)malloc(sizeof(int) * quantOfpr);
		result = (int*)malloc(sizeof(int) * quantOfpr);
		for (int i = 0; i < quantOfpr; i++) {
			id[i] = i + 1;
			printf_s("Процесс № %d: ", id[i]);
			scanf("%d", &timeOfpr[i]);
		}
		printf_s("____________________\n");
		break;
	case '2':
		fscanf(f, "%d", &quantOfpr);
		id = (int*)malloc(sizeof(int) * quantOfpr);
		timeOfpr = (int*)malloc(sizeof(int) * quantOfpr);
		result = (int*)malloc(sizeof(int) * quantOfpr);
		for (int i = 0; i < quantOfpr; i++) {
			id[i] = i + 1;
			fscanf(f, "%d", &timeOfpr[i]);
		}
		break;
	case '3':
		srand(time(0));
		quantOfpr = 5 + rand() % 46;
		id = (int*)malloc(sizeof(int) * quantOfpr);
		timeOfpr = (int*)malloc(sizeof(int) * quantOfpr);
		result = (int*)malloc(sizeof(int) * quantOfpr);
		for (int i = 0; i < quantOfpr; i++) {
			id[i] = i + 1;
			timeOfpr[i] =1 + rand() % 50;
		}
		break;
	default: exit(0);
	}
	fclose(f);


	printf_s("Номер процесса: ");
	for (int i = 0; i < quantOfpr; i++) {
		printf_s("%-3d", id[i]);
	}
	printf_s("\n");
	printf_s("Время процесса: ");
	for (int i = 0; i < quantOfpr; i++) {
		printf_s("%-3d", timeOfpr[i]);
	}
	printf_s("\n____________________\n");

	while (true) {
		iter++;
		printf_s("________________________________________________________________________________\n");
		if (quantOfpr > 20) fprintf(in,"________________________________________________________________________________\n");
		printf_s("Введите квант времени: ");
		scanf_s("%d", &quantumOfTime);
		if ((quantumOfTime+remainTime) < min(timeOfpr, quantOfpr)) {
			sumTime += quantumOfTime;
			procTime += quantumOfTime;
			remainTime = sumTime;
			printf_s("Номер Итерации: %-3d Квант времени: %-4d  Время цп: %-4d Номер процессора: -- Время выбранного процесса: -- Оставшееся время %-4d|\n", iter, quantumOfTime, sumTime, remainTime);
			if (quantOfpr>20) fprintf(in,"Номер Итерации: %-3d Квант времени: %-4d  Время цп: %-4d Номер процессора: -- Время выбранного процесса: -- Оставшееся время %-4d|\n", iter, quantumOfTime, sumTime, remainTime);
			continue;
		}
		sumTime += quantumOfTime;
		procTime += quantumOfTime;
		while (sumTime >= min(timeOfpr, quantOfpr)) {
			for (int i = 0; i < quantOfpr; i++) {
				if ((minpr >= (sumTime - timeOfpr[i])) && (sumTime >= timeOfpr[i])) {
					minpr = sumTime - timeOfpr[i];
					procces = i;
				}
			}
			remainTime = sumTime - timeOfpr[procces];
			result[iR] = id[procces];
			iR++;
			if(quantOfpr<21) printf_s("Номер Итерации: %-3d Квант времени: %-4d  Время цп: %-4d Номер процесса: %-3d Время выбранного процесса: %-4d Оставшееся время %-4d|\n", iter, quantumOfTime, procTime, procces, timeOfpr[procces], remainTime);
			else fprintf(in,"Номер Итерации: %-3d Квант времени: %-4d  Время цп: %-4d Номер процесса: %-3d Время выбранного процесса: %-4d Оставшееся время %-4d|\n", iter, quantumOfTime, procTime, procces, timeOfpr[procces], remainTime);
			procTime -= timeOfpr[procces];
			sumTime -= timeOfpr[procces];
			timeOfpr[procces] = _CRT_INT_MAX;
			minpr = _CRT_INT_MAX;
		}
		printf_s("________________________________________________________________________________\n");
		if (quantOfpr > 20) fprintf(in,"________________________________________________________________________________\n");
		check = 0;
		for (int i = 0; i < quantOfpr; i++) {
			if (timeOfpr[i] == _CRT_INT_MAX) {
				check++;
			}
		}
		if (check == quantOfpr) break;
	}
	printf_s("\n________________________________________________________________________________\n");
	printf_s("Результат: ");
	for (int i = 0; i < quantOfpr; i++) {
		printf_s("%d   ", result[i]);
		if(quantOfpr>20) fprintf(in,"%d   ", result[i]);
	}
	fclose(in);
}

int min(int* arr, int size) {
	int min = arr[0];
	for (int i = 1; i < size; i++) {
		if (arr[i] < min) min = arr[i];
	}
	return min;
}