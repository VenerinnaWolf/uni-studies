#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <locale.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

// Создание файла
FILE* makeFile(int n) {
    FILE* f = fopen("Numbers.dat", "w+b");
    for (int i = 0; i < n; i++) {
        float number = float((rand() % 10 + 1)) / float((rand() % 10 + 1));
        fwrite(&number, sizeof(float), 1, f);
    }
    return f;
}

// Вычисление сумм и заполнение ими файла
FILE* countSums(FILE* f, int n) {
    FILE* g = fopen("Sums.dat", "w+b");
    rewind(f);
    for (int i = 0; i < n; i++) {
        float a, sum;
        fread(&sum, sizeof(float), 1, f);
        i++;
        fread(&a, sizeof(float), 1, f);
        sum += a;
        fwrite(&sum, sizeof(float), 1, g);
    }
    return g;
}

// Нахождение максимальной суммы
void findMaxInFile(FILE* f, int n) {
    rewind(f);
    float max = -1;
    int imax = 0;
    for (int i = 0; i < n; i++) {
        float a;
        fread(&a, sizeof(float), 1, f);
        if (a > max) {
            max = a;
            imax = i;
        }
    }
    printf("\n\nМаксимальная сумма = %f, ее номер = %d", max, imax + 1);
}

// Печать файла
void printFile(FILE* f, int n) {
    rewind(f);
    for (int i = 0; i < n; i++) {
        float a;
        fread(&a, sizeof(float), 1, f);
        printf("%f ", a);
    }
}

int main()
{
    setlocale(0, "rus");
    srand(time(NULL));

    int numOfNumbers = (rand() % 10 + 2) * 2;
    FILE* f = makeFile(numOfNumbers);
    puts("Изначальный файл");
    printFile(f, numOfNumbers);
    FILE* g = countSums(f, numOfNumbers);
    puts("\n\nФайл с суммами");
    printFile(g, numOfNumbers / 2);    
    findMaxInFile(g, numOfNumbers / 2);
    fclose(f);
    fclose(g);
    puts("\n\nНажмите любую клавишу для завершения...");
    _getch();
    return 0;
}