#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <conio.h>


int main()
{
	float x, y;
	setlocale(0, "russian");
	puts("Введите x,y: ");
	scanf_s("%f %f", &x, &y);

	if (((x - 1) * (x - 1) + (y - 1) * (y - 1)) > 1)
		puts("Точка не принадлежит окружности");
	else
		if (x < 1)
			puts("Точка находится левее заштрихованной плоскости");
		else
			if (y < 1)
				puts("Точка находится ниже заштрихованной плоскости");
			else
				puts("Точка принадлежит заштрихованной плоскости");
	puts("Нажмите любую клавишу для завершения...");
	_getch();
	return 0;
}