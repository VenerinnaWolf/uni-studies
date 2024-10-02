#pragma once
#include "money.h"


class Bankomat {
	Money m_cashInBankomat;
	Money m_minSum;
	Money m_maxSum;

public:
	int m_ID;

	// Конструкторы
	Bankomat();
	Bankomat(const int ID, const Money& cash, const Money& minSum, const Money& maxSum);

	// Метод загрузки купюр в банкомат
	void AddMoney(const Money& cash);

	// Метод снятия денег
	void TakeMoney(const Money& cash);

	// Ввод и вывод
	friend std::ostream& operator<<(std::ostream& out, const Bankomat& bankomat);
	friend std::istream& operator>>(std::istream& in, Bankomat& bankomat);

	std::string toString() const;
};