#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <conio.h>
#include <locale.h>
#include <io.h>

struct Telephone {
    char mark[20];
    int date;
    int amount;
    int price;
    char country[20];
};

bool fileExist;

void initInterface(char* fileName);
void showMenu();
Telephone* initElement();
void addElements(char* fileName, int number);
void deleteElement(char* fileName, int position);
void displayFile(char* fileName);
void displayTelephone(Telephone* phone);
void findElement(char* fileName, char* mark, char* country);
void howMuchPhones(char* fileName, int money);
void summarizeByDate(char* fileName, int date);

void showMenu() {
    puts("Что вы хотели бы сделать?");
    puts("1 - Добавить элементы в базу данных");
    puts("2 - Удалить элемент из базы данных");
    puts("3 - Вывести базу данных на экран");
    puts("4 - Найти элемент в базе данных (Есть ли некоторая марка производства некоторой страны?)");
    puts("5 - У меня есть некоторая сумма денег. Сколько телефонов я смогу купить?");
    puts("6 - На какую общую сумму поступили товары, начиная с указанной даты?");
    puts("7 - Выход из программы");
    puts("8 - Показать меню");
}

void initInterface(char* fileName) {
    bool exit = false;
    showMenu();
    while (!exit) {
        printf("\n>> ");
        int a;
        scanf_s("%d", &a); 
        getchar();
        switch (a) {
        case 1:
            puts("Сколько элементов вы хотите добавить в базу данных?");
            int number;
            scanf_s("%d", &number);
            getchar();
            if (number <= 0) puts("Ошибка ввода. Число должно быть больше 0");
            else addElements(fileName, number);
            break;
        case 2:
            puts("Введите номер элемента, который вы хотите удалить");
            int posintion;
            scanf_s("%d", &posintion);
            deleteElement(fileName, posintion);
            break;
        case 3:
            displayFile(fileName);
            break;
        case 4:
            puts("Какую марку вы ищете?");
            char mark[20];
            gets_s(mark);
            puts("Какая страна производства?");
            char country[20];
            gets_s(country);
            findElement(fileName, mark, country);
            break;
        case 5:
            puts("Сколько у вас имеется денег?");
            int money;
            scanf_s("%d", &money);
            howMuchPhones(fileName, money);
            break;
        case 6:
            puts("С какой даты начинать отсчет?");
            int date;
            scanf_s("%d", &date);
            summarizeByDate(fileName, date);
            break;
        case 7:
            exit = true;
            break;
        case 8:
            showMenu();
            break;
        default:
            puts("Ошибка ввода. Для вывода меню нажмите (8)");
            break;
        }
    }
}

Telephone* initElement() {
    Telephone* phone = new Telephone;
    puts("Введите информацию о новом элементе:");
    printf("Марка телефона: ");
    gets_s(phone->mark);
    printf("Дата поступления: ");
    scanf_s("%d", &phone->date);
    if (phone->date <= 0) {
        while (phone->date <= 0) {
            puts("Дата должна быть положительным числом. Введите снова");
            scanf_s("%d", &phone->date);
        }
    }
    printf("Количество телефонов: ");
    scanf_s("%d", &phone->amount);
    if (phone->amount <= 0) {
        while (phone->amount <= 0) {
            puts("Количество телефонов должно быть положительным числом. Введите снова");
            scanf_s("%d", &phone->amount);
        }
    }
    printf("Установленная цена: ");
    scanf_s("%d", &phone->price); 
    if (phone->price <= 0) {
        while (phone->price <= 0) {
            puts("Цена должна быть положительным числом. Введите снова");
            scanf_s("%d", &phone->price);
        }
    }
    printf("Страна-производитель: ");
    getchar();
    gets_s(phone->country);
    return phone;
}

void addElements(char* fileName, int number) {
    FILE* f = fopen(fileName, "ab"); 
    if (f == NULL)
    {
        puts("Невозможно отрыть файл для записи");
        _getch();
        exit(100);
    }
    int BufSize = sizeof(Telephone);
    Telephone* newPhone = (Telephone*)malloc(BufSize);
    for (int i = 0; i < number; i++) {
        newPhone = initElement();
        fwrite(newPhone, BufSize, 1, f);
    }
    free(newPhone);
    fclose(f);
    if (!fileExist) fileExist = true;
}

