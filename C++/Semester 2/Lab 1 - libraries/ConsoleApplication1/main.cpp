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
    // ����� ��������� ������� ������ ������� ������������ / ����������
    int n;
    std::cout << "������� ������ �������: ";
    std::cin >> n;
    int* array = new int[n];
    std::cout << "�������������� ������: ";
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 20 - 5;
    }
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    puts("");

    // �������� �������� dll
    if (hDLL != NULL) {
        std::cout << "\n��������� ���������� ����� �����������" << std::endl;
        // ��������� ������ ������� sort �� ����������
        void (*sort)(int*, size_t);
        sort = (void (*)(int*, size_t))(GetProcAddress(hDLL, "sort"));

        // �������� ��������� ������ ������� sort
        if (sort != NULL) {
            // ������������� �������
            // �� 5, � n, �� ���� ������������ ������������� ����� / ����������
            sort(array, n);

            // ����� ���������������� ������� �� �����
            std::cout << "��������������� ������: ";
            for (int i = 0; i < n; i++) {
                std::cout << array[i] << " ";
            }
            puts("");
        }
        else {
            std::cout << "�� ���������� ��������� ������� sort()"
                << std::endl;
        }

        // �������� ������������ ���������� �� ������
        FreeLibrary(hDLL);
    }
    else {
        std::cout << "�� ���������� ��������� ���������� DLL1.dll";
    }

    std::cout << "\n��������� ���������� ������� �����������" << std::endl;
    std::cout << "���������� ����� ������: ";
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 20 - 5;
    }
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    puts("");
    sort(array, n);
    std::cout << "��������������� ������: ";
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    puts("");

    std::cout << "\n��������� ����������� ����������" << std::endl;
    std::cout << "���������� ����� ������: ";
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 20 - 5;
    }
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    puts("");
    sortStatic(array, n);
    std::cout << "��������������� ������: ";
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }

    puts("");
    puts("\n���� �� ������� { 3, 2, 5, 0, 1 }");
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
    // ��� ������������ ������, ���������� ��� ������ array? / ����������
    delete[]array;
    return 0;    
}
