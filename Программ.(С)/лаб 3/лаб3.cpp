#include<stdio.h>
#include<conio.h>
#include<locale.h>

int main(void) {
	setlocale(LC_ALL, "Russian");

	int d, m, g, minm, x, y,Month;
	long result;
	int day[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	do {
		printf_s("Введите год: ");
		if (!scanf_s("%d", &g)) {
			printf_s("Вы ввели не число!");
			return -1;
		}
	} while ((g > 4092) || (g < 1582));
	if (((g % 4 == 0) && (g % 100 != 0)) || (g % 400 == 0)) {
		day[1] = 29;
	}
	do {
		printf_s("Введите номер месяца: ");
		if (!scanf_s("%d", &m)) {
			printf_s("Вы ввели не число!");
			return -1;
		}
	} while ((m > 12) | (m < 1));
	do {
		printf_s("Введите день: ");
		if (!scanf_s("%d", &d)) {
			printf_s("Вы ввели не число!");
			return -1;
		}
	} while ((d > day[m-1]) || (d < 1));
	Month = m;
	if (Month >= 3) {
		Month -= 2;
	}else {
		Month+= 10;
		g -= 1;
	}
	x = g / 100;
	y = g % 100;
	result = ((int)(2.6 * Month - 0.2) + d + y + (y / 4) + (x / 4) - 2 * x)%7;
	if (result < 0) {
		result+=7;
	}
	switch (result) {
	case 0:
		printf_s("%d.%d.%d - Воскресенье",d, m, g);
		break;
	case 1:
		printf_s("%d.%d.%d - Понедельник", d, m, g);
		break;
	case 2:
		printf_s("%d.%d.%d - Вторник", d, m, g);
		break;
	case 3:
		printf_s("%d.%d.%d - Среда", d, m, g);
		break;
	case 4:
		printf_s("%d.%d.%d - Четверг", d, m, g);
		break;
	case 5:
		printf_s("%d.%d.%d - Пятница", d, m, g);
		break;
	case 6:
		printf_s("%d.%d.%d - Суббота", d, m, g);
		break;
	}
	_getch();
}