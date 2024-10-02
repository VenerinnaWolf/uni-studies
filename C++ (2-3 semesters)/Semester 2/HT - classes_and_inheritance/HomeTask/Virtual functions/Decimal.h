#pragma once
#include "Array.h"

//     
class Decimal : public Array {
public:
	// 
	Decimal() = default;
	Decimal(const int numOfElements, const unsigned char initialValue = 0);

	Decimal Resize(const int newSize);

	//  
	void Sum(const Array* arr, Array* result) override; //!!! Где override? --- Исправлено
	Decimal Substract(const Decimal& num);
	Decimal Multiply(const Decimal& num);
	Decimal Divide(const Decimal& num);

	//  
	friend bool operator>(const Decimal& num1, const Decimal& num2);
	friend bool operator>=(const Decimal& num1, const Decimal& num2);
	friend bool operator<(const Decimal& num1, const Decimal& num2);
	friend bool operator<=(const Decimal& num1, const Decimal& num2);
	friend bool operator==(const Decimal& num1, const Decimal& num2);
};