#include <locale.h>		
#include <stdio.h>		
#include <conio.h>
#include <math.h>		

int main()
{
    int a, b;
    setlocale(0, "russian");
    puts("Введите a и b:");
    scanf_s("%d %d", &a, &b);
    if (a > b)
        puts("Введенные данные некорректны");
    else
        if (a * a * a * a != a)
            if (b != 1)
                printf("f(x) имеет разрыв на границе a = %d и b = %d\n", a, b);
            else
                printf("f(x) имеет разрыв на границе a = %d\n", a);
        else
            if (b != 1)
                printf("f(x) имеет разрыв на границе b = %d\n", b);
            else
                puts("Функция непрерывна");
    puts("Нажмите любую клавишу для завершения...");
    _getch();
    return 0;
}
