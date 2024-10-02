#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <conio.h>
#include <ctime>
#include <stdlib.h>

int main()
{
	setlocale(0, "russian");
	srand(time(0));
	const int m = 10;
	int a[m][m];
	int b[m]; 
	int n;
	puts("Введите размер матрицы:");
	scanf_s("%d", &n);

	for (int i = 0; i < n; i++) {
		b[i] = 0;
		for (int j = 0; j < n; j++) {
			a[i][j] = rand() % 5 - 2;
			printf("%5d", a[i][j]);
		}
		puts("\n");
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			b[i] += a[i][j];
		}
	}

	printf("Суммы элементов строк: ");
	for (int i = 0; i < n; i++) {
		printf("[%d] = %d; ", i + 1, b[i]);
	}
	puts("\n");

	bool f = false;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (b[j] == b[i]) {
				printf("Строки [%d] и [%d] имеют сумму %d\n", j+1, i+1, b[i]);
				f = true;
			}
		}
	}

	if (!f) puts("Нет строк с равными суммами элементов");
	puts("Нажмите любую клавишу для завершения...");
	_getch();
	return 0;
}