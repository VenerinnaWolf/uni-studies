#include "Calculator.h"

// CONSTRUCTOR
Calculator::Calculator(QWidget* pwgt/*= О*/) : QWidget(pwgt)
{
    this->setWindowTitle("Калькулятор");
    create_display();
    create_buttons();
    add_layouts();
}

// FUNCTIONS
QPushButton* Calculator::create_button(const QString& name){
    QPushButton* button = new QPushButton(name);
    button->setMinimumSize(60, 60);
    button->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    QFont font = QFont();
    font.setPointSize(16);
    button->setFont(font);
    connect(button, SIGNAL(clicked()), this, SLOT(button_clicked()));
    return button;
}

void Calculator::create_display() {
    display = new QLCDNumber(display_size);
    display->setSegmentStyle(QLCDNumber::Flat);
    display->setMinimumSize(500,100);
//    display->setMaximumHeight(100);
    display->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);
}

void Calculator::create_buttons() {
    basic_radio_button = new QRadioButton("Стандартный калькулятор");
    engineer_radio_button = new QRadioButton("Инженерный калькулятор");
    QFont font = QFont();
    font.setPointSize(12);
    basic_radio_button->setFont(font);
    engineer_radio_button->setFont(font);
    basic_radio_button->setChecked(true);

    connect(basic_radio_button, SIGNAL(clicked()), SLOT(radio_button_clicked()));
    connect(engineer_radio_button, SIGNAL(clicked()), SLOT(radio_button_clicked()));

    clear_button = create_button("C");
    // basic buttons
    num_0_button = create_button("0");
    num_1_button = create_button("1");
    num_2_button = create_button("2");
    num_3_button = create_button("3");
    num_4_button = create_button("4");
    num_5_button = create_button("5");
    num_6_button = create_button("6");
    num_7_button = create_button("7");
    num_8_button = create_button("8");
    num_9_button = create_button("9");
    plus_button = create_button("+");
    mult_button = create_button("*");
    minus_button = create_button("-");
    divide_button = create_button("/");
    sqrt_button = create_button("√x");
    one_div_x_button = create_button("1/x");
    equal_button = create_button("=");
    dot_button = create_button(".");
    // their shortcuts
    clear_button->setShortcut(QKeySequence("DEL"));
    num_0_button->setShortcut(QKeySequence("0"));
    num_1_button->setShortcut(QKeySequence("1"));
    num_2_button->setShortcut(QKeySequence("2"));
    num_3_button->setShortcut(QKeySequence("3"));
    num_4_button->setShortcut(QKeySequence("4"));
    num_5_button->setShortcut(QKeySequence("5"));
    num_6_button->setShortcut(QKeySequence("6"));
    num_7_button->setShortcut(QKeySequence("7"));
    num_8_button->setShortcut(QKeySequence("8"));
    num_9_button->setShortcut(QKeySequence("9"));
    plus_button->setShortcut(QKeySequence("+"));
    mult_button->setShortcut(QKeySequence("*"));
    minus_button->setShortcut(QKeySequence("-"));
    divide_button->setShortcut(QKeySequence("/"));
    dot_button->setShortcut(QKeySequence("."));
    equal_button->setShortcut(Qt::Key_Enter);
    // engineer buttons
    sinh_button = create_button("sinh");
    cosh_button = create_button("cosh");
    tanh_button = create_button("tanh");
    sin_button = create_button("sin");
    cos_button = create_button("cos");
    tan_button = create_button("tan");
    factorial_button = create_button("n!");
    exp_button = create_button("exp");
    ln_button = create_button("ln");
    log_button = create_button("log");
    pi_button = create_button("π");
    pow2_button = create_button("x²");
    pow3_button = create_button("x³");
    powy_button = create_button("xʸ");
    sqrt3_button = create_button("³√x");
    sqrty_button = create_button("ʸ√x");

    numbers << num_0_button << num_1_button << num_2_button << num_3_button << num_4_button
            << num_5_button << num_6_button << num_7_button << num_8_button << num_9_button
            << pi_button << dot_button;

    binary_op << plus_button << minus_button << mult_button << divide_button
              << powy_button << sqrty_button << equal_button;

    unary_op << sqrt_button << sqrt3_button << pow2_button << pow3_button << one_div_x_button
             << sin_button << sinh_button << cos_button << cosh_button << tan_button << tanh_button
             << factorial_button << exp_button << log_button << ln_button;
}

