#pragma once
#include "Application.h"

void Application::run() {
	bool exit(false);
	PrintMenu("MAIN");
	while (!exit) {
	    
	    //!!! Что тут делают объекты? Работа только через указатели на базовый класс (= new ...). --- Исправлено
	    //!!! Указатели инициализируются в подменю. --- Исправлено	   

		cout << "\nYour input >> ";
		int command;
		cin >> command;
		switch (command)
		{
		case 1: {
			tr = new RectTriangle;
			break;
		}
		case 2: {
			tr = new EquilateralTriangle;
			break;
		}
		case 3: {
			tr = new IsoscelessTriangle;
			break;
		}
		case 4: {
			PrintMenu("MAIN");
			break;
		}
		case 5: {
			exit = true;
			break;
		}
		default:
			cout << "Wrong input. Try again. To show menu press 4." << endl;
			break;
		}

		if (command == 1 || command == 2 || command == 3) {
			cout << "\n-------- New triangle --------" << endl << endl;
			tr->GetTriangle();
			tr->PrintTriangle();
			bool newExit = false;
			while (!newExit) {
				cout << endl;
				PrintMenu("TRIANGLE");
				cout << "\nYour input >> ";
				cin >> command;
				switch (command)
				{
				case 1: {
					cout << "Area = " << tr->Area() << endl;
					break;
				}
				case 2: {
					cout << "Perimeter = " << tr->Perimeter() << endl;
					break;
				}
				case 3: {
					newExit = true;
					cout << "\n-------- End of new triangle --------" << endl << endl;
					PrintMenu("MAIN");
					break;
				}
				default:
					cout << "Wrong input. Try again." << endl;
					break;
				}
			}			
		}	

		delete tr;
	}
}

void Application::PrintMenu(std::string str) {
	if (str == "MAIN") {
		cout << "What would you like to do?" << endl;
		cout << "1 - Create rectangular triangle" << endl;
		cout << "2 - Create isosceles triangle" << endl;
		cout << "3 - Create equilateral triangle" << endl;
		cout << "4 - Print menu" << endl;
		cout << "5 - Exit program" << endl;
	}

	if (str == "TRIANGLE") {
		cout << "What would you like to do?" << endl;
		cout << "1 - Calculate area of a triangle" << endl;
		cout << "2 - Calculate perimeter of a triangle" << endl;
		cout << "3 - Go back to main menu" << endl;
	}
}