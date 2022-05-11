#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<locale.h>

typedef struct queue {
	int num;
	queue* next;
	queue* prev;
}queue;

queue* createQueue(queue* top, int n) {
	queue* tmp = (queue*)malloc(sizeof(queue));
	tmp->next = NULL;
	tmp->prev = 0;
	tmp->num = n;
	return tmp;
}

queue* push(queue* top, int n) {
	queue* tmpnew = (queue*)malloc(sizeof(queue));
	queue* tmp = top;
	tmpnew->prev = NULL;
	tmpnew->num = n;
	while (tmp->prev) tmp = tmp->prev;
	tmpnew->next = tmp;
	tmp->prev = tmpnew;
	while (tmpnew->next) tmpnew=tmpnew->next;
	return tmpnew;
}

int count(queue* top) {
	if (!top) return 0;
	queue* tmp = top;
	int c = 0;
	while (tmp->prev) {
		c++;
		tmp = tmp->prev;
	}
	return c+1;
}

int peek(queue* top) {
	return top->num;
}

queue* pop(queue* top) {
	queue* tmp = (queue*)malloc(sizeof(queue));
	if (!top) {
		printf_s("Очередь пуста!");
		exit(0);
	}
	tmp = top->prev;
	free(top->next);
	top->next = NULL;
	return tmp;
}

bool inQueue(queue* top, int n) {
	queue* tmp = top;
	while (tmp) {
		if (tmp->num == n) return true;
		tmp = tmp->prev;
	}
	return false;
}

int main(void) {
	setlocale(LC_ALL, "Russian");

	int** procceses;
	char** result=NULL;
	int pr;
	float wait = 0, run = 0;
	int min, minId;
	int sum = 0;
	int point=0;
	int time = 0;
	int quantOfprocceses;
	char choice=NULL;
	queue* top = NULL;

	printf_s("Введите кол-во процессов: ");
	scanf_s("%d", &quantOfprocceses);
	procceses = (int**)malloc(sizeof(int*) * quantOfprocceses);
	for (int i = 0; i < quantOfprocceses; i++) procceses[i] = (int*)malloc(sizeof(int) * 2);
	for (int i = 0; i < quantOfprocceses; i++) {
		printf_s("Время процесса №%d: ", i+1);
		scanf_s("%d", &procceses[i][1]);
		procceses[i][0] = i+1;
		sum += procceses[i][1];
	}
	getchar();
	while (true) {
		printf_s("\n__________________________________________\n");
		printf_s("Выберите алгоритм обработки:\n1. FCFS\n2. SJF\nВаш выбор: ");
		scanf_s("%c", &choice);
		getchar();
		switch (choice) {
		case '1':
			result = (char**)malloc(sizeof(char*) * quantOfprocceses);
			for (int i = 0; i < quantOfprocceses; i++) {
				result[i] = (char*)malloc(sizeof(char) * sum);
				for (int j = 0; j < sum; j++) result[i][j] = '\0';
			}
		    point = 0;
			time = 0;
			wait = 0, run = 0;
			top = createQueue(top, procceses[0][0]);
			for (int i = 1; i < quantOfprocceses; i++) {
				top = push(top, procceses[i][0]);
			}
			while (top) {
				pr = peek(top);
				top = pop(top);
				for (int j = 0; j < time; j++) {
					result[pr - 1][j] = 'Г';
					wait++;
				}
				for (int j = time; j < time + procceses[pr - 1][1]; j++) {
					result[pr - 1][j] = 'И';
					run++;
				}
				time += procceses[pr-1][1];
			}
			run /= quantOfprocceses;
			wait /= quantOfprocceses;
			printf_s("   1 ");
			for (int i = 1; i < sum; i++) printf_s(" %-3d",i+1);
			printf_s("\n");
			for (int i = 0; i < quantOfprocceses; i++) {
				printf_s("%d  ",i+1);
				for (int j = 0; (result[i][j] != '\0')&&(j<sum); j++)printf_s("%c   ", result[i][j]);
				printf_s("\n");
			}
			printf_s("\nОбщее время выполнения: %d\nСреднее время выполнения:%-3.2f\nСреднее время ожидания:%-3.2f", sum, run, wait);
			break;
		case '2':
			result = (char**)malloc(sizeof(char*) * quantOfprocceses);
			for (int i = 0; i < quantOfprocceses; i++) {
				result[i] = (char*)malloc(sizeof(char) * sum);
				for (int j = 0; j < sum; j++) result[i][j] = '\0';
			}
			point = 0;
			time = 0;
			wait = 0, run = 0;
			while (count(top) != quantOfprocceses) {
				min = _CRT_INT_MAX;
				for (int i = 0; i < quantOfprocceses; i++) {
					if ((procceses[i][1] <= min) && (!inQueue(top, procceses[i][0]))) {
						minId = procceses[i][0];
						min = procceses[i][1];
					}
				}
				if (!top) top=createQueue(top, minId);
				else top=push(top, minId);
			}
			while (top) {
				pr = peek(top);
				top = pop(top);
				for (int j = 0; j < time; j++) {
					result[pr - 1][j] = 'Г';
					wait++;
				}
				for (int j = time; j < time + procceses[pr - 1][1]; j++) {
					result[pr - 1][j] = 'И';
					run++;
				}
				time += procceses[pr - 1][1];
			}
			run /= quantOfprocceses;
			wait /= quantOfprocceses;
			printf_s("   1 ");
			for (int i = 1; i < sum; i++) printf_s(" %-3d", i + 1);
			printf_s("\n");
			for (int i = 0; i < quantOfprocceses; i++) {
				printf_s("%d  ", i + 1);
				for (int j = 0; (result[i][j] != '\0') && (j < sum); j++)printf_s("%c   ", result[i][j]);
				printf_s("\n");
			}
			printf_s("\nОбщее время выполнения: %d\nСреднее время выполнения:%-3.2f\nСреднее время ожидания:%-3.2f", sum, run, wait);
			break;
		default: exit(0);
		}
	}
}