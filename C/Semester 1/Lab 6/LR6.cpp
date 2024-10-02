#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

bool isPrime(int a) {
    bool b = 1;
    int i = 2;
    while ((b == 1) && (i <= sqrt(a))) {
        if (a % i == 0) b = 0;
        else i++;
    }
    return b;
}


int main()
{
    srand(time(0));
    setlocale(0, "russian");
    int n;
    int c[100];
    puts("Введите размер массива (от 1 до 100):");
    scanf_s("%d", &n);
    int k=0;
    puts("Массив:");
    for (int i = 0; i < n; i++) {
        c[i] = rand() % 50 + 1;
        printf("%d ", c[i]);
    }
    puts("\nНайденные простые числа:");
    for (int i = 0; i < n; i++) {
        if (isPrime(c[i])) {
            k++;
            printf("%d ", c[i]);
        }
    }
    printf("\nПростых чисел: %d", k);
    puts("\nНажмите любую клавишу для завершения...");
    _getch();
}