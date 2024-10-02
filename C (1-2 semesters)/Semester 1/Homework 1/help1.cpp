#include <locale.h>		
#include <stdio.h>		
#include <conio.h>
#include <math.h>		

int main()
{
    double x,y,z;
    setlocale(0, "russian");
    puts("Введите x и z:");
    scanf_s ("%lf %lf", &x, &z);
    if (x == 5) puts("Ошибка, деление на ноль");
    else {
        y = sin(35.5 * z / (x - 5)) + (x * x / (2 * exp(x)));
        printf ("Y равен %14.12lf\n",y);
    }
    puts("Нажмите любую клавишу для завершения...");
    _getch();
    return 0;
}
