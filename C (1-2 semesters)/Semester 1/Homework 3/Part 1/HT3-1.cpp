#include "Header.h"
#include "masshtab.h"

#include <locale.h>
#include <stdio.h>
#include <conio.h>

int main()
{
	setlocale(0, "rus");
	puts("Введите точность вычислений:");
	float n;
	scanf_s("%f", &n);
	puts("\nВведите размер экрана B:");
	int b;
	scanf_s("%d", &b);
	printf("\nМасштаб функции x*sin(x) = %f", masshtab(f1, b, n));
	printf("\nМасштаб функции tg(x) = %f", masshtab(f2, b, n));
	puts("\nНажмите любую клавишу для завершения...");
	_getch();
	return 0;
}
