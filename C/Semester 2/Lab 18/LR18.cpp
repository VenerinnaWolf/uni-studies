#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <locale.h>
#include <conio.h>
#include <ctime>
#include <cstdlib>

struct Element {
    int number;
    int sumOfDigits;
    Element* right;
    Element* left;
    Element* parent;
};

enum side { right, left, none };

Element* firstElement; // Начало дерева
bool treeExist; // Дерево существует

void showMenu();
void loadInterface();
void makeTree();
int sumOfDigits(int n);
void makeNewElement(Element* newElement, int number);
void addElement(Element* curElement, Element* newElement);
int countAndPrintEven(Element* curElement);
void deleteEven(Element* curElement);
void deleteElement(Element* parentOfElementToDelete, side sideOfElementToDelete);
void printTree(Element* curElement);
void PreOrder_PrintTree(Element* curElement);
void SymmetricOrder_PrintTree(Element* curElement);
void PostOrder_PrintTree(Element* curElement);
int countNodes(Element* curElement);
int countDepth(Element* curElement);
void deleteTree(Element* curElement);

// Меню
void showMenu() {
    puts("\nЧто вы хотели бы сделать?");
    puts("1 - Создать дерево из вводимой последовательности чисел");
    puts("2 - Добавить новый элемент в дерево");
    puts("3 - Посчитать количество четных элементов в дереве и вывести их на экран. (Прямой обход дерева)");
    puts("4 - Удалить все четные элементы из дерева. (Обратный обход дерева)");
    puts("5 - Вывести дерево на экран, а также его характеристики (глубина, количество узлов)");
    puts("6 - Выйти из программы");
    puts("7 - Показать меню");
}

// Весь интерфейс программы
void loadInterface() {
    int exit = false;
    showMenu();
    while (!exit) {
        printf("\n>> ");
        int a;
        scanf_s("%d", &a);
        switch (a)
        {
        case 1:
            if (!treeExist) makeTree();
            else puts("Дерево уже существует");
            break;
        case 2:
            if (treeExist) {
                Element* newElement = new Element;
                int number;
                puts("Введите число:");
                scanf_s("%d", &number);
                makeNewElement(newElement, number);
                addElement(firstElement, newElement);
                puts("Элемент успешно добавлен в дерево");
            }
            else puts("Дерева не существует. Чтобы добавить элемент в дерево, сначала необходимо его создать командой (1)");
            break;
        case 3:
            if (treeExist) {
                puts("Числа кратные двум:");
                int count = countAndPrintEven(firstElement);
                printf("\nИх количество = %d\n", count);
            }
            else puts("Дерева не существует. Чтобы анализировать элементы дерева, сначала необходимо его создать командой (1)");
            break;
        case 4:
            if (treeExist) deleteEven(firstElement);
            else puts("Дерева не существует. Чтобы удалять элементы дерева, сначала необходимо его создать командой (1)");
            break;
        case 5:
            if (treeExist) printTree(firstElement);
            else puts("Дерева не существует. Чтобы вывести на экран дерево, сначала необходимо его создать командой (1)");
            break;
        case 6:
            exit = true;
            break;
        case 7:
            showMenu();
            break;
        default:
            puts("Неверная команда. Для вывода помощи нажмите (7)");
            break;
        }
    }
}

// Создание дерева
void makeTree() {
    puts("Введите последовательность чисел. Окончание ввода - 0");
    int number;
    scanf_s("%d", &number);
    if (number == 0) puts("Дерево не было создано");
    else {
        firstElement = new Element;
        makeNewElement(firstElement, number);
        scanf_s("%d", &number);
        while (number != 0) {
            Element* newElement = new Element;
            makeNewElement(newElement, number);
            addElement(firstElement, newElement);
            scanf_s("%d", &number);
        }
        treeExist = true;
        puts("Дерево создано");
    }
}

// Сумма цифр числа
int sumOfDigits(int n) {
    int sum = 0;
    do {
        sum += n % 10;
        n /= 10;
    } while (n != 0);
    return sum;
}