void Calculator::add_layouts() {
    QVBoxLayout* main_layout = new QVBoxLayout;
    QHBoxLayout* display_layout = new QHBoxLayout;
    QHBoxLayout* change_view_layout = new QHBoxLayout;
    QVBoxLayout* radio_buttons_layout = new QVBoxLayout;
    QHBoxLayout* buttons_layout = new QHBoxLayout;

    engineer_buttons_frame = new QFrame;
    QFrame* basic_buttons_frame = new QFrame;
    QGridLayout* engineer_buttons_layout = new QGridLayout(engineer_buttons_frame);
    QGridLayout* basic_buttons_layout = new QGridLayout(basic_buttons_frame);
    engineer_buttons_frame->hide();

    radio_buttons_layout->setSpacing(5);
    radio_buttons_layout->addWidget(basic_radio_button,5);
    radio_buttons_layout->addWidget(engineer_radio_button,4);

    change_view_layout->setContentsMargins(10,5,10,5);
    change_view_layout->setSpacing(5);
    change_view_layout->addLayout(radio_buttons_layout,4);
    change_view_layout->addWidget(clear_button,1);

    engineer_buttons_layout->addWidget(sinh_button,0,0);
    engineer_buttons_layout->addWidget(sin_button,0,1);
    engineer_buttons_layout->addWidget(exp_button,0,2);
    engineer_buttons_layout->addWidget(pow2_button,0,3);
    engineer_buttons_layout->addWidget(cosh_button,1,0);
    engineer_buttons_layout->addWidget(cos_button,1,1);
    engineer_buttons_layout->addWidget(ln_button,1,2);
    engineer_buttons_layout->addWidget(pow3_button,1,3);
    engineer_buttons_layout->addWidget(tanh_button,2,0);
    engineer_buttons_layout->addWidget(tan_button,2,1);
    engineer_buttons_layout->addWidget(log_button,2,2);
    engineer_buttons_layout->addWidget(powy_button,2,3);
    engineer_buttons_layout->addWidget(factorial_button,3,0);
    engineer_buttons_layout->addWidget(pi_button,3,1);
    engineer_buttons_layout->addWidget(sqrt3_button,3,2);
    engineer_buttons_layout->addWidget(sqrty_button,3,3);

    basic_buttons_layout->addWidget(num_7_button,0,0);
    basic_buttons_layout->addWidget(num_8_button,0,1);
    basic_buttons_layout->addWidget(num_9_button,0,2);
    basic_buttons_layout->addWidget(divide_button,0,3);
    basic_buttons_layout->addWidget(sqrt_button,0,4);
    basic_buttons_layout->addWidget(num_4_button,1,0);
    basic_buttons_layout->addWidget(num_5_button,1,1);
    basic_buttons_layout->addWidget(num_6_button,1,2);
    basic_buttons_layout->addWidget(mult_button,1,3);
    basic_buttons_layout->addWidget(one_div_x_button,1,4);
    basic_buttons_layout->addWidget(num_1_button,2,0);
    basic_buttons_layout->addWidget(num_2_button,2,1);
    basic_buttons_layout->addWidget(num_3_button,2,2);
    basic_buttons_layout->addWidget(minus_button,2,3);
    basic_buttons_layout->addWidget(equal_button,2,4,2,1);
    basic_buttons_layout->addWidget(num_0_button,3,0,1,2);
    basic_buttons_layout->addWidget(dot_button,3,2);
    basic_buttons_layout->addWidget(plus_button,3,3);

    buttons_layout->setContentsMargins(5,5,5,5);
    buttons_layout->setSpacing(5);
    buttons_layout->addWidget(engineer_buttons_frame);
    buttons_layout->addWidget(basic_buttons_frame);

//    display_layout->addStretch(1);
//    QWidget* spacer = new QWidget;
//    spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
//    display_layout->addWidget(spacer);
//    display_layout->setAlignment(Qt::AlignRight);
    display_layout->addWidget(display);
    display_layout->setContentsMargins(10,5,10,5);

    main_layout->setContentsMargins(5,5,5,5);
    main_layout->setSpacing(5);
    main_layout->addLayout(display_layout,1);
    main_layout->addLayout(change_view_layout,1);
    main_layout->addLayout(buttons_layout,4);

    setLayout(main_layout);
}

