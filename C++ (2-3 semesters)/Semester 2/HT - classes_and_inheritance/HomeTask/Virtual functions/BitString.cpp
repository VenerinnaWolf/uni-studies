#include "BitString.h"

// 
//!!! Зачем писать пустой конструктор? Нужно использовать =default при объявлении --- Исправлено

BitString::BitString(const int numOfElements, const unsigned char initialValue) : Array(numOfElements, initialValue) {}

//!!! Чем не устраивает автоматически создаваемый конструтор копирования? --- Исправлено - удалила конструктор копирования, дублиружщий функционал автоматически созданного

//    
BitString BitString::And(const BitString& str) const {
	if (m_size != str.m_size) {
		throw InCompatibleDimException("Bit strings are different sizes");
	}
	BitString result(m_size);
	for (int i = 0; i < m_size; i++) {
		if (m_arr[i] == 1 && str[i] == 1) result[i] = 1;
		else result[i] = 0;
	}
	return result;
}

BitString BitString::Or(const BitString& str) const {
	if (m_size != str.m_size) {
		throw InCompatibleDimException("Bit strings are different sizes");
	}
	BitString result(m_size);
	for (int i = 0; i < m_size; i++) {
		if (m_arr[i] == 0 && str[i] == 0) result[i] = 0;
		else result[i] = 1;
	}
	return result;
}

BitString BitString::Xor(const BitString& str) const {
	if (m_size != str.m_size) {
		throw InCompatibleDimException("Bit strings are different sizes");
	}
	BitString result(m_size);
	for (int i = 0; i < m_size; i++) {
		if ((m_arr[i] == 1 || str[i] == 1) && m_arr[i] != str[i]) result[i] = 1;
		else result[i] = 0;
	}
	return result;
}

BitString BitString::Not() const {
	BitString result(m_size);
	for (int i = 0; i < m_size; i++) {
		if (m_arr[i] == 1) result[i] = 0;
		else result[i] = 1;
	}
	return result;
}

BitString BitString::MoveRight(const int number) {
	if (number < 0 || number > m_size) {
		throw std::out_of_range("Number is out of range");
	}
	BitString result(*this);
	for (int i = 0; i < m_size - number; i++) {
		result[i] = result[i + number];
	}
	for (int i = m_size - number; i < m_size; i++) {
		result[i] = 0;
	}
	return result;
}

BitString BitString::MoveLeft(const int number) {
	if (number < 0 || number > m_size) {
		throw std::out_of_range("Number is out of range");
	}
	BitString result(*this);
	for (int i = m_size - 1; i > number - 1; i--) {
		result[i] = result[i - number];
	}
	for (int i = number - 1; i >= 0; i--) {
		result[i] = 0;
	}
	return result;
}

void BitString::Sum(const Array* arr, Array* result) {
	if (m_size != arr->getSize()) {
		throw InCompatibleDimException("Bit strings are different sizes");
	}
	result->setSize(m_size + 1);

	unsigned char tmp = 0;
	for (int i = 0; i < m_size; i++) {
		tmp += m_arr[i] + (*arr)[i];
		if (tmp < 2) {
			(*result)[i] = tmp;
			tmp = 0;
		}
		if (tmp >= 2) {
			(*result)[i] = tmp - 2;
			tmp = 1;
		}
	}
	if (tmp == 1 && m_size < m_MAX_SIZE) (*result)[m_size] = 1;
	else result->changeSize(result->getSize() - 1);
}