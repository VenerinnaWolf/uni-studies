#include <iostream>
#include <conio.h>
#include <ctime>

int count;

int min(int* arr, int size) {
    count++;
    if (size == 1) { return *(arr); }
    else {
        int i = rand() % (size - 1);
        int left = min(arr, i + 1);
        int right = min(arr + i + 1, size - i - 1);
        if (left > right) return right;
        else return left;
    }
}

int main()
{
    setlocale(0, "rus");
    srand(time(NULL));
    puts("Введите размер массива");
    int n;
    scanf_s("%d", &n);
    puts("Сгенерированный массив");
    int* a = new int[n];
    for (int i = 0; i < n; i++) {
        *(a + i) = rand() % 50 - 25;
        printf("%d ", *(a + i));
    }
    count = 0;
    int result = min(a, n);
    printf("\nНаименьшее число = %d. Количество вызовов функции = %d", result, count);
    puts("\nНажмите любую клавишу для завершения...");
    _getch();
    delete[]a;
    return 0;
}