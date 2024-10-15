#include "money.h"

Money::Money() : 
	rubles_1(0), 
	rubles_10(0), 
	rubles_100(0), 
	rubles_1000(0), 
	rubles_2(0), 
	rubles_5(0), 
	rubles_50(0), 
	rubles_500(0), 
	rubles_5000(0), 
	kopek_1(0), 
	kopek_10(0), 
	kopek_5(0), 
	kopek_50(0) {}

// Вспомогательная функция, высчитывающая, сколько раз число n умещается в value
int CountNominals(int n, int& value) {
	int result = 0;
	if (value >= n) {
		result += value / n;
		value -= n * result;
	}
	return result;
}

Money::Money(double value) : Money() {
	value *= 100;
	int intVal = (int)value;
	rubles_5000 = CountNominals(500000, intVal);
	rubles_1000 = CountNominals(100000, intVal);
	rubles_500 = CountNominals(50000, intVal);
	rubles_100 = CountNominals(10000, intVal);
	rubles_50 = CountNominals(5000, intVal);
	rubles_10 = CountNominals(1000, intVal);
	rubles_5 = CountNominals(500, intVal);
	rubles_2 = CountNominals(200, intVal);
	rubles_1 = CountNominals(100, intVal);
	kopek_50 = CountNominals(50, intVal);
	kopek_10 = CountNominals(10, intVal);
	kopek_5 = CountNominals(5, intVal);
	kopek_1 = CountNominals(1, intVal);
}

//!!! Чем не устраивает конструктор копирования, создаваемый автоматически? --- Исправлено - удалила конструктор копирования, дублиружщий функционал автоматически созданного

double Money::Summarize() const {
	return rubles_1 + rubles_10 * 10 + rubles_100 * 100 + rubles_1000 * 1000 +
		rubles_2 * 2 + rubles_5 * 5 + rubles_50 * 50 + rubles_500 * 500 + rubles_5000 * 5000 +
		kopek_1 * 0.01 + kopek_10 * 0.1 + kopek_5 * 0.05 + kopek_50 * 0.5;
}

// ToString
std::string Money::toString() const {
	return std::to_string(rubles_1 + rubles_10 * 10 + rubles_100 * 100 + rubles_1000 * 1000 +
		rubles_2 * 2 + rubles_5 * 5 + rubles_50 * 50 + rubles_500 * 500 + rubles_5000 * 5000) + "," +
		std::to_string(kopek_1 + kopek_10 * 10 + kopek_5 * 5 + kopek_50 * 50);
}

// Операции

//!!! Чем не устраивает operator=, создаваемый автоматически? --- Исправлено - удалила operator=, дублиружщий функционал автоматически созданного

Money& Money::operator=(const double value) {//!!! Неверный возвращаемый тип --- Исправлено
	Money money(value);
	*this = money;
	return *this;
}

Money operator+(const Money& m1, const Money& m2) {
	double value = m1.Summarize() + m2.Summarize();
	Money result(value);
	return result;
}

Money operator-(const Money& m1, const Money& m2) {
	if (m1 < m2) {
		throw NegativeNumberException("First sum is smaller than second sum");
	}
	double value = m1.Summarize() - m2.Summarize();
	Money result(value);
	return result;
}

//  
Money operator/(const Money& m1, const Money& m2) {
	if (m2.Summarize() == 0) {
		throw DivisionByZero();
	}
	double value = m1.Summarize() / m2.Summarize();
	Money result(value);
	return result;
}

//    
Money operator/(const Money& m, const double value) {
	if (value == 0) {
		throw DivisionByZero();
	}
	double val = m.Summarize() / value;
	Money result(val);
	return result;
}

//    
Money operator*(const Money& m, const double value) {	
	double val = m.Summarize() * value;
	Money result(val);
	return result;
}

//  
bool operator>(const Money& m1, const Money& m2) {
	if (m1.Summarize() > m2.Summarize())
		return true;
	return false;
}
bool operator>=(const Money& m1, const Money& m2) {
	if (m1.Summarize() >= m2.Summarize())
		return true;
	return false;
}
bool operator<(const Money& m1, const Money& m2) {
	if (m1.Summarize() < m2.Summarize())
		return true;
	return false;
}
bool operator<=(const Money& m1, const Money& m2) {
	if (m1.Summarize() <= m2.Summarize())
		return true;
	return false;
}
bool operator==(const Money& m1, const Money& m2) {
	if (m1.Summarize() == m2.Summarize())
		return true;
	return false;
}

//   
std::istream& operator>>(std::istream& in, Money& m) {
	double value;
	in >> value;
	m = value;
	return in;
}

std::ostream& operator<<(std::ostream& out, const Money& m) {
	out << m.toString();
	return out;
}