// Создание элемента
void makeNewElement(Element* newElement, int number) {
    newElement->left = nullptr;
    newElement->right = nullptr;
    newElement->parent = nullptr;
    newElement->number = number;
    newElement->sumOfDigits = sumOfDigits(newElement->number);
}

// Добавление элемента в дерево
void addElement(Element* curElement, Element* newElement) {
    if (newElement->sumOfDigits < curElement->sumOfDigits) {
        if (curElement->left != nullptr) addElement(curElement->left, newElement);
        else {
            curElement->left = newElement;
            newElement->parent = curElement;
        }
    }
    else {
        if (curElement->right != nullptr) addElement(curElement->right, newElement);
        else {
            curElement->right = newElement;
            newElement->parent = curElement;
        }
    }
}

// Подсчет и печать четных элементов
int countAndPrintEven(Element* curElement) {
    if (curElement == nullptr) return 0;
    else
        if (curElement->number % 2 == 0) {
            printf("%d ", curElement->number);
            return countAndPrintEven(curElement->left) + countAndPrintEven(curElement->right) + 1;
        }
        else {
            return countAndPrintEven(curElement->left) + countAndPrintEven(curElement->right);
        }
}

// Удаление четных элементов
void deleteEven(Element* curElement) {
    if (curElement->left != nullptr) {
        deleteEven(curElement->left);
        if (curElement->left->number % 2 == 0) deleteElement(curElement, left);
    }
    if (curElement->right != nullptr) {
        deleteEven(curElement->right);
        if (curElement->right->number % 2 == 0) deleteElement(curElement, right);
    }
    if (curElement->parent == nullptr && curElement->number % 2 == 0) deleteElement(nullptr, none);
}

// Удаление элемента
void deleteElement(Element* parentOfElementToDelete, side sideOfElementToDelete) {
    Element* elementToDelete;
    if (sideOfElementToDelete == left) elementToDelete = parentOfElementToDelete->left;
    else if (sideOfElementToDelete == right) elementToDelete = parentOfElementToDelete->right;
    else elementToDelete = firstElement;

    printf("Удален элемент %d\t", elementToDelete->number);
    if (sideOfElementToDelete == none) printf(", это была вершина дерева\n");
    else {
        if (sideOfElementToDelete == right) printf(", он находился     справа     от своего родителя %d\n", parentOfElementToDelete->number);
        else printf(", он находился     слева      от своего родителя %d\n", parentOfElementToDelete->number);
    }

    // Если элемент является листом (нет ни правых, ни левых потомков)
    if (elementToDelete->left == nullptr && elementToDelete->right == nullptr) {
        if (sideOfElementToDelete == left) parentOfElementToDelete->left = nullptr;
        else if (sideOfElementToDelete == right) parentOfElementToDelete->right = nullptr;
        else {
            puts("Т.к. единственный элемент дерева является четным, то дерево полностью удалено");
            treeExist = false;
        }
    }

    // Если у элемента есть только правый потомок
    if (elementToDelete->left == nullptr && elementToDelete->right != nullptr) {
        if (sideOfElementToDelete == left) parentOfElementToDelete->left = elementToDelete->right;
        else if (sideOfElementToDelete == right) parentOfElementToDelete->right = elementToDelete->right;

        if (sideOfElementToDelete == none) firstElement = elementToDelete->right;
        else elementToDelete->right->parent = parentOfElementToDelete;
    }

    // Если у элемента есть только левый потомок
    if (elementToDelete->left != nullptr && elementToDelete->right == nullptr) {
        if (sideOfElementToDelete == left) parentOfElementToDelete->left = elementToDelete->left;
        else if (sideOfElementToDelete == right) parentOfElementToDelete->right = elementToDelete->left;

        if (sideOfElementToDelete == none) firstElement = elementToDelete->left;
        else elementToDelete->left->parent = parentOfElementToDelete;
    }

    // Если у элемента есть оба потомка
    if (elementToDelete->left != nullptr && elementToDelete->right != nullptr) {
        // Идем на один вправо, остальные влево
        if (elementToDelete->right->left != nullptr) {
            Element* current = elementToDelete->right->left;
            while (current->left != nullptr) current = current->left;
            current->parent->left = nullptr;
            elementToDelete->number = current->number;
            elementToDelete->sumOfDigits = current->sumOfDigits;
            elementToDelete = current;
        }
        // Если после одного шага вправо, влево потомков нет, то перемещаем правый потомок на место elementToDelete
        else {
            if (sideOfElementToDelete == none) elementToDelete->right->parent = nullptr;
            else {
                elementToDelete->right->parent = parentOfElementToDelete;
                if (sideOfElementToDelete == right) parentOfElementToDelete->right = elementToDelete->right;
                else parentOfElementToDelete->left = elementToDelete->right;
            }
            elementToDelete->right->left = elementToDelete->left;
            elementToDelete->left->parent = elementToDelete->right;
        }
    }

    delete elementToDelete;
}

