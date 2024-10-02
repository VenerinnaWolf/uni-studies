//Из текстового файла вводится последовательность чисел, состоящая из чисел различных знаков, разделенных пробелом.Составить программу, которая вводит строку, организует из ее чисел двунаправленный список, отсортированный по возрастанию количества цифр числа, считает общее количество чисел в списке, количество цифр которых меньше 4 и сумму двузначных чисел.Вывести на экран созданный список и всю найденную информацию с соответствующими комментариями.Если искомых чисел нет - вывести соответствующее сообщение.
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "conio.h"
#include "locale.h"
#include "string.h"

int numOfDigits(int);
char* getStringOutOfFile();
void makeList(char* s);
void printList();
void analyzeList();
void deleteList();

struct Element {
    int number;
    int numOfDigits;
    Element* next;
    Element* prev;
};

Element* first;
Element* last;

//Количество разрядов в числе
int numOfDigits(int x) {
    int num = 0;
    do {
        x = x / 10;
        num++;
    } while (x != 0);
    return num;
}

//Ввод строки из файла
char* getStringOutOfFile() {
    FILE* f;
    f = fopen("Stroka.txt", "r");
    if (f == NULL) {
        fprintf(stderr, "no file");
        _getch();
        exit(100);
    }
    puts("Откроем файл Stroka.txt и считаем из него строку с числами:");    
    if (getc(f) == EOF) {
        puts("Файл пуст!");
        _getch();
        exit(100);
    }
    rewind(f);
    char* s = new char[100];
    fgets(s, 100, f);    
    puts(s);
    puts("");
    fclose(f);
    return s;
}

//Создание списка
void makeList(char* s) {
    char* snum = strtok(s, " ");
    Element* current = first;
    while (snum != NULL) {
        //Если в списке не было элементов, создаем первый
        if (first == NULL) {
            first = new Element;
            first->number = atoi(snum);
            first->numOfDigits = numOfDigits(first->number);
            first->next = NULL;
            first->prev = NULL;
            last = first;
            //Иначе добавляем элементы в существующий список
        }
        else {
            int num = atoi(snum);
            Element* element = new Element;
            element->number = num;
            element->numOfDigits = numOfDigits(num);
            //Добавляем новый элемент в нужное место списка
            current = first;
            bool elementAdded = false;
            while (!elementAdded) {
                //Если число цифр элемента меньше текущего, то добавляем элемент до него
                if (element->numOfDigits < current->numOfDigits) {
                    //Если до текущего не было элементов (т.е. он был первым), объявляем элемент - первым
                    if (current == first) first = element;
                    //Иначе просто вставляем элемент между текущим и его предыдущим
                    else current->prev->next = element;
                    element->next = current;
                    element->prev = current->prev;
                    current->prev = element;
                    elementAdded = true;
                }
                if (!elementAdded) {
                    //Если элемент не был добавлен, то идем дальше
                    if (current != last) current = current->next;
                    //Если мы уже дошли до конца списка и все еще не добавили элемент, то добавляем его в конец
                    else {
                        last = element;
                        element->next = NULL;
                        element->prev = current;
                        current->next = element;
                        elementAdded = true;
                    }
                }
            }
            current = last;
        }
        snum = strtok(NULL, " ");
    }
}

//Вывод списка
void printList() {
    puts("Полученный отсортированный список в прямую и в обратную сторону.\n(сортировка: по возрастанию количества цифр числа):");
    Element* current = first;
    while (current != NULL) {
        printf("%d(%d) ", current->number, current->numOfDigits);
        current = current->next;
    }
    puts("");
    current = last;
    while (current != NULL) {
        printf("%d(%d) ", current->number, current->numOfDigits);
        current = current->prev;
    }
    puts("\n");
}

//Анализ списка (найти кол-во чисел в которых меньше 4 цифр и сумму двузначных)
void analyzeList() {
    int count = 0;
    int sum = 0;
    bool hasTwoDigits = false;
    Element* current = first;
    while (current != NULL) {
        if (current->numOfDigits < 4) count++;
        if (current->numOfDigits == 2) {
            sum += current->number;
            hasTwoDigits = true;
        }
        current = current->next;
    }

    if (count == 0) puts("Нет чисел, в которых меньше 4 цифр.");
    else printf("Количество чисел, в которых меньше 4 цифр = %d.\n", count);
    if (!hasTwoDigits) puts("Нет двузначных чисел.");
    else printf("Сумма двузначных чисел = %d.\n", sum);
}

//Удаление списка
void deleteList() {
    Element* current = first;
    while (current != NULL) {
        Element* tmp = current;
        current = current->next;
        delete tmp;
    }
}

int main()
{
    setlocale(0, "rus");
    char* s = getStringOutOfFile();
    first = NULL;
    last = NULL;
    makeList(s);
    printList();
    analyzeList();
    deleteList();
    delete[]s;
    puts("Введите любую клавишу для завершения...");
    _getch();
    return 0;
}
