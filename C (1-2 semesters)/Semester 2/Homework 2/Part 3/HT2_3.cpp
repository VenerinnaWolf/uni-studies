#define _CRT_SECURE_NO_WARNINGS

#include <conio.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
//максимальная длина строки
const int MaxLengthLine = 300;

struct binTree {
	char* value;
	char* type;
	binTree* left;
	binTree* right;
};

//Приоритет операции ch
int priority(char ch) {
	switch (ch) {
		//для операций '+' и '-' приоритет - 1
	case '+':
	case '-':
		return 1;
		//для операций '*' и '/' приоритет - 2
	case '*':
	case '/':
		return 2;
	}
	//для остальных символов приоритет - 100 (самый большой)
	return 100;
}

//Проверка, находится ли построка от first до last строки st в скобках (Если да, то такая строка - "плохая")
bool inBrackets(char* st, int first, int last) {
	bool bad = true; //Предполагаем, что строка - плохая
	int nest = 0; //Счётчик кол-ва скобок
	char* ptr = st + first;
	while (ptr != (st + last + 1)) { 
		if (*ptr == '(')
			nest++;
		if (nest == 0)
			bad = false;
		if (*ptr == ')')
			nest--;
		ptr++;
	}
	return bad;
}

//Создание бинарного дерево по строке st начиная с позиции first до позиции last
binTree* makeTree(char* st, int first, int last) {
	//Проверяем строку на наличие обрамляющих скобок:
	//Если таких скобок нет, то:
	if (!inBrackets(st, first, last)) {
		binTree* TreePointer = new binTree;
		binTree* Tree = TreePointer;
		int nest = 0;
		//Если указатели совпадают, то есть мы дошли до операнда
		if (first == last) {
			//Определяем и записываем тип содержимого (либо целое число, либо переменная)
			Tree->type = new char[MaxLengthLine];
			if (strchr("0123456789", *(st + first)) != NULL)
				strcpy(Tree->type, "int");
			else
				strcpy(Tree->type, "var");
			Tree->value = new char;
			*(Tree->value) = *(st + first);
			Tree->left = NULL;
			Tree->right = NULL;
			return Tree;
		}
		//Если мы ещё не дошли до операнда (пока находимся на операции), то:
		//Ищем самую правую операцию с минимальным приоритетом, не учитывая операции в скобках
		char* minOper = st + first;
		for (int i = first; i <= last; ++i) {
			if (*(st + i) == '(')
				nest++;
			else if (*(st + i) == ')')
				nest--;
			if ((nest == 0) && (priority(*(st + i)) <= priority(*minOper)))
				minOper = st + i;
		}
		Tree->type = new char[MaxLengthLine];
		strcpy(Tree->type, "operation");
		Tree->value = new char;
		*(Tree->value) = *minOper;
		Tree->left = makeTree(st, first, ((minOper - st) - 1));
		Tree = TreePointer;
		Tree->right = makeTree(st, ((minOper - st) + 1), last);
		Tree = TreePointer;
	}
	//Если же такие скобки есть, то создаём дерево из строки без блокирующих скобок:
	else
		return makeTree(st, first + 1, last - 1);
}

// Печать при прямом обходе бинарного дерева
void PrefPrintTree(binTree* root) {
	if (root != NULL) {
		printf("%c", *(root->value)); 
		PrefPrintTree(root->left);
		PrefPrintTree(root->right);
	}
}

// Печать при обратном обходе бинарного дерева
void PostPrintTree(binTree* root) {
	if (root != NULL) { 
		PostPrintTree(root->left); 
		PostPrintTree(root->right); 
		printf("%c", *(root->value)); 
	}
}

// Печать при симметричном обходе бинарного дерева (со всеми скобками)
void SimPrintTree(binTree* root) {
	if (root != NULL) { 
		if ((strcmp(root->type, "operation") == 0) && (priority(*(root->value)) >
			priority(*(root->left->value)))) {
			//выводим левое поддерево в скобках
			printf("(");
			SimPrintTree(root->left);
			printf(")");
		}
		else
			//выводим левое поддерево без скобок
			SimPrintTree(root->left);
		//выводим корень
		printf("%c", *(root->value));
		
		if ((strcmp(root->type, "operation") == 0) && ((priority(*(root->value)) >
			priority(*(root->right->value))) || (((*(root->value) == '-') || (*(root->value) == '/')) && ((strcmp(root->right->type, "operation") == 0) && (priority(*(root->value)) == priority(*(root->right->value))))))) {
			//выводим правое поддерево в скобках
			printf("(");
			SimPrintTree(root->right);
			printf(")");
		}
		else
			//выводим правое поддерево без скобок
			SimPrintTree(root->right);
	}
}

