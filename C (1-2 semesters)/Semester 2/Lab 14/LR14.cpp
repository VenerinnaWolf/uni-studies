#include "Sort.h"
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <ctime>


int main()
{
    setlocale(0, "rus");
    srand(time(NULL));
    puts("Введите размеры матрицы n и m:");
    int n, m;
    scanf_s("%d %d", &n, &m);
    float** a;
    a = new float* [n];
    for (int i = 0; i < n; i++) {
        *(a + i) = new float[m];
    }

    puts("Изначальная матрица");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            *(*(a + i) + j) = (rand() % 100)/float(rand() % 20 + 1) - 10;
            printf("%10.6f",*(*(a + i) + j));
        }
        puts("");
    }

    for (int i = 0; i < n; i++) {
        SortStr(*(a + i), m);
    }

    puts("\nОтсортированная матрица");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%10.6f", *(*(a + i) + j));
        }
        puts("");
    }
    puts("\nАдресная арифметика");
    printf("Адрес первого элемента массива (0,0) - %p\n", *a);
    printf("Адрес второго в первой строке элемента массива (0,1) - %p\n", *(a)+1);
    printf("Адрес второго в первом столбце элемента массива (1,0) - %p\n", *(a+1));


    for (int i = 0; i < n; i++) {
        delete[]a[i];
    }
    delete[]a;

    _getch();
    return 0;
}
