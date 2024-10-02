#pragma once
#include <iostream>
#include <exception>
#include <string>

class OutOfRangeException : public std::exception
{
	std::string err;
public:
	OutOfRangeException(int id)
	{
		err = "Out of range error: index = " + std::to_string(id) + " is out of range";
	}
	const char* what() const noexcept override
	{
		return err.c_str();
	}
};

