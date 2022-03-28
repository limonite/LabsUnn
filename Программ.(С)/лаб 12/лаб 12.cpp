#include<locale.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

#define _CRT_SECURE_NO_WARNINGS

typedef struct orders {
	int id;
	char name[20];
	char servise[20];
	char branch[20];
	int period;
	int difficulty;
	char dateOfAdmission[12];
	struct orders* next;
}orders;
orders* head = NULL;

orders* createData(int fid, char* fname, char* fservise, char* fbranch, int fperiod, int fdifficulty, char* fdate) {
	orders* tmp = (orders*)malloc(sizeof(orders));

	tmp->id = fid;
	for (int i = 0; i < 20; i++) {
		tmp->name[i] = fname[i];
		tmp->servise[i] = fservise[i];
		tmp->branch[i] = fbranch[i];
		if (i < 12) tmp->dateOfAdmission[i] = fdate[i];
	}
	tmp->period = fperiod;
	tmp->difficulty = fdifficulty;

	tmp->next = NULL;

	return(tmp);
}

int newEntry(int fid, char* fname, char* fservise, char* fbranch, int fperiod, int fdifficulty, char* fdate) {
	if (head == NULL) {
		printf("\nСоздайте базу данных!\n");
		return 0; 
	}
	orders* tmp = (orders*)malloc(sizeof(orders));

	tmp->id = fid;
	for (int i = 0; i < 20; i++) {
		tmp->name[i] = fname[i];
		tmp->servise[i] = fservise[i];
		tmp->branch[i] = fbranch[i];
		if(i<12) tmp->dateOfAdmission[i] = fdate[i];
	}
	tmp->period = fperiod;
	tmp->difficulty = fdifficulty;

	tmp->next = NULL;

	orders* p = head;

	while (p->next != NULL) p = p->next;
	p->next = tmp;
}

int viewingDatabase() {
	if (head == NULL) {
		printf("\nСоздайте базу данных!\n");
		return 0;
	}
	orders* tmp = head;

	printf_s("\n--------------\nБаза данных:\n");
	printf_s("№  Клиент                                  Услуга              Филиал              Срок      Сложн.    Дата приёма\n");
	while (tmp != NULL)
	{
		printf_s("%-3d%-40s%-20s%-20s%-10d%-10d%-11s\n", tmp->id, tmp->name, tmp->servise, tmp->branch, tmp->period, tmp->difficulty, tmp->dateOfAdmission);
		tmp = tmp->next;
	}
	printf_s("\n--------------\n");
}

