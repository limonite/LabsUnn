#include <stdio.h>
#include <conio.h>
#include <locale.h>

int prime(long N)
{
    long j;
    if (N < 4) return 1;
    if (N % 2 == 0) return 0;
    for (j = 3; j * j <= N; j += 2)
        if (N % j == 0) return 0;
    return 1;
}

int main() {
    int number, summand1, summand2;

    setlocale(LC_ALL, "Russian");

    do{
        fflush(stdin);
        number = 0;
        printf_s("Введите чётное неотрицательное число: ");
        if (!scanf_s("%d", &number)) {
            printf_s("Вы ввели не число! ");
            number=getchar()== '\0';
        }
    } while ((number <= 0) || (number % 2 == 1)||(number == '\0'));

    printf_s("Все разложения числа  на сумму двух простых чисел: \n");
    for (summand1 = 1; summand1 < number / 2; summand1++) {
        summand2 = number - summand1;
        if ((prime(summand1) == 1) & (prime(summand2) == 1)) {
            printf_s("%d = %d + %d\n", number, summand1, summand2);
        }
    }
    _getch();
    return 0;
}