void Calculator::calculate() {
    QString lexeme;
    lexeme = expression_stack.pop();

    if (lexeme.contains("UNARY_OP")){
        QString operation = lexeme;
        QString operand;
        if (expression_stack.isEmpty()) operand = "0";
        else operand = expression_stack.pop();
        if (operand.contains("OP")) operand = expression_stack.pop();
        qreal x = operand.toDouble();

        if (operation == "UNARY_OP_SQRT") {
            if (x < 0) is_error = true;
            else x = sqrt(x);
        }
        if (operation == "UNARY_OP_SQRT3") x = qPow(x,1.0/3.0);
        if (operation == "UNARY_OP_POW2") x = x*x;
        if (operation == "UNARY_OP_POW3") x = x*x*x;
        if (operation == "UNARY_OP_ONE_DIV_X") {
            if (x == 0) is_error = true;
            else x = 1.0/x;
        }
        if (operation == "UNARY_OP_SIN") x = sin(x);
        if (operation == "UNARY_OP_SINH") x = sinh(x);
        if (operation == "UNARY_OP_COS") x = cos(x);
        if (operation == "UNARY_OP_COSH") x = cosh(x);
        if (operation == "UNARY_OP_TAN") x = tan(x);
        if (operation == "UNARY_OP_TANH") x = tanh(x);
        if (operation == "UNARY_OP_EXP") x = exp(x);
        if (operation == "UNARY_OP_LN") {
            if ( x <= 0) is_error = true;
            else x = qLn(x);
        }
        if (operation == "UNARY_OP_LOG") {
            if ( x <= 0) is_error = true;
            else x = log10(x);
        }
        if (operation == "UNARY_OP_FACT") {
            const int MAX_FACT = 20;
            if ((x < 0)||(x > MAX_FACT)||(floor(x)!=x)) is_error = true;
            else {
                unsigned int n = floor(x);
                long long result = 1;
                for (auto i = 1; i <= n; ++i){
                    result *= i;
                }
                x = result;
            }
        }
        if (is_error) {
            display->display("Error");
            expression_stack.clear();
            is_error = false;
        }
        else {
//            x = floor(x*precision)/precision;
            expression_stack.push(QString::number(x,'G',display_size));
//            display->display(QString::number(x,'G',display_size));
            display->display(x);
        }
    }

    if (lexeme.contains("BINARY_OP")){
        QString next_operation = lexeme;
        QString operand2;
        if (expression_stack.isEmpty()) {
            expression_stack.push("0");
            if (next_operation!="BINARY_OP_EQUAL") expression_stack.push(next_operation);
        }
        else {
            operand2 = expression_stack.pop();
            if (operand2.contains("OP")) operand2 = expression_stack.pop();
            if (expression_stack.isEmpty()) {
                expression_stack.push(operand2);
                if (next_operation!="BINARY_OP_EQUAL") expression_stack.push(next_operation);
            }
            else {
                QString operation = expression_stack.pop();
                QString operand1 = expression_stack.pop();
                qreal x = operand1.toDouble();
                qreal y = operand2.toDouble();
                qreal result;

                if (operation == "BINARY_OP_PLUS") result = x+y;
                if (operation == "BINARY_OP_MINUS") result = x-y;
                if (operation == "BINARY_OP_MULT") result = x*y;
                if (operation == "BINARY_OP_DIV") {
                    if (y == 0) is_error = true;
                    else result = x/y;
                }
                if (operation == "BINARY_OP_POVY") result = pow(x,y);
                if (operation == "BINARY_OP_SQRTY") {
                    if ((x<0)||(y==0)) is_error = true;
                    else result = pow(x,1/y);
                }
                if (is_error) {
                    display->display("Error");
                    expression_stack.clear();
                    is_error = false;
                }
                else {
//                    result = floor(result*precision)/precision;
                    expression_stack.push(QString::number(result,'G',display_size));
//                    display->display(QString::number(result,'G',display_size));
                    display->display(result);
                    if (next_operation!="BINARY_OP_EQUAL") expression_stack.push(next_operation);
                }
            }
        }
    }
}