int readDatabase() {
	FILE* f = fopen("Database.txt", "r+");
	if (f = NULL) {
		printf_s("\nФайл пуст!\n");
		return 0;
	}
	int mid = 0;
	char mname[20];
	char mservice[20];
	char mbranch[20];
	int mperiod = 0;
	int mdifficulty = 0;
	char mdate[20];

	fscanf(f, "%d", &mid);
	fscanf(f, "%s", &mname);
	fscanf(f, "%s", &mservice);
	fscanf(f, "%s", &mbranch);
	fscanf(f, "%d", &mperiod);
	fscanf(f, "%d", &mdifficulty);
	fscanf(f, "%s", &mdate);
	head = createData(mid, mname, mservice, mbranch, mperiod, mdifficulty, mdate);
	for (int i = 0; i < 20; i++) {
		mname[i] = '\0';
		mservice[i] = '\0';
		mbranch[i] = '\0';
	}
	mperiod = 0;
	mdifficulty = 0;
	for (int i = 0; i < 12; i++) {
		mdate[i] = '\0';
	}

	while (!feof(f)) {
		for (int i = 0; i < 20; i++) {
			mname[i] = '\0';
			mservice[i] = '\0';
			mbranch[i] = '\0';
		}
		mperiod = 0;
		mdifficulty = 0;
		for (int i = 0; i < 12; i++) {
			mdate[i] = '\0';
		}
		fscanf(f, "%d", &mid);
		fscanf(f, "%s", &mname);
		fscanf(f, "%s", &mservice);
		fscanf(f, "%s", &mbranch);
		fscanf(f, "%d", &mperiod);
		fscanf(f, "%d", &mdifficulty);
		fscanf(f, "%s", &mdate);
		newEntry(mid, mname, mservice, mbranch, mperiod, mdifficulty, mdate);
	}
}
int saveData() {
	if (head == NULL) {
		printf("\nСоздайте базу данных!\n");
		return 0;
	}
	orders* tmp = head;
	FILE* f = fopen("Database.txt", "w+");
	int i = 0;

	while ((tmp->next) != NULL) {
		if (i=0) fprintf_s(f, "%-3d%-40s%-20s%-20s%-10d%-10d%-11s", tmp->id, tmp->name, tmp->servise, tmp->branch, tmp->period, tmp->difficulty, tmp->dateOfAdmission);
		fprintf_s(f,"\n%-3d%-40s%-20s%-20s%-10d%-10d%-11s", tmp->id, tmp->name, tmp->servise, tmp->branch, tmp->period, tmp->difficulty, tmp->dateOfAdmission);
		tmp = tmp->next;
		i++;
	}
	fclose(f);
}
orders* searchEntry(int fid) {
	if (head == NULL) return NULL;
	orders* tmp = head;
	int i = 0; 
	while (tmp->id != fid) tmp = tmp->next;
	printf_s("Запись №%d: ", fid);
	printf_s("%-3d%-40s%-20s%-20s%-10d%-10d%-11s\n", tmp->id, tmp->name, tmp->servise, tmp->branch, tmp->period, tmp->difficulty, tmp->dateOfAdmission);
	return tmp;
}
void modificate(int fid) {

	orders* tmp = searchEntry(fid);
	int chce = 0;
	printf_s("\nЧто вы хотите изменить?\n1 Фамилию\n2 Услуга\n3 Филиал\n4 Время выполнения услуги\n5 Уровень сложности\n6 Дата приёма вещей\nВаш выбор: ");
	scanf("%d", &chce);
	switch (chce) {
	case 1:
		printf_s("Введите фамилию: ");
		for(int i=0;i<20;i++)tmp->name[i] = '\0';
		while ((getchar()) != '\n');
		gets_s(tmp->name, sizeof(char) * 20);
		break;
	case 2:
		printf_s("Введите услугу: ");
		for (int i = 0; i < 20; i++)tmp->servise[i] = '\0';
		while ((getchar()) != '\n');
		gets_s(tmp->servise, sizeof(char) * 20);
		break;
	case 3:
		printf_s("Введите филиал: ");
		for (int i = 0; i < 20; i++)tmp->branch[i] = '\0';
		while ((getchar()) != '\n');
		gets_s(tmp->branch, sizeof(char) * 20);
		break;
	case 4:
		printf_s("Введите время выполнения услуги: ");
		scanf("%d", &tmp->period);
		break;
	case 5:
		printf_s("Введите сложность: ");
		scanf("%d", &tmp->difficulty);
		break;
	case 6:
		printf_s("Введите дату приёма вещей: ");
		for (int i = 0; i < 12; i++)tmp->dateOfAdmission[i] = '\0';
		while ((getchar()) != '\n');
		gets_s(tmp->dateOfAdmission, sizeof(char) * 20);
		break;
	}
}
void deleteEntry(int fid) {
	orders* tmp = searchEntry(fid);
	orders* tmpprev = head;
	if (tmp==head) {
		head = head->next;
		free(tmpprev);
	}
	else if (tmp->next == NULL) {
		for (int i = 0;(tmpprev->next)!=tmp ; i++) tmpprev = tmpprev->next;
		tmpprev->next = NULL;
		free(tmp);
	}
	else {
		for (int i = 0; (tmpprev->next)!=tmp; i++) tmpprev = tmpprev->next;
		tmpprev->next = tmp->next;
		free(tmp);
	}
	printf_s("\nЗапись удалена\n");
}