void deleteElement(char* fileName, int position) {
    FILE* f = fopen(fileName, "r+b"); 
    if (f == NULL || !fileExist) {
        puts("Файл для удаления элементов пуст");
    }
    else {
        int DescriptorFile = _fileno(f);
        int BufSize = sizeof(Telephone);
        Telephone* phone = (Telephone*)malloc(BufSize);
        fseek(f, position * BufSize, SEEK_SET);
        while (fread(phone, BufSize, 1, f) != 0)
        {
            fseek(f, -2 * (long)BufSize, SEEK_CUR);
            fwrite(phone, BufSize, 1, f);
            fseek(f, (long)BufSize, SEEK_CUR);
        }
        DescriptorFile = _chsize(DescriptorFile, _filelength(DescriptorFile) - BufSize);
        printf("Элемент под номером %d был удален\n", position);
        free(phone);
    }
    rewind(f);
    if (getc(f) == EOF) fileExist = false;
    fclose(f);
}

void displayFile(char* fileName) {
    FILE* f = fopen(fileName, "rb");
    if (f == NULL || !fileExist) {
        puts("Файл пуст");
    }
    else {
        int BufSize = sizeof(Telephone);
        Telephone* phone = (Telephone*)malloc(BufSize);
        printf("      Марка телефона     Дата поступления           Количество            Стоимость               Страна\n");
        while (fread(phone, BufSize, 1, f) != 0)
        {
            displayTelephone(phone);
        }
        free(phone);
    }
    fclose(f);
}

void displayTelephone(Telephone* phone) {
    printf("%20s %20d %20d %20d %20s\n",phone->mark,phone->date,phone->amount,phone->price,phone->country);
}

void findElement(char* fileName, char* markSearched, char* countrySearched) {
    FILE* f = fopen(fileName, "rb");
    if (f == NULL || !fileExist) {
        puts("Файл для поиска элементов пуст");
    }
    else {
        int BufSize = sizeof(Telephone);
        Telephone* phone = (Telephone*)malloc(BufSize);
        bool found = false;
        while (fread(phone, BufSize, 1, f) != 0 && !found)
        {
            if (strcmp(phone->mark, markSearched) == 0 && strcmp(phone->country, countrySearched) == 0) {
                printf("Да, в магазине есть телефон марки %s производства страны %s\n", markSearched, countrySearched);
                found = true;
            }
        }
        if (!found) printf("Нет, в магазине нет телефона марки %s производства страны %s\n", markSearched, countrySearched);
        free(phone);
    }    
    fclose(f);
}

void howMuchPhones(char* fileName, int money) {
    FILE* f = fopen(fileName, "rb"); 
    if (f == NULL || !fileExist) {
        puts("Файл для поиска элементов пуст");
    }
    else {
        int BufSize = sizeof(Telephone);
        Telephone* phone = (Telephone*)malloc(BufSize);
        bool iCanBuy = false;
        while (fread(phone, BufSize, 1, f) != 0)
        {
            int amount = money / phone->price;
            if (amount > 0) {
                printf("%d телефонов марки %s\n", amount, phone->mark);
                iCanBuy = true;
            }
        }
        if (iCanBuy) printf("Вы сможете купить на сумму %d\n", money);
        else printf("Вы ничего не сможете купить на сумму %d\n", money);
        free(phone);
    }    
    fclose(f);
}

void summarizeByDate(char* fileName, int date) {
    FILE* f = fopen(fileName, "rb");
    if (f == NULL || !fileExist) {
        puts("Файл для поиска элементов пуст");
    }
    else {
        int BufSize = sizeof(Telephone);
        Telephone* phone = (Telephone*)malloc(BufSize);
        int sum = 0;
        while (fread(phone, BufSize, 1, f) != 0)
        {
            if (phone->date >= date) sum += phone->price * phone->amount;
        }
        if (sum == 0) printf("Не найдено поступлений начиная с %d\n", date);
        else printf("Общая сумма товаров, поступивших после %d составляет %d\n", date, sum);
        free(phone);
    }
    fclose(f);
}

int main()
{
    setlocale(0, "rus");
    fileExist = false;
    char NameOfFile[20];
    puts("Введите название для файла базы данных:");
    gets_s(NameOfFile);
    FILE* f = fopen(NameOfFile, "wb");
    fclose(f);
    initInterface(NameOfFile);
    return 0;
}
