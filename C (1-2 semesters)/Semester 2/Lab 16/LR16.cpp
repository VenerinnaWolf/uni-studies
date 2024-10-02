#include <iostream>
#include <locale.h>
#include <ctime>
#include <cstdlib>
#include <conio.h>

int sumOtr(int* a, int n);
void sumOtrProc(int* a, int n, int &sum);

int sumOtr(int* a, int n) {
    if (n == 0) { //Базисное утверждение
        return 0;
    }
    else { //Рекурсивное утверждение
        if (*(a) < 0) return *(a)+sumOtr(a + 1, n - 1);
        else return sumOtr(a + 1, n - 1);
    }
}

void sumOtrProc(int* a, int n, int& sum) {
    if (n == 0) { //Базисное утверждение
        sum = 0;
    }
    else { //Рекурсивное утверждение
        if (*(a) < 0) {
            sumOtrProc(a + 1, n - 1, sum);
            sum += *(a);
        }
        else sumOtrProc(a + 1, n - 1, sum);
    }
}

int main()
{
    setlocale(0, "rus");
    srand(time(NULL));
    int n;
    puts("Введите размер массива n:");
    scanf_s("%d", &n);
    int* a = new int[n];
    puts("Полученный массив:");
    for (int i = 0; i < n; i++) {
        *(a + i) = rand() % 100 - 50;
        printf("%4d", *(a + i));
    }
    int sum = sumOtr(a, n);
    if (sum == 0) puts("\nОтрицательных элементов нет (функция)");
    else printf("\nСумма отрицательных (функция) = %d", sum);
    sum = 0;
    sumOtrProc(a, n, sum);
    if (sum == 0) puts("\nОтрицательных элементов нет (процедура)");
    else printf("\nСумма отрицательных (процедура) = %d", sum);
    delete[]a;
    _getch();
    return 0;
}