#include "Application.h"

void Application::run() {
	bool exit(false);
	PrintMenu();
	while (!exit) {
		cout << "\nYour input >> ";
		int command;
		cin >> command;
		switch (command)
		{
		case 1: {
			Bankomat newBankomat;
			try {
				cin >> newBankomat;
				bankomats[newBankomat.m_ID] = newBankomat;
			}
			catch (BankomatException& exception){
				cerr << exception.what() << endl;
			}
			break;
		}
		case 2: {
			cout << "Input ID of needed bankomat: ";
			int ID;
			cin >> ID;
			if (bankomats.count(ID) == 0) {
				cout << "There is no bankomat with that ID." << endl;
				cout << "To init new bankomat press 1" << endl;
				break;
			}
			cout << "Input amount of money to add: ";
			Money cash;
			cin >> cash;
			bankomats[ID].AddMoney(cash);
			break;
		}
		case 3: {
			cout << "Input ID of needed bankomat: ";
			int ID;
			cin >> ID;
			if (bankomats.count(ID) == 0) {
				cout << "There is no bankomat with that ID." << endl;
				cout << "To init new bankomat press 1" << endl;
				break;
			}
			cout << "Input amount of money to take: ";
			Money cash;
			cin >> cash;
			try {
				bankomats[ID].TakeMoney(cash);
			}
			catch (BankomatException& exception) {
				cerr << exception.what() << endl;
			}
			break;
		}
		case 4: {
			cout << "Input ID of needed bankomat: ";
			int ID;
			cin >> ID;
			if (bankomats.count(ID) == 0) {
				cout << "There is no bankomat with that ID." << endl;
				cout << "To init new bankomat press 1." << endl;
				break;
			}
			cout << bankomats[ID];
			break;
		}
		case 5: {
			PrintMenu();
			break;
		}
		case 6: {
			exit = true;
			break;
		}
		default:
			cout << "Wrong input. Try again. To show menu press 5." << endl;
			break;
		}
	}
}

void Application::PrintMenu() {
	cout << "What would you like to do?" << endl;
	cout << "1 - Init new bankomat" << endl;
	cout << "2 - Add money to bankomat" << endl;
	cout << "3 - Take money from bankomat" << endl;
	cout << "4 - Show info about bankomat" << endl;
	cout << "5 - Print menu" << endl;
	cout << "6 - Exit" << endl;
}