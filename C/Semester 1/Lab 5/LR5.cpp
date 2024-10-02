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
	const int n = 10;
	int a[n][n];
	double b[n];
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a[i][j] = rand() % 110 - 30;
			printf("%7d", a[i][j]);
		}
		puts("\n");
	}
	puts("\n");

	for (int j = 0; j < n; j++) {
		int k=0;
		b[j] = 0;
		for (int i = 0; i < n; i++) {
			if (a[i][j] % 3 == 0) {
				b[j] += a[i][j];
				k++;
			}
		}
		b[j] /= k;
		printf("%7.2lf",b[j]);
	}

	puts("\n\nНажмите любую клавишу для завершения...");
	_getch();
}
