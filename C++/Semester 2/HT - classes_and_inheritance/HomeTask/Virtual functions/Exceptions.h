#pragma once
#include <string>
#include <exception>

class InCompatibleDimException : public std::exception {
	std::string m_error;
public:
	InCompatibleDimException(const std::string& error);
	const char* what() const noexcept;
};