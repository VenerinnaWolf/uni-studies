#include "bankomat.h"

// 
Bankomat::Bankomat() : 
	m_ID(0), m_cashInBankomat(0), m_maxSum(0), m_minSum(0)
{}

Bankomat::Bankomat(const int ID, const Money& cash, const Money& minSum, const Money& maxSum) : 
	m_ID(ID), m_cashInBankomat(cash), m_maxSum(maxSum), m_minSum(minSum)
{}
	
//!!! Чем не устраивает конструктор копирования, создаваемый автоматически? --- Исправлено - удалила конструктор копирования, дублиружщий функционал автоматически созданного

//     
void Bankomat::AddMoney(const Money& cash) { //!!! Объекты передаются по ссылке на константу --- Исправлено
	m_cashInBankomat = m_cashInBankomat + cash;
}

//   
void Bankomat::TakeMoney(const Money& cash) { //!!! Объекты передаются по ссылке на константу --- Исправлено
	if (cash > m_maxSum) { 
		throw BankomatException("You are trying to take too much money");
	}
	if (cash < m_minSum) {
		throw BankomatException("You are trying to take too little money");
	}
	m_cashInBankomat = m_cashInBankomat - cash;
}

//   
std::istream& operator>>(std::istream& in, Bankomat& bankomat) {
	std::cout << "Input bankomat ID: ";
	in >> bankomat.m_ID;
	std::cout << "Input initial amount of money in bankomat: ";
	in >> bankomat.m_cashInBankomat;
	std::cout << "Input maximum amount of money to withdraw: ";
	in >> bankomat.m_maxSum;
	std::cout << "Input minimal amount of money to withdraw: ";
	in >> bankomat.m_minSum;
	if (bankomat.m_maxSum < bankomat.m_minSum) {
		throw BankomatException("Max sum is smaller than min sum");
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const Bankomat& bankomat) {
	out << "ID: " << bankomat.m_ID << std::endl;
	out << "Amount of money in bankomat: " << bankomat.toString() << std::endl;
	out << "Maximum amount of money to withdraw: " << bankomat.m_maxSum.toString() << std::endl;
	out << "Minimal amount of money to withdraw: " << bankomat.m_minSum.toString() << std::endl;
	return out;
}

std::string Bankomat::toString() const {
	return m_cashInBankomat.toString();
}