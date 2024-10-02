#include "Application.h"

void Application::run() {
	bool exit(false);
	PrintMenu("MAIN");
	while (!exit) {
		cout << "\nYour input >> ";
		int command;
		cin >> command;
		switch (command)
		{
		case 1: {
			TestArray();
			PrintMenu("MAIN");
			break;
		}
		case 2: {
			TestBitString();
			PrintMenu("MAIN");
			break;
		}
		case 3: {
			TestDecimal();
			PrintMenu("MAIN");
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
	}
}

void Application::TestArray() {
	bool exit(false);
	cout << "\n------------ Testing Array ------------" << endl << endl;
	PrintMenu("ARRAY");
	
	a = new Array; //!!! Утечка памяти --- Исправлено
	b = new Array; //!!! Утечка памяти --- Исправлено
	c = new Array; //!!! Утечка памяти --- Исправлено

	while (!exit) {
		cout << "\nYour input >> ";
		int command;
		cin >> command;
		try {
			switch (command)
			{
			case 1: {
				cout << "First array:" << endl;
				cin >> *a;
				cout << "Second array:" << endl;
				cin >> *b;
				a->Sum(b, c);
				cout << *a << " + " << *b << " = " << *c << endl;
				break;
			}
			case 2: {
				cout << "Input array:" << endl;
				cin >> *a;
				cout << "Input index: ";
				int index;
				cin >> index;
				int result = (*a)[(*a).getSize() - index - 1];
				cout << "Array[" << index << "] = " << result << endl;
				break;
			}
			case 3: {
				cout << "Input array:" << endl;
				cin >> *a;
				cout << "Size of array = " << a->getSize() << endl;
				break;
			}
			case 4: {
				PrintMenu("ARRAY");
				break;
			}
			case 5: {
				cout << "\n------------ Finished Testing Array ------------" << endl << endl;
				exit = true;
				break;
			}
			default:
				cout << "Wrong input. Try again. To show menu press 4." << endl;
				break;
			}
		}
		catch (std::length_error& exception) {
			cerr << "Length error: " << exception.what() << endl;
		}
		catch (std::out_of_range& exception) {
			cerr << "Out of range error: " << exception.what() << endl;
		}
		catch (std::underflow_error& exception) {
			cerr << "Underflow error: " << exception.what() << endl;
		}
		catch (InCompatibleDimException& exception) {
			cerr << "Error: " << exception.what() << endl;
		}
		catch (std::exception& exception) {
			cerr << "Some other std::exception: " << exception.what() << endl;
		}
	}

	delete a;
	delete b;
	delete c;
}

void Application::TestBitString() {
	bool exit(false);
	cout << "\n------------ Testing BitString ------------" << endl << endl;
	PrintMenu("BITSTRING");
	
	a = new BitString; //!!! Утечка памяти --- Исправлено
	b = new BitString; //!!! Утечка памяти --- Исправлено
	c = new BitString; //!!! Утечка памяти --- Исправлено

	while (!exit) {
		cout << "\nYour input >> ";
		int command;
		cin >> command;
		try {
			switch (command)
			{
			case 1: {
				cout << "First string:" << endl;
				cin >> *a;
				cout << "Second string:" << endl;
				cin >> *b;
				a->Sum(b, c);
				cout << *a << " + " << *b << " = " << *c << endl;
				break;
			}
			case 2: {
				cout << "First string:" << endl;
				cin >> *a;
				cout << "Second string:" << endl;
				cin >> *b;

				BitString* str_a = dynamic_cast<BitString*>(a);
				if (str_a == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to BitString*");
				BitString* str_b = dynamic_cast<BitString*>(b);
				if (str_b == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to BitString*");
				BitString* str_c = dynamic_cast<BitString*>(c);
				if (str_c == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to BitString*");
				
				//!!! Где проверка правильности приведения? --- Исправлено везде

				*str_c = (*str_a).And(*str_b);
				cout << *str_a << " And " << *str_b << " = " << *str_c << endl;
				break;
			}
			case 3: {
				cout << "First string:" << endl;
				cin >> *a;
				cout << "Second string:" << endl;
				cin >> *b;

				BitString* str_a = dynamic_cast<BitString*>(a);
				if (str_a == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to BitString*");
				BitString* str_b = dynamic_cast<BitString*>(b);
				if (str_b == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to BitString*");
				BitString* str_c = dynamic_cast<BitString*>(c);
				if (str_c == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to BitString*");
				
				*str_c = (*str_a).Or(*str_b);
				cout << *str_a << " Or " << *str_b << " = " << *str_c << endl;
				break;
			}
			case 4: {
				cout << "First string:" << endl;
				cin >> *a;
				cout << "Second string:" << endl;
				cin >> *b;

				BitString* str_a = dynamic_cast<BitString*>(a);
				if (str_a == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to BitString*");
				BitString* str_b = dynamic_cast<BitString*>(b);
				if (str_b == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to BitString*");
				BitString* str_c = dynamic_cast<BitString*>(c);
				if (str_c == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to BitString*");
                
				*str_c = (*str_a).Xor(*str_b);
				cout << *str_a << " Xor " << *str_b << " = " << *str_c << endl;
				break;
			}
			case 5: {
				cout << "Input string:" << endl;
				cin >> *a;

				BitString* str_a = dynamic_cast<BitString*>(a);
				if (str_a == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to BitString*");
				BitString* str_b = dynamic_cast<BitString*>(b);
				if (str_b == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to BitString*");

				*str_b = (*str_a).Not();
				cout << "Not " << *str_a << " = " << *str_b << endl;
				break;
			}
			case 6: {
				cout << "Input string:" << endl;
				cin >> *a;
				int number;
				cout << "Input number to move: ";
				cin >> number;

				BitString* str_a = dynamic_cast<BitString*>(a);
				if (str_a == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to BitString*");
				BitString* str_b = dynamic_cast<BitString*>(b);
				if (str_b == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to BitString*");

				*str_b = (*str_a).MoveLeft(number);
				cout << *str_a << " moved left with number " << number << " = " << *str_b << endl;
				break;
			}
			case 7: {
				cout << "Input string:" << endl;
				cin >> *a;
				int number;
				cout << "Input number to move: ";
				cin >> number;

				BitString* str_a = dynamic_cast<BitString*>(a);
				if (str_a == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to BitString*");
				BitString* str_b = dynamic_cast<BitString*>(b);
				if (str_b == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to BitString*");

				*str_b = (*str_a).MoveRight(number);
				cout << *str_a << " moved right with number " << number << " = " << *str_b << endl;
				break;
			}
			case 8: {
				PrintMenu("BITSTRING");
				break;
			}
			case 9: {
				cout << "\n------------ Finished Testing BitString ------------" << endl << endl;
				exit = true;
				break;
			}
			default:
				cout << "Wrong input. Try again. To show menu press 8." << endl;
				break;
			}
		}
		catch (std::length_error& exception) {
			cerr << "Length error: " << exception.what() << endl;
		}
		catch (std::out_of_range& exception) {
			cerr << "Out of range error: " << exception.what() << endl;
		}
		catch (std::underflow_error& exception) {
			cerr << "Underflow error: " << exception.what() << endl;
		}
		catch (InCompatibleDimException& exception) {
			cerr << "Error: " << exception.what() << endl;
		}
		catch (std::exception& exception) {
			cerr << exception.what() << endl;
		}
	}

	delete a;
	delete b;
	delete c;
}

void Application::TestDecimal() {
	bool exit(false);
	cout << "\n------------ Testing Decimal ------------" << endl << endl;
	PrintMenu("DECIMAL");
	a = new Decimal;
	b = new Decimal;
	c = new Decimal;

	while (!exit) {
		cout << "\nYour input >> ";
		int command;
		cin >> command;
		try {
			switch (command)
			{
			case 1: {
				cout << "First decimal:" << endl;
				cin >> *a;
				cout << "Second decimal:" << endl;
				cin >> *b;
				a->Sum(b, c);
				cout << *a << " + " << *b << " = " << *c << endl;
				break;
			}
			case 2: {
				cout << "First decimal:" << endl;
				cin >> *a;
				cout << "Second decimal:" << endl;
				cin >> *b;

				Decimal* dec_a = dynamic_cast<Decimal*>(a);
				if (dec_a == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to Decimal*");
				Decimal* dec_b = dynamic_cast<Decimal*>(b);
				if (dec_b == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to Decimal*");
				Decimal* dec_c = dynamic_cast<Decimal*>(c);
				if (dec_c == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to Decimal*");

				*dec_c = (*dec_a).Substract(*dec_b);
				cout << *dec_a << " - " << *dec_b << " = " << *dec_c << endl;
				break;
			}
			case 3: {
				cout << "First decimal:" << endl;
				cin >> *a;
				cout << "Second decimal:" << endl;
				cin >> *b;

				Decimal* dec_a = dynamic_cast<Decimal*>(a);
				if (dec_a == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to Decimal*");
				Decimal* dec_b = dynamic_cast<Decimal*>(b);
				if (dec_b == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to Decimal*");
				Decimal* dec_c = dynamic_cast<Decimal*>(c);
				if (dec_c == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to Decimal*");

				*dec_c = (*dec_a).Multiply(*dec_b);
				cout << *dec_a << " * " << *dec_b << " = " << *dec_c << endl;
				break;
			}
			case 4: {
				cout << "First decimal:" << endl;
				cin >> *a;
				cout << "Second decimal:" << endl;
				cin >> *b;

				Decimal* dec_a = dynamic_cast<Decimal*>(a);
				if (dec_a == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to Decimal*");
				Decimal* dec_b = dynamic_cast<Decimal*>(b);
				if (dec_b == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to Decimal*");
				Decimal* dec_c = dynamic_cast<Decimal*>(c);
				if (dec_c == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to Decimal*");

				*dec_c = (*dec_a).Divide(*dec_b);
				cout << *dec_a << " / " << *dec_b << " = " << *dec_c << endl;
				break;
			}
			case 5: {
				cout << "First decimal:" << endl;
				cin >> *a;
				cout << "Second decimal:" << endl;
				cin >> *b;

				Decimal* dec_a = dynamic_cast<Decimal*>(a);
				if (dec_a == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to Decimal*");
				Decimal* dec_b = dynamic_cast<Decimal*>(b);
				if (dec_b == nullptr)
					throw std::exception("Bad cast error: Cannot cast Array* to Decimal*");

				if ((*dec_a) > (*dec_b)) cout << *dec_a << " > " << *dec_b << endl;
				if ((*dec_a) < (*dec_b)) cout << *dec_a << " < " << *dec_b << endl;
				if ((*dec_a) == (*dec_b)) cout << *dec_a << " == " << *dec_b << endl;
				break;
			}
			case 6: {
				PrintMenu("DECIMAL");
				break;
			}
			case 7: {
				cout << "\n------------ Finished Testing Decimal ------------" << endl << endl;
				exit = true;
				break;
			}
			default:
				cout << "Wrong input. Try again. To show menu press 6." << endl;
				break;
			}
		}
		catch (std::length_error& exception) {
			cerr << "Length error: " << exception.what() << endl;
		}
		catch (std::out_of_range& exception) {
			cerr << "Out of range error: " << exception.what() << endl;
		}
		catch (std::underflow_error& exception) {
			cerr << "Underflow error: " << exception.what() << endl;
		}
		catch (InCompatibleDimException& exception) {
			cerr << "Error: " << exception.what() << endl;
		}
		catch (std::exception& exception) {
			cerr << exception.what() << endl;
		}
	}

	delete a;
	delete b;
	delete c;
}

void Application::PrintMenu(std::string str) {
	if (str == "MAIN") {
		cout << "What would you like to do?" << endl;
		cout << "1 - Test Array" << endl;
		cout << "2 - Test BitString" << endl;
		cout << "3 - Test Decimal" << endl;
		cout << "4 - Print menu" << endl;
		cout << "5 - Exit program" << endl;
	}

	if (str == "ARRAY") {
		cout << "What would you like to do?" << endl;
		cout << "1 - Sum two Arrays (virtual function)" << endl;
		cout << "2 - Display Array[i]" << endl;
		cout << "3 - Get size of Array" << endl;
		cout << "4 - Print menu" << endl;
		cout << "5 - Go back to main menu" << endl;
	}

	if (str == "BITSTRING"){
		cout << "What would you like to do?" << endl;
		cout << "1 - Sum two BitStrings (virtual function)" << endl;
		cout << "2 - Operation And" << endl;
		cout << "3 - Operation Or" << endl;
		cout << "4 - Operation Xor" << endl;
		cout << "5 - Operation Not" << endl;
		cout << "6 - Operation MoveLeft" << endl;
		cout << "7 - Operation MoveRight" << endl;
		cout << "8 - Print menu" << endl;
		cout << "9 - Go back to main menu" << endl;
	}

	if (str == "DECIMAL"){
		cout << "What would you like to do?" << endl;
		cout << "1 - Sum two Decimals (virtual function)" << endl;
		cout << "2 - Substract two Decimals" << endl;
		cout << "3 - Multiply two Decimals" << endl;
		cout << "4 - Divide two Decimals" << endl;
		cout << "5 - Compare two Decimals" << endl;
		cout << "6 - Print menu" << endl;
		cout << "7 - Go back to main menu" << endl;
	}
}