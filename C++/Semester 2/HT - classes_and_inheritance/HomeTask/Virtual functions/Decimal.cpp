#include "Decimal.h"
#include <cmath>
using std::max;
using std::min;

// 
//!!! Использовать =default при объявлении --- Исправлено

Decimal::Decimal(const int numOfElements, const unsigned char initialValue) : Array(numOfElements, initialValue) {}

//!!! Чем не устраивает автоматически создаваемый конструктор копирования? --- Исправлено - удалила конструктор копирования, дублиружщий функционал автоматически созданного

//  
void Decimal::Sum(const Array* arr, Array* result) {
	if (m_size != arr->getSize()) {
		throw InCompatibleDimException("Decimals are different sizes");
	}
	result->setSize(m_size + 1);

	unsigned char tmp = 0;
	for (int i = 0; i < m_size; i++) {
		tmp += m_arr[i] + (*arr)[i];
		if (tmp < 10) {
			(*result)[i] = tmp;
			tmp = 0;
		}
		if (tmp >= 10) {
			(*result)[i] = tmp - 10;
			tmp = 1;
		}
	}

	if (tmp == 1 && m_size < m_MAX_SIZE) (*result)[m_size] = 1;
	else result->changeSize(result->getSize() - 1);
}

Decimal Decimal::Resize(const int newSize) {
	Decimal newNum(newSize,0);
	for (int i = 0; i < this->m_size; i++) {
		newNum[i] = this->m_arr[i];
	}
	return newNum;
}

Decimal Decimal::Substract(const Decimal& num) {
	if (*this < num) {
		throw std::underflow_error("The second number is bigger than the first");
	}
	int maxSize = max(m_size, num.m_size);
	Decimal tmpNum1(*this);
	Decimal tmpNum2(num);
	if (m_size > num.m_size) {
		tmpNum2 = tmpNum2.Resize(maxSize);
	}
	if (m_size < num.m_size) {
		tmpNum1 = tmpNum1.Resize(maxSize);
	}	

	Decimal result(maxSize);
	unsigned char tmp = 0;
	for (int i = 0; i < maxSize; i++) {
		tmp = tmpNum1[i] - tmpNum2[i] - tmp;
		if (tmp >= 0) {
			result[i] = tmp;
			tmp = 0;
		}
		if (tmp < 0) {
			result[i] = tmp + 10;
			tmp = 1;
		}
	}

	return result;
}

Decimal Decimal::Multiply(const Decimal& num) {
	if (m_size + num.m_size > m_MAX_SIZE) {
		throw std::length_error("You are trying to muliply too big numbers, result will have more than 100 bits.");
	}

	Decimal result(m_size + num.m_size);
	for (int i = 0; i < num.m_size; i++) {
		unsigned char tmp = 0;
		int j;
		for (j = i; j < m_size + i; j++) {
			result[j] += (m_arr[j - i] * num[i] + tmp) % 10;
			tmp = (m_arr[j - i] * num[i] + tmp) / 10;
			if (result[j] >= 10) {
				tmp += result[j] / 10;
				result[j] %= 10;
			}
		}
		result[j] += tmp;
	}

	if (result[result.m_size - 1] == 0) result.changeSize(result.m_size - 1);

	return result;
}

//   
Decimal Decimal::Divide(const Decimal& num) {
	if (*this < num) {
		throw std::underflow_error("The second number is bigger than the first");
	}
	Decimal tmpResult(m_size - num.m_size + 1);
	long number2 = num[num.m_size-1];
	for (int i = num.m_size - 2; i >= 0; i--) {
		number2 *= 10;
		number2 += num[i];
	}

	int k = 0;
	long remainder = 0;
	for (int i = m_size - 1; i >= 0; i--) {
		long partOfNum1 = 0;
		for (int j = i; j >= 0; j--) {
			partOfNum1 *= 10;
			if (remainder != 0) {
				partOfNum1 += remainder;
				partOfNum1 *= 10;
				remainder = 0;
			}
			partOfNum1 += m_arr[j];
			if (partOfNum1 / number2 > 0) {
				tmpResult[tmpResult.m_size - k - 1] = partOfNum1 / number2;
				k++;
				remainder = partOfNum1 % number2;
				if (remainder != 0) i = j;
				else i = j - 1;
				break;
			}
		}
		if (partOfNum1 < number2) break;
	}

	if (k != tmpResult.m_size) {
		for (int i = 0; i < k; i++) {
			tmpResult[i] = tmpResult[i + tmpResult.m_size - k];
		}
		tmpResult.changeSize(k);
	}

	return tmpResult;
}

//  
bool operator>(const Decimal& num1, const Decimal& num2) {
	if (num1.m_size > num2.m_size) return true;
	if (num1.m_size < num2.m_size) return false;
	for (int i = num1.m_size; i >= 0; i--) {
		if (num1[i] > num2[i]) return true;
		if (num1[i] < num2[i]) return false;
	}
	return false;
}

bool operator>=(const Decimal& num1, const Decimal& num2) {
	if (num1.m_size > num2.m_size) return true;
	if (num1.m_size < num2.m_size) return false;
	for (int i = num1.m_size; i >= 0; i--) {
		if (num1[i] > num2[i]) return true;
		if (num1[i] < num2[i]) return false;
	}
	return true;
}

bool operator<(const Decimal& num1, const Decimal& num2) {
	if (num1.m_size < num2.m_size) return true;
	if (num1.m_size > num2.m_size) return false;
	for (int i = num1.m_size; i >= 0; i--) {
		if (num1[i] < num2[i]) return true;
		if (num1[i] > num2[i]) return false;
	}
	return false;
}

bool operator<=(const Decimal& num1, const Decimal& num2) {
	if (num1.m_size < num2.m_size) return true;
	if (num1.m_size > num2.m_size) return false;
	for (int i = num1.m_size; i >= 0; i--) {
		if (num1[i] < num2[i]) return true;
		if (num1[i] > num2[i]) return false;
	}
	return true;
}

bool operator==(const Decimal& num1, const Decimal& num2) {
	if (num1.m_size != num2.m_size) return false;
	for (int i = num1.m_size; i >= 0; i--) {
		if (num1[i] != num2[i]) return false;
	}
	return true;
}