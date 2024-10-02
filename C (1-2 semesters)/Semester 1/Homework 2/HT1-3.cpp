
#include <stdio.h>
#include <locale.h>
#include <conio.h>

void sort(float *a,int m) {
	bool sorted = false;
	while (!sorted) {
		sorted = true;
		for (int i = 0; i < m - 1; i++) {
			if (a[i] > a[i + 1]) {
				float c = a[i];
				a[i] = a[i + 1];
				a[i + 1] = c;
				sorted = false;
			}
		}
	}
}

float med(float *a) {
	float b = (a[4] + a[5]) / 2;
	return b;
}

float sred(float *a, int m) {
	float s = 0;
	for (int i = 0; i < m; i++) {
		s += a[i];
	}
	s /= m;
	return s;
}

int main()
{
	setlocale(0, "russian");
	const int n = 10;
	float a[n];
	puts("Введите 10 вещественных элементов последовательности (от -99.999 до 999.999):");
	for (int i = 0; i < n; i++) {
		scanf_s("%f", &a[i]);
	}
	puts("\nИсходная последовательность:");
	for (int i = 0; i < n; i++) {
		printf("%8.3f", a[i]);
	}
	sort(a,n);
	puts("\nОтсортированная последовательность:");
	for (int i = 0; i < n; i++) {
		printf("%8.3f", a[i]);
	}
	printf("\nМедиана последовательности = %8.3f",med(a));
	float b[5] = { a[0],a[1],a[2],a[3],a[4] };
	float c[5] = { a[5],a[6],a[7],a[8],a[9] };
	printf("\nСреднее арифметическое элементов до медианы = %8.3f", sred(b,5));
	printf("\nСреднее арифметическое элементов после медианы = %8.3f", sred(c,5));

	puts("\nНажмите любую клавишу для завершения...");
	_getch();
	return 0;
}
