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
    printf("Введите размеры матрицы n и m (n и m не больше 10): ");
    scanf_s("%d %d", &n, &m);
    if (n > 10 || m > 10) {
        puts("Ошибка ввода: n или m больше 10");
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

        puts("\nСначала все нечетные столбцы, а рядом – все четные:");

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j += 2) {
                printf("%4d", *(*(a + i) + j));
            }
            printf("\t");
            for (int j = 1; j < m; j += 2) {
                printf("%4d", *(*(a + i) + j));
            }
            printf("\n");
        }

        for (int i = 0; i < n; i++) {
            delete[]a[i];
        }
        delete[]a;
    }

    puts("Нажмите любую клавишу для завершения...");
    _getch();
    return 0;
}
