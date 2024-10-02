#include "Exceptions.h"

InCompatibleDimException::InCompatibleDimException(const std::string& error) : m_error(error) {}
const char* InCompatibleDimException::what() const noexcept {
	return m_error.c_str();
}