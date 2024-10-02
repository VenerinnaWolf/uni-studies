#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <stdio.h>
#include <locale.h>

int main()
{
    srand(time(NULL));
    setlocale(0, "rus");
    int n, m;
    printf("Введите размеры матрицы n и m (n<m): ");
    scanf_s("%d %d", &n, &m);

    if (n >= m) {
        puts("Ошибка ввода: n>=m");
    }
    else {
        int** a;
        a = new int* [n];
        for (int i = 0; i < n; i++) {
            *(a + i) = new int[m];
        }

        puts("Исходная матрица:");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                *(*(a + i) + j) = rand() % 100 - 50;
                printf("%4d", *(*(a + i) + j));
            }
            printf("\n");
        }

        int p, q;
        printf("Введите индексы искомого элемента p и q: ");
        scanf_s("%d %d", &p, &q);

        if ((p > n) || (q > m)) {
            puts("Ошибка ввода: элемент находится за границами матрицы");
        }
        else {
            int element = *(*(a + p) + q);
            printf("Значение искомого элемента: %d", element);
            int k = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (*(*(a + i) + j) < element) {
                        if (k==0) {
                            printf("\nАдреса элементов, которые меньше искомого:");
                        }
                        k++;
                        printf("\nАдрес (%d,%d)-го элемента: %p", i,j, *(a + i) + j);                      
                    }
                }
                printf("\n");
            }

            printf("\nВ статической матрице разность адресов первых элементов двух соседних строк была бы = %d\nВ динамической же она равна:", m * 4);
            for (int i = 0; i < n-1; i++) {
                printf("\nМежду %d и %d строками = %d", i, i + 1, int(*(a + i)) - int(*(a + i + 1)));
            }
            
            if (k == 0) {
                puts("\nНе найдено элементов, которые меньше искомого");
            }
            else {
                printf("\nКоличество элементов, меньше искомого = %d", k);
            }
        }

        for (int i = 0; i < n; i++) {
            delete[]a[i];
        }
        delete[]a;
    }
    
    puts("\nНажмите любую клавишу для завершения...");
    _getch();
    return 0;
}
