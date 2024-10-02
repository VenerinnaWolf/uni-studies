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
	puts("Введите строку символов.");
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

		while (s[k] != '\0') {
			element* newEl = new element;
			newEl->data = s[k];
			newEl->next = first;
			first = newEl;
			k++;
		}

		puts("\nПостроенный список:");

		element* current = first;
		while (current != NULL) {
			printf("%c", current->data);
			current = current->next;
		}

		current = first;
		while (current != NULL) {
			if (current->data == 'A') {
				element* newEl = new element;
				newEl->data = '#';
				newEl->next = current->next;
				current->next = newEl;
			}
			current = current->next;
		}

		puts("\nПолученная строка просле добавления символа # после символа A (английская):");

		current = first;
		while (current != NULL) {
			printf("%c", current->data);
			current = current->next;
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
