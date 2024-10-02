#include "Deleter.h"
#include <iostream>
#include <locale.h>
#include <ctime>
#include <cstdlib>
#include <conio.h>

void printMtrx(int** a, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%4d", *(*(a + i) + j));
		}
		puts("");
	}
}

int main()
{
	setlocale(0, "rus");
	srand(time(NULL));
	int n, m;
	printf("Введите размеры матрицы n и m: ");
	scanf_s("%d %d", &n, &m);
	int** a = new int*[n];
	for (int i = 0; i < n; i++) {
		*(a + i) = new int[m];
		for (int j = 0; j < m; j++) {
			*(*(a + i) + j) = rand() % 10 - 5;
		}
	}
	puts("Исходная матрица:");
	printMtrx(a, n, m);
	puts("");
	deleteZeros(a, n, m);
	puts("");
	puts("Полученная матрица:");
	printMtrx(a, n, m);
	puts("");

	for (int i = 0; i < n; i++) {
		delete[] * (a + i);
	}
	delete[]a;
	puts("Для завершения нажмите любую клавишу...");
	_getch();
}