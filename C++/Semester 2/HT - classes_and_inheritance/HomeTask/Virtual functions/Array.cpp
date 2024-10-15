#include "Array.h"
using std::max;
using std::min;

// 
Array::Array()
    : m_arr(nullptr)
    , m_size(0)
{}

Array::Array(const int numOfElements, const unsigned char initialValue) 
    : m_size(numOfElements)
{
	if (numOfElements > m_MAX_SIZE) {
		throw std::length_error("Size is bigger than maxSize");
	}
	m_arr = new unsigned char[numOfElements];
	for (int i = 0; i < numOfElements; i++) {
		m_arr[i] = initialValue;
	}
}

Array::Array(const Array& arr) : m_size(arr.m_size) {
	m_arr = new unsigned char[arr.m_size];
	for (int i = 0; i < arr.m_size; i++) {
		m_arr[i] = arr.m_arr[i];
	}
}

// 
Array::~Array() {
	delete[] m_arr;
}

// 
unsigned char& Array::operator[](const int index){
	if (index < 0 || index > m_size) {
		throw std::out_of_range("Index is out of range");
	}
	return m_arr[index];
}

const unsigned char& Array::operator[](const int index) const {
	if (index < 0 || index > m_size) {
		throw std::out_of_range("Index is out of range");
	}
	return m_arr[index];
}

Array& Array::operator=(const Array& arr) {             //!!! Неверный тип возврата --- Исправлено
	if (this == &arr)
	    return *this;
	    
	if (m_size != arr.m_size) {
		delete[] m_arr;
		m_arr = new unsigned char[arr.m_size];
		m_size = arr.m_size;
	}
	
	for (int i = 0; i < m_size; i++) {
		m_arr[i] = arr.m_arr[i];
	}
	
	return *this;
}

std::istream& operator>>(std::istream& in, Array& arr) {
	std::cout << "Input array size: ";
	int size;
	in >> size;
	if (size != arr.m_size) {
		delete[] arr.m_arr;
		arr.m_size = size;
		arr.m_arr = new unsigned char[size];
	}
	std::cout << "Input array: ";
	for (int i = size - 1; i >= 0; i--) {
		int tmp;
		in >> tmp;
		arr.m_arr[i] = tmp;
	}
	return in;
}

//     , ..    
std::ostream& operator<<(std::ostream& out, const Array& arr) {
	out << "[";
	for (int i = arr.m_size - 1; i > 0; i--) {
		out << (int)arr[i] << " ";
	}
	out << (int)arr[0] << "]";
	return out;
}

//     
void Array::Sum(const Array* arr, Array* result) {
	if (m_size != arr->m_size) {
		throw InCompatibleDimException("Arrays are different sizes");
	}
	result->m_size = m_size;
	delete[] result->m_arr;
	result->m_arr = new unsigned char[m_size];
	for (int i = 0; i < m_size; i++) {
		result->m_arr[i] = m_arr[i] + arr->m_arr[i];
	}
}

void Array::setSize(const int newSize) {
	if (newSize > m_MAX_SIZE) {
		throw std::length_error("Size is bigger than maxSize");
	}
	m_size = newSize;
	m_arr = new unsigned char[newSize];
}

void Array::changeSize(const int newSize) {
	if (newSize > m_MAX_SIZE) {
		throw std::length_error("Size is bigger than maxSize");
	}
	m_size = newSize;
}