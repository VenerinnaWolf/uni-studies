#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <math.h>
#include <conio.h>

double myCh(double x) {
    return (exp(x) + exp(-x)) / 2;
}

double mySh(double x) {
    return (exp(x) - exp(-x)) / 2;
}

int main()
{
    setlocale(0, "rus");
    double x;
    printf("Введите x: ");
    scanf_s("%lf", &x);
    double y1 = myCh(x);
    double y2 = mySh(x);
    double y = y1 * y1 - y2 * y2;
    double ap = fabs(1 - y);
    double op = ap / 1;
    printf("ch(x) = y1 = %20.16lf\nsh(x) = y2 = %20.16lf\ny = %20.16lf (Точное значение = 1)\nАбсолютная погрешность: ap = %20.16lf\nОтносительная погрешность: op = %20.16lf",y1,y2,y,ap,op);
    _getch();
    return 0;
}