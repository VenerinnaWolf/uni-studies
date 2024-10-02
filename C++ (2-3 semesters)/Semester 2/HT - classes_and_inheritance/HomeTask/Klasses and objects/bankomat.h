#pragma once
#include "money.h"


class Bankomat {
	Money m_cashInBankomat;
	Money m_minSum;
	Money m_maxSum;

public:
	int m_ID;

	// ������������
	Bankomat();
	Bankomat(const int ID, const Money& cash, const Money& minSum, const Money& maxSum);

	// ����� �������� ����� � ��������
	void AddMoney(const Money& cash);

	// ����� ������ �����
	void TakeMoney(const Money& cash);

	// ���� � �����
	friend std::ostream& operator<<(std::ostream& out, const Bankomat& bankomat);
	friend std::istream& operator>>(std::istream& in, Bankomat& bankomat);

	std::string toString() const;
};