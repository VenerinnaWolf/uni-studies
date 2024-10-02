#include <locale.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	setlocale(0, "rus");
	puts("Введите текст. В конце каждого предложения точка, между словами и предложениями ровно один пробел");
	char s[999], currentSent[100], sentences[10][100];
	gets_s(s);
	int i = 0;
	int j = 0;
	int numOfWords = 0;
	int numOfSent = 0; //количество предложений, имеющих более 3 слов
	while (s[i] != '\0') {
		while (s[i] != '.') {
			currentSent[j] = s[i];
			if ((s[i] == ' ') && (s[i-1] != '.'))
				numOfWords++;
			i++;
			j++;
		}
		currentSent[j] = '\0';
		numOfWords++;
		j = 0;
		if (numOfWords > 3) {
			while (currentSent[j] != '\0') {
				sentences[numOfSent][j] = currentSent[j];
				j++;
			}
			sentences[numOfSent][j] = '\0';
			numOfSent++;
		}
		numOfWords = 0;
		i++;
		j = 0;
	}
	printf("\nКоличество предложений, имеющих более 3 слов: %d", numOfSent);
	if (numOfSent != 0) {
		puts("\nПредложения, в которых более 3 слов:");
		for (i = 0; i < numOfSent; i++) {
			puts(sentences[i]);
		}
	}
	_getch();
	return 0;
}