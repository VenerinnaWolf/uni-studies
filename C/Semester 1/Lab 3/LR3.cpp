#include <locale.h>
#include <stdio.h>
#include <conio.h>


int main()
{
	setlocale(0, "russian");
	int n, k, a, b, c;
	puts("Введите число k:");
	scanf_s("%d", &k);
	puts("Нечетные числа последовательности:");
	n = 2;
	a = 1;
	b = 1;
	c = 2; 
	printf("%d %d ", a, b);
	while (c <= k) {
		if (c % 2 != 0)
		{
			n++;
			printf("%d ", c);
		}
		a = b;
		b = c;
		c = a + b;
	}
	printf("\nКоличество нечетных чисел = %d", n);
	puts("\nНажмите любую клавишу для завершения...");
	_getch();
	return 0;
}