#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <conio.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    setlocale(0, "rus");
    int n;
    printf("Введите размер массива: ");
    scanf_s("%d", &n);
    int* d = new int[n];
    puts("Исходный массив:");
    for (int i = 0; i < n; i++) {
        *(d + i) = rand() % 100 - 50;
        printf("%d ", *(d + i));
    }

    int sum = 0;
    int* prev = &sum;
    bool hasKrat = false;
    bool hasNeg = false;
    for (int i = 0; i < n; i++) {
        if (*(d + i) < 0) {
            hasNeg = true;
        }
        if (*(d + i) % 2 == 0) {
            if (sum == 0) {
                printf("\n\nАдреса элементов кратных 2:");
            }
            sum += *(d + i);
            printf("\nАдрес %d-го элемента: %p", i, d + i);
            if (prev != &sum) {
                printf("\tРазность между этим и предыдущим адресом = %d", int(d+i)-int(prev));
            }
            hasKrat = true;
            prev = d + i;
        }
    }

    if (!hasKrat || !hasNeg) {
        puts("\nВ массиве нет отрицательных или кратных двум элементов");
    }
    else {
        printf("\n\nСумма кратных двум = %d", sum);
        puts("\n\nИзмененный массив:");
        for (int i = 0; i < n; i++) {
            if (*(d + i) < 0) {
                *(d + i) = sum;
            }
            printf("%d ", *(d + i));
        }
    }

    delete[]d;
    _getch();
    return 0;
}
