#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable: 4018)

struct element
{
	int data;
	element* next;
};

int main()
{
	setlocale(0, "rus");

	char s[100], num[10];
	puts("Введите строку с числами, разделенными одним пробелом.");
	gets_s(s);

	element* first = new element;

	int l = 0; //Номер заполняемой ячейки в num. Каждый раз обновляется с новым элементом
	int k = 0; //Номер текущего элемента строки

	if (s[0] == '\0') {
		first = NULL;
	}
	else
	{
		while ((s[k] != ' ') && (s[k] != '\0')) {
			num[l] = s[k];
			k++;
			l++;
		}
		num[l] = '\0';
		first->data = atoi(num);
		first->next = NULL;
		if (s[k] != '\0')
			k++;
		l = 0;
		int dl = strlen(num);
		for (int i = 0; i < dl; i++) {
			num[i] = '\0';
		}
	}

	element* current = first;
	element* previous = NULL;
	while (s[k] != '\0') {

		//Создание нового элемента
		element* newEl = new element;
		while ((s[k] != ' ') && (s[k] != '\0')) {
			num[l] = s[k];
			k++;
			l++;
		}
		num[l] = '\0';
		newEl->data = atoi(num);
		newEl->next = NULL;
		if (s[k] != '\0')
			k++;
		l = 0;
		int dl = strlen(num);
		for (int i = 0; i < dl; i++) {
			num[i] = '\0';
		}

		//Добавление элемента в нужную часть списка
		current = first;
		bool added = false;
		while ((current != NULL) && !added) {
			if ((abs(current->data) > abs(newEl->data)) && !added) {
				if (current == first) {
					newEl->next = current;
					first = newEl;
					previous = first;
					current = previous->next;
				}
				else {
					previous->next = newEl;
					newEl->next = current;
					previous = current;
					current = current->next;
				}
				added = true;
			}
			else {
				previous = current;
				current = current->next;
			}
		}
		if (!added) {
			previous->next = newEl;
		}
	}

	puts("\nПостроенный список, отсортированный по возрастанию абсолютной величины числа:");

	current = first;
	while (current != NULL) {
		printf("%d ", current->data);
		current = current->next;
	}

	bool exit = false;

	while (!exit) {
		puts("\n\nВведите число, соответсвующее желаемой операции:");
		puts("1 --- Добавление элемента к списку");
		puts("2 --- Удаление элемента из списка");
		puts("0 --- Завершение программы");
		printf(">> ");
		int a;
		scanf_s("%d", &a);
		puts("");
		int number;

		switch (a) {
		case 1:
		{
			//Создание нового элемента
			element* newEl = new element;
			puts("Введите значение элемента:");
			printf(">> ");
			scanf_s("%d", &number);
			newEl->data = number;
			newEl->next = NULL;

			//Добавление элемента в нужную часть списка
			current = first;
			bool added = false;
			while ((current != NULL) && !added) {
				if ((abs(current->data) > abs(newEl->data)) && !added) {
					if (current == first) {
						newEl->next = current;
						first = newEl;
						previous = first;
						current = previous->next;
					}
					else {
						previous->next = newEl;
						newEl->next = current;
						previous = current;
						current = current->next;
					}
					added = true;
				}
				else {
					previous = current;
					current = current->next;
				}
			}
			if (!added) {
				if (first == NULL)
					first = newEl;
				else
					previous->next = newEl;
			}

			puts("\nСписок после добавления элемента:");

			current = first;
			while (current != NULL) {
				printf("%d ", current->data);
				current = current->next;
			}
			break;
		}
		case 2:
		{
			if (first == NULL) {
				puts("Нельзя удалить элемент из пустого списка");
				break;
			}
			puts("Введите значение элемента:");
			printf(">> ");
			scanf_s("%d", &number);
			bool found = false;
			current = first;
			previous = NULL;
			while ((current != NULL) && !found) {
				if (current->data == number) {
					if (current == first) {
						if (first->next == NULL) {
							first = NULL;
						}
						else {
							element* tmp = first;
							first = first->next;
							delete tmp;
						}
					}
					else {
						element* tmp = current;
						previous->next = current->next;
						delete tmp;
					}
					current = NULL;
					found = true;
				}
				else {
					previous = current;
					current = current->next;
				}
			}
			if (!found)
				puts("Элемент не найден.");
			else {
				puts("\nСписок после удаления элемента:");

				current = first;
				while (current != NULL) {
					printf("%d ", current->data);
					current = current->next;
				}
			}

			break;
		}
		case 0:
		{
			exit = true;
			break;
		}
		default:
		{
			puts("Некорректные данные ввода");
		}
		}

	}

	while (first != NULL) {
		element* tmp = first;
		first = first->next;
		delete tmp;
	}

	return 0;
}
