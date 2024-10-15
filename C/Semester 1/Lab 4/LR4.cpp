#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <ctime>

int main()
{
	srand(time(NULL));
	setlocale(0, "russian");
	int n;
	puts("Введите количество элементов (от 1 до 40)");
	scanf_s("%d", &n);
	int b[40];
	for (int i = 0; i < n; i++) {
		b[i] = rand() % 10 - 5;
		printf("%4d", b[i]);
	};
	int min = b[0] * b[n - 1];
	int imin = 0;
	for (int i = 0; i <= n / 2; i++) {
		if (min > b[i] * b[n - 1 - i]) {
			min = b[i] * b[n - 1 - i];
			imin = i;
		}
	};
	printf("\nНаименьшее произведение %d = %d * %d \nНомера элементов: [%d] и [%d]", min, b[imin], b[n - imin - 1], imin + 1, n - imin);
	puts("\nНажмите любую клавишу для завершения...");
	_getch();
	return 0;
}