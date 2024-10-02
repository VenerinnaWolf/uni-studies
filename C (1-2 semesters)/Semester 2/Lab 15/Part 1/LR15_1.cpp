#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "locale.h"
#include "conio.h"
#include "string.h"
#include "cstdlib"
#include "ctime"

void makeFile(FILE* f) {
    const char symbol = 'R';
    int numOfStrings = rand() % 8 + 2;
    //Заполнение файла
    for (int i = 0; i < numOfStrings; i++) {
        int numOfWords = rand() % 10 + 1;
        int numOfSymbols = rand() % 5 + 1;
        char* word = new char[numOfSymbols + 1];
        for (int k = 0; k < numOfSymbols; k++) {
            *(word + k) = symbol;
        }
        *(word + numOfSymbols) = '\0';
        fputs(word, f);
        delete[]word;
        for (int j = 0; j < numOfWords; j++) {
            fputs(" ", f);
            numOfSymbols = rand() % 5 + 1;
            char* word = new char[numOfSymbols + 1];
            for (int k = 0; k < numOfSymbols; k++) {
                *(word + k) = symbol;
            }
            *(word + numOfSymbols) = '\0';
            fputs(word, f);
            delete[]word;
        }
        fputs("\n", f);
    }
}

void printFile(FILE* f) {
    rewind(f);
    char s[100];
    fgets(s, 100, f);
    while (!feof(f)) {
        printf("%s", s);
        fgets(s, 100, f);
    }
}

void findMinsAndDelete(FILE* original, FILE* recieved) {
    // Найдем количество строчек в оригинальном файле
    int numOfStrings = 0;
    rewind(original);
    char s[100];
    fgets(s, 100, original);
    while (!feof(original)) {
        numOfStrings++;
        fgets(s, 100, original);
    }

    // Анализ файла
    puts("");
    puts("Найдем строки, содержащие наименьшее количество слов и удалим их.");
    rewind(original);
    int minWords = 11; //Минимальное количество слов
    int* nums = new int[numOfStrings]; //Массив, содержащий количество слов в строке, чтобы можно было удалить сразу несколько строк с минимальным количеством слов
    for (int i = 0; i < numOfStrings; i++) {
        char s[100];
        fgets(s, 100, original);
        int numOfWords = 1;
        while (strchr(s, ' ') != NULL) {
            numOfWords++;
            *strchr(s, ' ') = 'B'; //Заменяю знак пробела на B
        }
        if (minWords > numOfWords) {
            minWords = numOfWords;
        }
        *(nums + i) = numOfWords;
    }
    printf("Минимальное количество слов = %d\n", minWords);
    printf("Номера строк с минимальным количеством слов: ");

    //Удаление минимальных по количеству слов строк (Создание второго файла без этих строк из первого)
    rewind(original);
    for (int i = 0; i < numOfStrings; i++) {
        char s[100];
        fgets(s, 100, original);
        if (*(nums + i) == minWords) {
            printf("%d ", i + 1);
        }
        else {
            fputs(s, recieved);
        }
    }

    delete[]nums;
}

int main()
{
    setlocale(0, "rus");
    srand(time(NULL));
    FILE* f;
    f = fopen("Text.txt", "w+");
    makeFile(f);

    //Вывод файла
    puts("Изначальный файл:");
    printFile(f);

    //Анализ файла
    FILE* g;
    g = fopen("Text1.txt", "w+");
    findMinsAndDelete(f, g);

    //Вывод полученного файла
    puts("\n");
    puts("Полученный файл после удаления строк:");
    printFile(g);

    fclose(f);
    fclose(g);
    puts("Нажмите любую клавишу для завершения...");
    _getch();
    return 0;
}