#include <iostream>
#include <windows.h>
#include <locale.h>
#include <ctime>
#include <cstdlib>

#include "../Dll1/sortlibrary.h"
#include "../Static/Static.h"

int main() {
    srand(time(NULL));
    setlocale(0, "russian");
    HINSTANCE hDLL = LoadLibrary(L"DLL1.dll");
    // ЧИСЛО ЭЛЕМЕНТОВ МАССИВА ДОЛЖЕН ВВОДИТЬ ПОЛЬЗОВАТЕЛЬ / Исправлено
    int n;
    std::cout << "Введите размер массива: ";
    std::cin >> n;
    int* array = new int[n];
    std::cout << "Сформированный массив: ";
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 20 - 5;
    }
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    puts("");

    // Проверка загрузки dll
    if (hDLL != NULL) {
        std::cout << "\nПодключим библиотеку явным связыванием" << std::endl;
        // Получение адреса функции sort из библиотеки
        void (*sort)(int*, size_t);
        sort = (void (*)(int*, size_t))(GetProcAddress(hDLL, "sort"));

        // Проверка получения адреса функции sort
        if (sort != NULL) {
            // Использование функции
            // НЕ 5, А n, НЕ НАДО ИСПОЛЬЗОВАТЬ НЕИМЕНОВАННЫЕ ЧИСЛА / Исправлено
            sort(array, n);

            // Вывод отсортированного массива на экран
            std::cout << "Отсортированный массив: ";
            for (int i = 0; i < n; i++) {
                std::cout << array[i] << " ";
            }
            puts("");
        }
        else {
            std::cout << "Не получается загрузить функцию sort()"
                << std::endl;
        }

        // Выгрузка динамической библиотеки из памяти
        FreeLibrary(hDLL);
    }
    else {
        std::cout << "Не получается загрузить библиотеку DLL1.dll";
    }

    std::cout << "\nПодключим библиотеку неявным связыванием" << std::endl;
    std::cout << "Сформируем новый массив: ";
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 20 - 5;
    }
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    puts("");
    sort(array, n);
    std::cout << "Отсортированный массив: ";
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    puts("");

    std::cout << "\nПодключим статическую библиотеку" << std::endl;
    std::cout << "Сформируем новый массив: ";
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 20 - 5;
    }
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    puts("");
    sortStatic(array, n);
    std::cout << "Отсортированный массив: ";
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }

    puts("");
    puts("\nТест на массиве { 3, 2, 5, 0, 1 }");
    int a[5] = { 3, 2, 5, 0, 1 };
    for (int i = 0; i < 5; i++) {
        std::cout << a[i] << " ";
    }
    puts("");
    sort(a, 5);
    for (int i = 0; i < 5; i++) {
        std::cout << a[i] << " ";
    }
    puts("");

    system("pause");
    // ГДЕ ОСВОБОЖДЕНИЕ ПАМЯТИ, ВЫДЕЛЕННОЙ ПОД МАССИВ array? / Исправлено
    delete[]array;
    return 0;    
}