// Количество переменных в дереве Tree
int countVariables(binTree* Tree) {
	if (Tree != NULL) { 
		if (strcmp(Tree->type, "var") == 0) return countVariables(Tree->left) + countVariables(Tree->right) + 1;
		else return countVariables(Tree->left) + countVariables(Tree->right);
	} else return 0;
}

// Ввод переменных дерева Tree вручную в массив arr, если они не определены в массиве arrUse
void inputCustomVariables(binTree* Tree, double* arr, bool** arrUse) {
	if (Tree != NULL) {
		//вводим переменные левого поддерева
		inputCustomVariables(Tree->left, arr, arrUse);
		//если текущая вершина - переменная и она ранее не определялась
		if ((strcmp(Tree->type, "var") == 0) && (*(*arrUse + *(Tree->value)) == false)) {
			printf("%c = ", *(Tree->value));
			scanf_s("%lf", &*(arr + *(Tree->value)));
			*(*arrUse + *(Tree->value)) = true;
		}
		//вводим переменные правого поддерева
		inputCustomVariables(Tree->right, arr, arrUse);
	}
}

//Ввод переменных дерева Tree случайным образом в массив arr, если они не определены в массиве arrUse
void inputRandVariables(binTree* Tree, double* arr, bool** arrUse) {
	if (Tree != NULL) {
	//вводим переменные левого поддерева
		inputRandVariables(Tree->left, arr, arrUse);
		//если текущая вершина - переменная и она ранее не определялась
		if ((strcmp(Tree->type, "var") == 0) && (*(*arrUse + *(Tree->value)) == false)) {
			//генерируем случайное значение и записываем его в переменную
			*(arr + *(Tree->value)) = (rand() % (40 * 100) - 20 * 100.0) / 100.0;
			printf("%c = %7.2lf.\n", *(Tree->value), *(arr + *(Tree->value)));
			*(*arrUse + *(Tree->value)) = true;
		}
		//вводим переменные правого поддерева
		inputRandVariables(Tree->right, arr, arrUse);
	}
}

// Вычисление значения выражения
double calculation(binTree* Tree, double* arr, bool& notDevByZero) {
	//пока ошибок нет (пока всё правильно)
	if (notDevByZero) {
		//если текущая вершина - операция
		if (strcmp(Tree->type, "operation") == 0) {
			if (*(Tree->value) == '+')
				return calculation(Tree->left, arr, notDevByZero) + calculation(Tree->right, arr,
					notDevByZero);
			else if (*(Tree->value) == '-')
				return calculation(Tree->left, arr, notDevByZero) - calculation(Tree->right, arr,
					notDevByZero);
			else if (*(Tree->value) == '*')
				return calculation(Tree->left, arr, notDevByZero) * calculation(Tree->right, arr,
					notDevByZero);
			else if (*(Tree->value) == '/') {
				if (calculation(Tree->right, arr, notDevByZero) != 0)
					return calculation(Tree->left, arr, notDevByZero) / calculation(Tree->right, arr, notDevByZero);
				else
					//делить на ноль нельзя!
					notDevByZero = false;
			}
		}
		//если текущая вершина - число
		else if (strcmp(Tree->type, "int") == 0)
			return atof(Tree->value);
		//если текущая вершина - переменная
		else if (strcmp(Tree->type, "var") == 0) {
			return *(arr + *(Tree->value));
		}
	}
	//если элементов вышеуказанных типов нет, то возвращаем ноль
	else
		return 0;
}

