#include "Exceptions.h"

BankomatException::BankomatException(const std::string& error)
	: m_error("Error: " + error) {}
const char* BankomatException::what() const noexcept {
	return m_error.c_str();
}

//NegativeNumberException {};
NegativeNumberException::NegativeNumberException(const std::string& error)
: m_error("Error: " + error) {}
const char* NegativeNumberException::what() const noexcept {
	return m_error.c_str();
}

//DivisionByZero {};
DivisionByZero::DivisionByZero()
	: m_error("Error: Division by zero") {}
const char* DivisionByZero::what() const noexcept {
	return m_error.c_str();
}