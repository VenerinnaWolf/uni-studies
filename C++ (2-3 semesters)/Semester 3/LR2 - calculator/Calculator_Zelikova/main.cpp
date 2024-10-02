#include "Calculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication my_app(argc, argv);
    Calculator calculator;
    calculator.show();
    return my_app.exec();
}
