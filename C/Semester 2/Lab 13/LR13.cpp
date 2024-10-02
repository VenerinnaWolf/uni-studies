#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    setlocale(0, "rus");
    char* s = new char[100];
    puts("Вводите строки с числами, разделенными пробелом. Для окончания введите пустую строку");
    gets_s(s,100);
    int sum = 0;
    bool hasMax = false;
    while (s[0] != '\0') {
        char s1[10];
        int max = 0;
        int imax = 0;
        hasMax = false;
        int i = 0;
        while (i < strlen(s)) {
            int k = 0;
            while ((s[i] != '\0')&&(s[i] != ' ')) {
                s1[k] = s[i];
                i++;
                k++;
            }
            s1[k] = '\0';
            if (!hasMax) {
                max = atoi(s1);
                imax = 0;
                hasMax = true;
            } 
            else {
                if (atoi(s1) > max) {
                    max = atoi(s1);
                    imax = i - k;
                }
            }
            if (s[i] == ' ') i++;
        }
        printf("Адрес первого элемента строки = %p. Максимальное число из строки = %d. Его адрес = %p\nВведите новую строку:\n", s, max, s + imax);
        sum += max;
        gets_s(s,100);
    }
    if (!hasMax) puts("Строка не была введена");
    else printf("Сумма всех максимумов = %d\n", sum);
    delete[]s;
    puts("Для завершения нажмите любую клавишу...");
    _getch();
    return 0;
}