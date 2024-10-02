#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <math.h>
#include <conio.h>


int main()
{
    setlocale(0, "rus");
    double x;
    printf("Введите x: ");
    scanf_s("%lf", &x);
    double y = sin(x) * sin(x) + cos(x) * cos(x);
    double ap = fabs(1 - y);
    double op = ap / 1;
    printf("y = %20.16lf (Точное значение = 1)\nАбсолютная погрешность: ap = %20.16lf\nОтносительная погрешность: op = %20.16lf", y, ap, op);
    _getch();
    return 0;

}