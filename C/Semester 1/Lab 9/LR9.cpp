#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	srand((unsigned)time(NULL));
	setlocale(0, "rus");
	FILE *f,*g;
	int k, n;
	char s[80];
	char symbol = 'A';
	puts("Введите количество строк для первого файла:");
	scanf("%d", &n);
	f = fopen("first.dat", "w+");
	for (int i = 0; i < n; i++)
	{
		k = rand() % 20 + 1;
		for (int j = 0; j < k; j++)
		{
			s[j] = symbol;
		}
		s[k] = '\0';
		symbol++;
		fputs(s, f);
		fputs("\n", f);
	}

	puts("\nФайл F состоит из строк:");
	rewind(f);
	while (fgets(s, 80, f) != NULL)
		printf(s);

	rewind(f);
	g = fopen("second.dat", "w+");
	for (int i = 0; i < n; i++)
	{
		fgets(s, 80, f); 
		if (i % 2 == 0) {
			fputs(s, g);
		}
	}

	puts("\nФайл G состоит из строк:");
	rewind(g);
	while (fgets(s, 80, g) != NULL)
		printf(s);
	fclose(g);
	fclose(f);
	puts("Нажмите любую клавишу для завершения...");
	_getch();
	return 0;
}
