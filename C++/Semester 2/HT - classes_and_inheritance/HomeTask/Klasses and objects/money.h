#pragma once
#include <iostream>
#include <string>
#include "Exceptions.h"

class Money {
	int rubles_1;
	int rubles_2;
	int rubles_5;
	int rubles_10;
	int rubles_50;
	int rubles_100;
	int rubles_500;
	int rubles_1000;
	int rubles_5000;
	int kopek_1;
	int kopek_5;
	int kopek_10;
	int kopek_50;

public:
	// Конструкторы
	Money();
	explicit Money(double value);                            //!!! Запретить неявные преобразования --- Исправлено
		
	// Значение суммы
	double Summarize() const;

	std::string toString() const;

	// Операции

	Money& operator=(const double value);

	friend Money operator+(const Money& m1, const Money& m2);
	friend Money operator-(const Money& m1, const Money& m2);
	friend Money operator/(const Money& m1, const Money& m2);
	friend Money operator/(const Money& m, const double value);
	friend Money operator*(const Money& m, const double value);

	friend bool operator>(const Money& m1, const Money& m2);
	friend bool operator>=(const Money& m1, const Money& m2);
	friend bool operator<(const Money& m1, const Money& m2);
	friend bool operator<=(const Money& m1, const Money& m2);
	friend bool operator==(const Money& m1, const Money& m2);

	friend std::ostream& operator<<(std::ostream& out, const Money& m); //   
	friend std::istream& operator>>(std::istream& in, Money& m); //   
};