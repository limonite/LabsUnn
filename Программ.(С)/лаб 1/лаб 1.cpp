#include <stdio.h>
#include <conio.h>
#include <locale.h>

int main(void)
{
	float summa = 0;
	float numbers[100];
	int quantOfNumbers;

	setlocale(LC_ALL, "Russian");

	printf_s("Введите количество элементов массива: \n");
	if (!scanf_s("%d", &quantOfNumbers)) {
		printf_s("Вы ввели некоректные данные");
		return -1;
	}

	printf("Заполните массив: \n");
	for (int index = 0; index < quantOfNumbers; index++) {
		printf_s("a[%d]= ", index + 1);
		if (!scanf_s("%f", &numbers[index])) {
			printf_s("Вы ввели некоректные данные");
			return -1;
		}
		summa += numbers[index];
	}

	for (int index = 0; index < quantOfNumbers; index++) {
		if (index %5 == 0) {
			printf_s("\n");
		}
		printf_s("%2d: %-12.2f ", index + 1, numbers[index]);
	}
	printf_s("\n\n");

	for (int index = 0; index < quantOfNumbers; index++) {
		printf_s("%2d: %12.2f\n", index + 1, numbers[index]);
	}
	printf_s("_____________________\n %15.2f", summa);
	_getch();
}