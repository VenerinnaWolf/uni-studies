#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <math.h>
#include <conio.h>

long double y, ap, op;

int main()
{
    setlocale(0, "russian");
    y = 1;
    printf("До преобразований:   y = % 20.16Lf\n", y);
    y = y / 3;
    printf("Представление числа 1/3 в памяти:   y = % 20.16Lf\n", y);
    printf("Точное представление числа 1/3  =%20.16Lf\n", 1.0 / 3.0);
    ap = fabs(1.0 / 3 - y);    //абсолютная погрешность
    op = ap / fabs(1.0 / 3);  // относительная погрешность
    printf("Абсолютная погрешность предст. 1 / 3:   ap = % 20.16Lf\n", ap);
    printf("Относительная погрешность предст. 1 / 3:   op = % 20.16Lf\n", op);
    y = y / 6000;
    y = exp(y);
    y = sqrt(y); //Квадратный корень
    y = y / 14;
    y = 14 * y;
    y = y*y;
    y = logf(y);
    y = 6000 * y;
    y = y * 3;
    printf("После преобразований:   y = % 20.16Lf\n", y);
    ap = fabs(1 - y);  //абсолютная погрешность
    op = ap / 1; // относительная погрешность
    printf("Абсолютная погрешность:   ap = % 20.16Lf\n", ap);
    printf("Относительная погрешность:   op = % 20.16Lf\n", op);
    _getch();
    return 0;
}