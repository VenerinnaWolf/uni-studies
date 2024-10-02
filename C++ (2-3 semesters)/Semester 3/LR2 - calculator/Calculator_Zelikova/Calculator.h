#pragma once

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QtWidgets>
#include <QApplication>
#include <QtMath>

class QLCDNumber;
class QRadioButton;
class QPushButton;

class Calculator : public QWidget
{
    Q_OBJECT
private:
    QLCDNumber* display;
    QString str_to_display = "0"; // string that contains expression that will be shown on display
    QStack<QString> expression_stack; // stack that contains separate parts of expression (lexemes)

    bool is_pi = false;
    bool is_error = false;

    QFrame* engineer_buttons_frame;
    const int display_size = 16;
    const long long precision = pow(10,display_size-2);

    // radio buttons
    QRadioButton* basic_radio_button;
    QRadioButton* engineer_radio_button;

    // basic buttons
    QPushButton* clear_button;
    QPushButton* num_0_button;
    QPushButton* num_1_button;
    QPushButton* num_2_button;
    QPushButton* num_3_button;
    QPushButton* num_4_button;
    QPushButton* num_5_button;
    QPushButton* num_6_button;
    QPushButton* num_7_button;
    QPushButton* num_8_button;
    QPushButton* num_9_button;
    QPushButton* plus_button;
    QPushButton* mult_button;
    QPushButton* minus_button;
    QPushButton* divide_button;
    QPushButton* sqrt_button;
    QPushButton* one_div_x_button;
    QPushButton* equal_button;
    QPushButton* dot_button;

    // engineer buttons
    QPushButton* sinh_button;
    QPushButton* cosh_button;
    QPushButton* tanh_button;
    QPushButton* sin_button;
    QPushButton* cos_button;
    QPushButton* tan_button;
    QPushButton* factorial_button;
    QPushButton* exp_button;
    QPushButton* ln_button;
    QPushButton* log_button;
    QPushButton* pi_button;
    QPushButton* pow2_button;
    QPushButton* pow3_button;
    QPushButton* powy_button;
    QPushButton* sqrt3_button;
    QPushButton* sqrty_button;

    QSet<QPushButton*> numbers;
    QSet<QPushButton*> unary_op;
    QSet<QPushButton*> binary_op;

    QPushButton* create_button(const QString& name);
    void create_display();
    void create_buttons();
    void add_layouts();
    void calculate();

public:
    Calculator(QWidget* pwgt = 0);

public slots:
    void button_clicked();
    void radio_button_clicked();
};

#endif // CALCULATOR_H
