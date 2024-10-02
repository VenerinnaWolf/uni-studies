#include <locale.h>   	 
#include <stdio.h>   	 
#include <conio.h>
#include <math.h>   	 

int main()
{
	double s, a, eps;
	long k;
	setlocale(0, "russian");
	puts("Введите точность eps:");
	scanf_s("%lf", &eps);
	a = 1;
	k = 1;
	s = a;
	while (fabs(a) > eps) {

		k++;
		a = -a * (k - 1) / k;
		s += a;
	}
	float l = log(2.0);
	printf("Результат              = %20.16lf, количество итераций = %d\nОжидаемое значение ln2 = % 20.16lf\n", s, k, l);
		puts("Нажмите любую клавишу для завершения...");
	_getch();
	return 0;
}