void printTree(Element* curElement) {
    puts("Как вы хотите распечатать дерево?");
    puts("1 - Прямой обход");
    puts("2 - Симметричный обход");
    puts("3 - Обратный обход");
    printf(">> ");
    int a;
    scanf_s("%d", &a);
    switch (a) {
    case 1:
        PreOrder_PrintTree(curElement);
        break;
    case 2:
        SymmetricOrder_PrintTree(curElement);
        break;
    case 3:
        PostOrder_PrintTree(curElement);
        break;
    default:
        puts("Ошибка ввода. Будет произведена печать дерева прямым обходом");
        PreOrder_PrintTree(curElement);
        break;
    }
    puts("\nДерево создано по признаку \"Сумма цифр числа\" (сумма указана в скобках)");
    printf("Глубина дерева = %d, количество узлов = %d\n", countDepth(curElement), countNodes(curElement));
}
// Печать при прямом обходе бинарного дерева
void PreOrder_PrintTree(Element* curElement) {
    if (curElement != nullptr) {
        printf("%d(%d) ", curElement->number, curElement->sumOfDigits);
        PreOrder_PrintTree(curElement->left);
        PreOrder_PrintTree(curElement->right);
    }
}
// Печать при симметричном обходе бинарного дерева
void SymmetricOrder_PrintTree(Element* curElement) {
    if (curElement != nullptr) {
        SymmetricOrder_PrintTree(curElement->left);
        printf("%d(%d) ", curElement->number, curElement->sumOfDigits);
        SymmetricOrder_PrintTree(curElement->right);
    }
}
// Печать при обратном обходе бинарного дерева
void PostOrder_PrintTree(Element* curElement) {
    if (curElement != nullptr) {
        PostOrder_PrintTree(curElement->left);
        PostOrder_PrintTree(curElement->right);
        printf("%d(%d) ", curElement->number, curElement->sumOfDigits);
    }
}
// Количество узлов дерева
int countNodes(Element* curElement) {
    if (curElement == nullptr) return 0;
    else return countNodes(curElement->left) + countNodes(curElement->right) + 1;
}
// Глубина дерева
int countDepth(Element* curElement) {
    if (curElement == nullptr) return 0;
    else {
        int left = countDepth(curElement->left);
        int right = countDepth(curElement->right);
        if (left > right) return left + 1;
        else return right + 1;
    }
}

// Очистка памяти
void deleteTree(Element* curElement) {
    if (curElement != nullptr) {
        deleteTree(curElement->left);
        deleteTree(curElement->right);
        delete curElement;
    }
}

int main()
{
    setlocale(0, "rus");
    srand(time(NULL));
    treeExist = false;
    loadInterface();
    if (treeExist) deleteTree(firstElement);
    puts("Окончание работы программы. Для завершения нажмите любую клавишу...");
    _getch();
    return 0;
}