// Удаление всех унарных знаков из строки
char* deleteUnarOperators(char* st) {
	char* strRes = new char[MaxLengthLine];
	*strRes = '\0';
	//Преобразуем унарные операции в начале строки в аналогичные выражения
	if (strchr("-+", *st) != NULL)
		strcat(strRes, "0");
	if (strchr("*/", *st) != NULL)
		strcat(strRes, "1");
	char* ptr = st + 1; //указатель - счётчик (для цикла)
	char* promStr = new char[MaxLengthLine]; //промежуточная строка
	char* first = st; //указатель, от которого выделяется промежуточная строка
	while (*ptr != '\0') { //Идём в цикле до конца строки
	//Если находим 2 подряд идущих символа вида "(-"
		if ((strchr("-+*", *ptr) != 0) && (*(ptr - 1) == '(')) {
			//копируем в промежуточную строку символы от first до скобки включительно
			strncpy(promStr, first, (ptr - first));
			*(promStr + (ptr - first)) = '\0';
			//присоединяем промежуточную строку к строке результата
			strcat(strRes, promStr);
			//в зависимости от знака присоединяем нужную цифру
			if (strchr("-+", *ptr) != 0)
				strcat(strRes, "0");
			else
				strcat(strRes, "1");
			//перемещаем указатель first на операцию (там, где ptr)
			first = ptr;
		}
		//Если 2 идущих подряд символа не операции и 1-ый не открывающая скобка, а 2 - ой не закрывающая скобка, то:
		if ((strchr("-+*/)", *ptr) == 0) && (strchr("-+*/(", *(ptr - 1)) == 0)) {
			//копируем в промежуточную строку символы от first до первого символа
			strncpy(promStr, first, (ptr - first));
			*(promStr + (ptr - first)) = '\0';
			//присоединяем промежуточную строку к строке результата
			strcat(strRes, promStr);
			//присоединяем знак умножения к строке результата
			strcat(strRes, "*");
			//перемещаем указатель first на второй символ (там, где ptr)
			first = ptr;
		}
		//переходим к следующему символу
		ptr++;
	}
	//присоединяем к строке результата оставшиеся символы
	strcat(strRes, first);
	return strRes; //возвращаем строку результата
}

// Удаление дерева Tree из памяти
void deleteTree(binTree* Tree) {
	if (Tree != NULL) { 
		deleteTree(Tree->left);
		deleteTree(Tree->right);
		delete Tree->type;
		delete Tree->value;
		delete Tree;
	}
}

int main()
{
	setlocale(0, "russian");
	// Ввод строки
	char* st = new char[MaxLengthLine];
	*st = '\0';
	int code;
	puts("Что вы хотели бы сделать?");
	puts("1 - Решить выражение (6-3*(z+4)+2)*(5-k) из задания");
	puts("2 - Ввести собственное выражение");
	printf(">> ");
	scanf_s("%d", &code);
	switch(code) {
	case 1:
		strcpy(st, "(6-3*(z+4)+2)*(5-k)");
		break;
	case 2:
		puts("Введите строку, удовлетворяющую правилам:");
		gets_s(st, 80);
		gets_s(st, 80);
		break;
	default:
		puts("Ошибка ввода");
		_getch();
		exit(100);
		break;
	}

	// Создание бинарного дерева
	binTree* root = NULL;
	st = deleteUnarOperators(st);
	root = makeTree(st, 0, strlen(st) - 1);

	// Вывод дерева на экран
	puts("\nПолученное дерево (префиксная запись)");
	PrefPrintTree(root);
	puts("");
	puts("Полученное дерево (инфиксная запись) с проставленными скобками");
	SimPrintTree(root);
	puts("");
	puts("Полученное дерево (постфиксная запись)");
	PostPrintTree(root);
	puts("");

	double* arr = NULL;
	bool** arrUse = NULL;
	// Ввод значений переменных
	// Если в выражении есть переменные (их кол-во больше нуля)
	if (countVariables(root) > 0) {
		printf("\nВсего переменных в выражении (в том числе и одинаковых): %d\n", countVariables(root));
		int code;
		puts("Как вы бы хотели определить переменные?");
		puts("1 - Ввести с клавиатуры");
		puts("2 - Сгенерировать случайным образом");
		printf(">> ");
		scanf_s("%d", &code);
		
		arr = new double[256]; // Массив переменных
		// Массив bool, в котором true значит, что значение переменной уже определено(имя переменной в виде числа - индекс массива), а false противоположное
		arrUse = new bool*;
		*arrUse = new bool[256];
		for (int i = 0; i < 256; i++)
			*(*arrUse + i) = false;

		// Вводим значения переменных
		switch (code) {
		case 1:
			puts("Введите значения переменных:");
			inputCustomVariables(root, arr, arrUse);
			break;
		case 2:
			srand((unsigned)time(NULL));
			puts("Сгенерированные значения переменных:");
			inputRandVariables(root, arr, arrUse);
			break;
		default:
			puts("Ошибка ввода");
			_getch();
			exit(100);
			break;
		}
	}

	//выполнение действий выражения и вывод результата вычислений
	bool flag = true;
	double res = calculation(root, arr, flag);
	if (flag) printf("\nРезультат выражения: %7.2lf\n", res);
	else puts("\nНа ноль делить нельзя!");
	deleteTree(root);
	_getch();
	return 0;
}