// SLOTS
void Calculator::radio_button_clicked() {
    if (sender() == engineer_radio_button)
        engineer_buttons_frame->show();
    else
        engineer_buttons_frame->hide();
}

void Calculator::button_clicked() {
    QPushButton* button = (QPushButton*)sender();

    if (button == clear_button) {
        str_to_display = "0";
        expression_stack.clear();
        display->display(str_to_display);
    }

    if (numbers.contains(button)) {
        if (button == pi_button) {
            str_to_display = QString::number(M_PI,'g', display_size-1);
            is_pi = true;
        }
        else if (button == dot_button) {
            if (is_pi) {
                str_to_display = "";
                is_pi = false;
            }
            if (str_to_display.size() < display_size){
                if (str_to_display == "") str_to_display += "0";
                if (!str_to_display.contains('.')) str_to_display += '.';
            }
        }
        else {
            if (is_pi) {
                str_to_display = "";
                is_pi = false;
            }
            if (str_to_display.size() < display_size) {
                if (str_to_display == "0") str_to_display = "";
                str_to_display += button->text();
            }
        }

        display->display(str_to_display);
    }

    if (binary_op.contains(button)) {
        if (str_to_display != "") {
            if (!expression_stack.isEmpty()) {
                QString sth = expression_stack.pop();
                if (sth.contains("OP")) {
                    expression_stack.push(sth);
                }
            }
            expression_stack.push(str_to_display);
            str_to_display = "";
        }

        QString operation;
        if (button == plus_button) operation = "BINARY_OP_PLUS";
        if (button == minus_button) operation = "BINARY_OP_MINUS";
        if (button == mult_button) operation = "BINARY_OP_MULT";
        if (button == divide_button) operation = "BINARY_OP_DIV";
        if (button == powy_button) operation = "BINARY_OP_POVY";
        if (button == sqrty_button) operation = "BINARY_OP_SQRTY";
        if (button == equal_button) operation = "BINARY_OP_EQUAL";

        expression_stack.push(operation);
        calculate();
    }

    if (unary_op.contains(button)) {
        if (str_to_display != "") {
            expression_stack.push(str_to_display);
            str_to_display = "";
        }

        QString operation;
        if (button == sqrt_button) operation = "UNARY_OP_SQRT";
        if (button == sqrt3_button) operation = "UNARY_OP_SQRT3";
        if (button == pow2_button) operation = "UNARY_OP_POW2";
        if (button == pow3_button) operation = "UNARY_OP_POW3";
        if (button == one_div_x_button) operation = "UNARY_OP_ONE_DIV_X";
        if (button == sin_button) operation = "UNARY_OP_SIN";
        if (button == sinh_button) operation = "UNARY_OP_SINH";
        if (button == cos_button) operation = "UNARY_OP_COS";
        if (button == cosh_button) operation = "UNARY_OP_COSH";
        if (button == tan_button) operation = "UNARY_OP_TAN";
        if (button == tanh_button) operation = "UNARY_OP_TANH";
        if (button == factorial_button) operation = "UNARY_OP_FACT";
        if (button == exp_button) operation = "UNARY_OP_EXP";
        if (button == ln_button) operation = "UNARY_OP_LN";
        if (button == log_button) operation = "UNARY_OP_LOG";

        expression_stack.push(operation);
        calculate();
    }
}
