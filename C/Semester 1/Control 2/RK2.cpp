
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <ctime>

bool errors(int m, int n, int x) {
	bool b = 0;
	if (m > n) {
		puts("Некорректные данные ввода: M>N");
		b = 1;
	}
	if ((m > x) || (n > x)) {
		puts("Некорректные данные ввода: N или M превышают допустимое значение");
		b = 1;
	}
	if ((m < 1) || (n < 1)) {
		puts("Некорректные данные ввода: N или M < 1");
		b = 1;
	}
	return b;
}

int main()
{
	setlocale(0, "russian");
	srand(time(0));
	const int x = 10;
	int a[x][x];
	int n, m;
	puts("Введите количество элементов в столбце N и в строке M (от 1 до 10). N>M");
	scanf_s("%d %d", &n, &m);
	puts("\n");
	if (!errors(m, n, x)) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				a[i][j] = rand() % 100 - 50;
				printf("%4d", a[i][j]);
			}
			puts("\n");
		}
		puts("\n");

		int k = 0;
		for (int i = 0; i < n; i++) {
			k = 0;
			int b[x];
			for (int j = 0; j < m; j++) {
				if (a[i][j] % 2 == 0) {
					b[k] = a[i][j];
					k++;
				}
			}
			if (k > 3) {
				printf("Строка %d. Количество четных: %d\n", i + 1, k);
				for (int f = 0; f < k; f++) {
					printf("      Элемент %4d, его номер [%d]\n", b[f], f);
				}
			}
		}

		if (k <= 3) puts("Нет строк, в которых более трех четных элементов");
	}

	puts("\nНажмите любую клавишу для завершения...");
	_getch();
	return 0;
}
