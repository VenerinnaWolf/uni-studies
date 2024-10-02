#pragma once
#include <iostream>
#include "Exceptions.h"

class Array {
protected:
	unsigned char* m_arr;
	int m_size;
	const static int m_MAX_SIZE = 100;
public:
	// Конструкторы
	Array();
	Array(const int numOfElements, const unsigned char initialValue=0);
	Array(const Array& arr);

	// Деструктор
	virtual ~Array();

	// Операции
	unsigned char& operator[](const int index);
	const unsigned char& operator[](const int index) const;
	Array& operator=(const Array& arr);
	friend std::istream& operator>>(std::istream& in, Array& arr);
	friend std::ostream& operator<<(std::ostream& out, const Array& arr);

	int getSize() { return m_size; }
	int getSize() const { return m_size; }
	void setSize(const int newSize);
	void changeSize(const int newSize);

	// Виртуальная функция поэлементного сложения массивов
	virtual void Sum(const Array* arr, Array* result);
};