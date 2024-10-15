// Static.cpp : Определяет функции для статической библиотеки.
//

#include "pch.h"
#include <iostream>
#include "Static.h"

// TODO: Это пример библиотечной функции.
void sortStatic(int* a, size_t n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && a[j - 1] > a[j]; j--) {
            int tmp = a[j];
            a[j] = a[j - 1];
            a[j - 1] = tmp;
        }
    }
}
