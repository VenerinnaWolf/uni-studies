#pragma once
#include <iostream>
#include <string>

class BankomatException : public std::exception {
	std::string m_error;
public:
	BankomatException(const std::string& error);
	const char* what() const noexcept;
};

class NegativeNumberException : public std::exception {
	std::string m_error;
public:
	NegativeNumberException(const std::string& error);
	const char* what() const noexcept;
};

class DivisionByZero : public std::exception {
	std::string m_error;
public:
	DivisionByZero();
	const char* what() const noexcept;
};