int main(void) {
	setlocale(LC_ALL, "Russian");
	int choice = 0;
	char flag;
	int mid = 0;
	char mname[20];
	char mservice[20];
	char mbranch[20];
	int mperiod = 0;
	int mdifficulty = 0;
	char mdate[20];
	int num;

	while (true) {
		printf_s("Выберите действие:\n1 Создать новую БД.\n2 Прочитать из файла существующую БД.\n3 Сохранить БД в файл.\n4 Добавить запись.\n5 Найти запись по ключу.\n6 Модифицировать БД.\n7 Просмотреть БД.\n8 Удалить запись\nВаш выбор: ");
		scanf_s("%d", &choice);
		printf_s("\n_____________________________________________________\n");
		switch (choice) {
		case 1:
			mid = 0;
			while ((getchar()) != '\n');
			printf_s("Фамилия клиента: ");
			gets_s(mname, sizeof(char) * 20);
			printf_s("Услуга: ");
			gets_s(mservice, sizeof(char) * 20);
			printf_s("Филиал: ");
			gets_s(mbranch, sizeof(char) * 20);
			printf_s("Время выполнения услуги: ");
			scanf("%d", &mperiod);
			printf_s("Уровень сложности: ");
			scanf("%d", &mdifficulty);
			printf_s("Дата приёма вещей: ");
			while ((getchar()) != '\n');
			gets_s(mdate, sizeof(char) * 12);
			head=createData(mid,mname,mservice,mbranch,mperiod,mdifficulty,mdate);
			for (int i = 0; i < 20; i++) {
				mname[i] = '\0';
				mservice[i] = '\0';
				mbranch[i] = '\0';
			}
			mperiod = 0;
			mdifficulty = 0;
			for (int i = 0; i < 12; i++) {
				mdate[i] = '\0';
			}
			break;
		case 2:
			readDatabase();
			break;
		case 3:
			saveData();
			break;
		case 4:
			mid++;
			while ((getchar()) != '\n');
			printf_s("Фамилия клиента: ");
			gets_s(mname, sizeof(char)*20);
			printf_s("Услуга: ");
			gets_s(mservice, sizeof(char) * 20);
			printf_s("Филиал: ");
			gets_s(mbranch, sizeof(char) * 20);
			printf_s("Время выполнения услуги: ");
			scanf("%d", &mperiod);
			printf_s("Уровень сложности: ");
			scanf("%d", &mdifficulty);
			printf_s("Дата приёма вещей: ");
			while ((getchar()) != '\n');
			gets_s(mdate, sizeof(char) * 12);
			newEntry(mid, mname, mservice, mbranch, mperiod, mdifficulty, mdate);
			for (int i = 0; i < 20; i++) {
				mname[i] = '\0';
				mservice[i] = '\0';
				mbranch[i] = '\0';
			}
			mperiod = 0;
			mdifficulty = 0;
			for (int i = 0; i < 12; i++) {
				mdate[i] = '\0';
			}
			break;
		case 5:
			printf_s("Введите номер записи: ");
			scanf_s("%d", &num);
			searchEntry(num);
			break;
		case 6:
			printf_s("Введите номер записи: ");
			scanf_s("%d", &num);
			modificate(num);
			break;
		case 7:
			viewingDatabase();
			break;
		case 8:
			printf_s("Введите номер записи: ");
			scanf_s("%d", &num);
			deleteEntry(num);
			break;
		default: 
			return 0;
			break;
		}
		printf_s("Продолжить работу с базой данных? (Y/N): ");
		flag = _getch();
		if ((flag == 'n') || (flag == 'N') || (flag == 'т') || (flag == 'Т')) {
			break;
		}
		else if ((flag == 'Y') || (flag == 'y') || (flag == 'н') || (flag == 'Н')) {
			printf_s("\n_____________________________________________________\n\n\n");
			continue;
		}
		return 0;
	}
}