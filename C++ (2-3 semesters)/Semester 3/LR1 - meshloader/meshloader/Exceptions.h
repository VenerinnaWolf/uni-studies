#pragma once
#include <exception>
#include <string>

class FileIsNotFound : public std::exception {
private:
	std::string error;
public:
	FileIsNotFound(const std::string& error) noexcept;
	const char* what() const noexcept override;
};

FileIsNotFound::FileIsNotFound(const std::string& error) noexcept : error("The file " + error + " is not found ") {}

const char* FileIsNotFound::what() const noexcept {
	return error.c_str();
}