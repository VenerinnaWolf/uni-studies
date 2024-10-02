#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <string.h>


struct element
{
	char data;
	element* next;
};

int main()
{
	setlocale(0, "rus");

	char s[999];
	puts("Введите строку с нечетным количеством символов.");
	gets_s(s);

	if (s[0] == '\0')
		puts("Строка пуста!");
	else
	{
		element* first = NULL;

		first = new element;
		first->data = s[0];
		first->next = NULL;

		int k = 1;

		element* current = first;
		while (s[k] != '\0') {
			element* newEl = new element;
			newEl->data = s[k];
			newEl->next = NULL;
			current->next = newEl;
			current = newEl;
			k++;
		}

		puts("\nПостроенный список:");

		current = first;
		while (current != NULL) {
			printf("%c", current->data);
			current = current->next;
		}

		if (k % 2 == 0)
			puts("\nЧетное количество символов в строке!");
		else {
			printf("\nВсего символов в строке %d", k);

			if (k == 1) {
				element* newEl = new element;
				newEl->data = '#';
				newEl->next = first;
				first = newEl;
			}
			else {
				element* current = first;
				for (int i = 0; i < ((k / 2) - 1); i++) {
					current = current->next;
				}
				element* newEl = new element;
				newEl->data = '#';
				newEl->next = current->next;
				current->next = newEl;
			}

			printf("\nСредний символ %c находится под номером [%d]", s[k / 2], k / 2);
			puts("\nПолученная строка просле добавления символа # перед средним символом:");

			current = first;
			while (current != NULL) {
				printf("%c", current->data);
				current = current->next;
			}
		}

		while (first != NULL) {
			element* tmp = first;
			first = first->next;
			delete tmp;
		}
	}

	puts("\n\nНажмите любую клавишу для завершения...");
	_getch();
	return 0;
}