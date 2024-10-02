#include "Exceptions.h"

InCompatibleDimException::InCompatibleDimException(const std::string& error) 
	: m_error("Error: " + error + " are different sizes.\n") {}
const char* InCompatibleDimException::what() const noexcept {
	return m_error.c_str();
}

OutOfRangeException::OutOfRangeException()
	: m_error("Error: Index is out of range.\n") {}
const char* OutOfRangeException::what() const noexcept {
	return m_error.c_str();
}