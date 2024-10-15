#pragma once
#include "Array.h"

//   
class BitString : public Array {
public:
	// 
	BitString() = default;
	BitString(const int numOfElements, const unsigned char initialValue = 0);

	//    
	BitString And(const BitString& str) const;
	BitString Or(const BitString& str) const;
	BitString Xor(const BitString& str) const;
	BitString Not() const;
	BitString MoveLeft(const int number);
	BitString MoveRight(const int number);

	void Sum(const Array* arr, Array* result) override; //!!! Нужно использовать override --- Исправлено
};