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
	const int n = 100;
	float a[n];
	int m;
	puts("Введите размер массива (от 1 до 100)");
	scanf_s("%d", &m);
	for (int i = 0; i < m; i++) {
		a[i] = (rand() % 100 - 50)/3.0;
		printf("%8.3f", a[i]);
	}
	
	bool sorted = false;
	while (!sorted) {
		sorted = true;
		for (int i = 0; i < m-1; i++) {
			if (a[i] < a[i + 1]) {
				float c = a[i];
				a[i] = a[i + 1];
				a[i + 1] = c;
				sorted = false;
			}
		}
	}

	puts("\nОтсортированный массив:");
	for (int i = 0; i < m; i++) {
		printf("%8.3f", a[i]);
	}

	puts("\nНажмите любую клавишу для завершения...");
	_getch();
}
