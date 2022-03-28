#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<locale.h>

typedef struct list{
	int number;
	struct list *next;
}list;

struct list *bottom  = NULL;//указатель на 1-й жлемент списка


void createList(int a) {
	list* lst = (list*)malloc(sizeof(list));
	lst->number = a;
	lst->next = NULL;
	bottom = lst;
}

void newEntryTop(int a) {
	list* lst = (list*)malloc(sizeof(list));
	list* lstprev = (list*)malloc(sizeof(list));
	lst->number = a;
	lst->next = NULL;
	lstprev = bottom;
	while (lstprev->next != NULL) {
		lstprev = lstprev->next;
	}
	lstprev->next = lst;
}

void newEntryBottom(int a) {
	list* lst = (list*)malloc(sizeof(list));
	lst->number = a;
	lst->next = bottom;
	bottom = lst;
}

void newEntryMiddle(int a) {
	list* lst = (list*)malloc(sizeof(list));
	list* lstprev = (list*)malloc(sizeof(list));
	list* lstnext = (list*)malloc(sizeof(list));
	int entry = 0;
	int i = 1;

	printf_s("После какой записи вы хотите добавить новую запись?: ");
	scanf_s("%d", &entry);
	lstprev = bottom;
	while ((lstprev->next != NULL) && (i < entry)) {
		lstprev = lstprev->next;
		i++;
	}
	lstnext = lstprev->next;
	lstprev->next = lst;
	lst->next = lstnext;
	lst->number = a;
}

int count() {
	int i = 1;
	list* lst = (list*)malloc(sizeof(list));

	lst = bottom;
	while (lst->next != NULL) {
		lst = lst->next;
		i++;
	}
	return i;
}

void viewingList() {
	list* lst = (list*)malloc(sizeof(list));
	lst = bottom;
	int i = 1;

	while (lst->next != NULL) {
		printf_s("Элемент №%d: %d\n", i, lst->number);
		i++;
		lst = lst->next;
	}
	printf_s("Элемент №%d: %d\n", i, lst->number);
}

void deleteBottom() {
	list* lst = (list*)malloc(sizeof(list));
	lst = bottom;
	bottom = lst->next;
	free(lst);
}

void deleteMiddle(int a) {
	list* lst = (list*)malloc(sizeof(list));
	list* lstprev = (list*)malloc(sizeof(list));
	lst = bottom;
	lstprev = bottom;
	int i = 1;

	while((lstprev!=NULL)&&(i<a-1)){
		lstprev = lstprev->next;
		i++;
	}
	lst = lstprev->next;
	lstprev->next = lst->next;
	free(lst);
}

void deleteTop() {
	list* lst = (list*)malloc(sizeof(list));
	list* lstprev = (list*)malloc(sizeof(list));
	lst = bottom;
	lstprev = bottom;

	while (lstprev->next->next != 0) {
		lstprev = lstprev->next;
	}
	lst = lstprev->next;
	free(lst);
	lstprev->next = NULL;
}

void deleteNum(int num) {
	list* lst = (list*)malloc(sizeof(list));
	lst = bottom;
	int i = 1;

	while ((lst != NULL)) {
		if (lst->number == num) {
			if (lst == bottom) {
				i = 1;
				deleteBottom();
				lst = bottom;
			}
			else if (lst->next == NULL) {
				deleteTop();
				break;
			}
			else {
				lst = lst->next;
				deleteMiddle(i);
			}
		}
		else {
			i++;
			lst = lst->next;
		}
	}
}



int main(void) {
	setlocale(LC_ALL, "Russian");

	int choice = 0;
	int i = 0;
	int num = 0;
	FILE* input = fopen("input.txt", "r+");

	if (input == NULL) {
		printf_s("\nФайл пуст!\n");
		exit(0);
	}

	while(!feof(input)){
		if (i == 0) {
			fscanf_s(input, "%d", &num);
			createList(num);
		}
		else {
			fscanf_s(input, "%d", &num);
			newEntryTop(num);
		}
		i++;
	}

	while (true) {
		printf_s("________________\n");
		printf_s("Взаимодействия со списком:\n1. Добавить элемент в начало списка.\n2. Добавить элемент в ""середину"" списка\n3. Добавить элемент в конец списка.\n4. Подсчитать кол-во элементов списка.\n5. Показать список.\n6. Удалить первый элемент списка.\n7. Удалить элемент из ""середины"" списка.\n8. Удалить последний элемент.\n9. Удалить элементы по заданному значению.\n(Для выхода нажмите любую другую клавишу)\nВаш выбор: ");
		scanf_s("%d",&choice);
		printf_s("________________\n");
		switch (choice) {
			case 1:
				printf_s("\n________________\n");
				printf_s("Введите число: ");
				scanf_s("%d", &num);
				newEntryBottom(num);
				printf_s("\n________________\n");
				break;
			case 2:
				printf_s("\n________________\n");
				printf_s("Введите число: ");
				scanf_s("%d", &num);
				newEntryMiddle(num);
				printf_s("\n________________\n");
				break;
			case 3:
				printf_s("\n________________\n");
				printf_s("Введите число: ");
				scanf_s("%d", &num);
				newEntryTop(num);
				printf_s("\n________________\n");
				break;
			case 4:
				printf_s("\n________________\n");
				printf_s("Кол-во записей: %d", count());
				printf_s("\n________________\n");
				break;
			case 5:
				printf_s("\n________________\n");
				viewingList();
				printf_s("\n________________\n");
				break;
			case 6:
				deleteBottom();
				break;
			case 7:
				printf_s("\n________________\n");
				printf_s("Введите номер элемента списка, который хотите удалить: ");
				scanf_s("%d", &num);
				deleteMiddle(num);
				printf_s("\n________________\n");
				break;
			case 8:
				deleteTop();
				break;
			case 9:
				printf_s("\n________________\n");
				printf_s("Введите значения элементов списка, которые хотите удалить: ");
				scanf_s("%d", &num);
				deleteNum(num);
				printf_s("\n________________\n");
				break;
			default:exit(0);
		}
	}
}