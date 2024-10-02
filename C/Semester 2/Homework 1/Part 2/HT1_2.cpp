#include <iostream>
#include <locale.h>
#include <conio.h>

void printNumber(int x, int xi) {
    printf("%d + %di\n", x, xi);
}

void getNumber(int *x, int *xi, int k) {
    puts("Введите комплексное число (сначала действительная, потом мнимая часть)");
    printf("Действительная: ");
    scanf_s("%d", &*(x + k));
    printf("+ мнимая: ");
    scanf_s("%d", &*(xi + k));
    printf("Полученное число: ");
    printNumber(*(x + k), *(xi + k));
}

void printNumbers(int* x, int* xi, int k) {
    for (int i = 0; i < k; i++) {
        printf("%d: ", i + 1);
        printNumber(*(x + i), *(xi + i));
    }
}

void sumNumbers(int* x, int* xi, int k) {
    printf("Номера чисел, которые вы хотите сложить >> ");
    int one, two;
    scanf_s("%d %d", &one, &two);
    if (one >= k || two >= k || one <= 0 || two <= 0)
        puts("Ошибка ввода, числа с таким номером не существует");
    else {
        int a = *(x + one - 1) + *(x + two - 1);
        int ai = *(xi + one - 1) + *(xi + two - 1);
        printf("Сумма чисел %d + %di и %d + %di = ", *(x + one - 1), *(xi + one - 1), *(x + two - 1), *(xi + two - 1));
        printNumber(a, ai);
    }
}

void minusNumbers(int* x, int* xi, int k) {
    printf("Номера чисел, которые вы хотите вычесть (уменьшаемое и вычитаемое) >> ");
    int one, two;
    scanf_s("%d %d", &one, &two);
    if (one >= k || two >= k || one <= 0 || two <= 0)
        puts("Ошибка ввода, числа с таким номером не существует");
    else {
        int a = *(x + one - 1) - *(x + two - 1);
        int ai = *(xi + one - 1) - *(xi + two - 1);
        printf("Разность чисел %d + %di и %d + %di = ", *(x + one - 1), *(xi + one - 1), *(x + two - 1), *(xi + two - 1));
        printNumber(a, ai);
    }
}

void multNumber(int* x, int* xi, int k) {
    printf("Какое число вы хотите умножить? >> ");
    int i;
    scanf_s("%d", &i);
    if (i >= k || i <= 0)
        puts("Ошибка ввода, числа с таким номером не существует");
    else {
        printf("На сколько вы хотите умножить число? >> ");
        int b;
        scanf_s("%d", &b);
        int a = *(x + i - 1) * b;
        int ai = *(xi + i - 1) * b;
        printf("Полученное число: (%d + %di) * %d = ", *(x + i - 1), *(xi + i - 1), b);
        printNumber(a, ai);
    }
}

int main()
{
    setlocale(0, "rus");
    printf("Сколько чисел вы хотите использовать? >> ");
    int n;
    scanf_s("%d", &n);
    if (n <= 0) {
        puts("Окончание работы программы. Для завершения нажмите любую клавишу...");
        _getch();
    }
    else {
        int* numbers = new int[n];
        int* numbersI = new int[n];
        int count = 0;
        bool exit = false;
        while (!exit) {
            puts("\nЧто вы хотели бы сделать?");
            puts("1 - Ввести новое число в массив");
            puts("2 - Вывести все числа по порядку");
            puts("3 - Сложить два числа");
            puts("4 - Вычесть два числа");
            puts("5 - Умножить число на скаляр");
            puts("6 - Выход");
            printf(">> ");

            int a;
            scanf_s("%d", &a);
            switch (a) {
            case 1:
                if (count == n)
                    puts("Вы уже ввели максимальное количество чисел!");
                else {
                    getNumber(numbers, numbersI, count);
                    count++;
                }
                break;
            case 2:
                if (count == 0) puts("В массиве нет чисел");
                else printNumbers(numbers, numbersI, count);
                break;
            case 3:
                if (count == 0) puts("В массиве нет чисел");
                else sumNumbers(numbers, numbersI, count);
                break;
            case 4:
                if (count == 0) puts("В массиве нет чисел");
                else minusNumbers(numbers, numbersI, count);
                break;
            case 5:
                if (count == 0) puts("В массиве нет чисел");
                else multNumber(numbers, numbersI, count);
                break;
            case 6:
                exit = true;
                break;
            default:
                puts("Ошибка ввода");
            }
        }
        delete[]numbers;
        delete[]numbersI;
    }
    return 0;
}