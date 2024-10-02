#include "Vector.h"
#include "Exceptions.h"
 
// 
Vector::Vector() : m_size(0), m_arr(nullptr) {};

Vector::Vector(const int size) : m_size(size) {
	m_arr = new double[size];
	for (int i = 0; i < size; i++) {
		m_arr[i] = 0;
	}
}

Vector::Vector(const Vector& vector) : m_size(vector.m_size) {
	m_arr = new double[vector.m_size];
	for (int i = 0; i < vector.m_size; i++) {
		m_arr[i] = vector.m_arr[i];
	}
}

// 
Vector::~Vector() {
	delete[] m_arr;
}

// 

// =
Vector& Vector::operator=(const Vector& vector) { //!!! Неверный тип возврата --- Исправлено
	if (this == &vector) 
	    return *this;
	    
	if (m_size != vector.m_size) {
		delete[] m_arr;
		m_arr = new double[vector.m_size];
		m_size = vector.m_size;
	}
	
	for (int i = 0; i < m_size; i++) {
		m_arr[i] = vector.m_arr[i];
	}
	
	return *this;
}

// +=
Vector& Vector::operator+=(const Vector& vector) { //!!! Неверный тип возврата --- Исправлено
	if (m_size != vector.m_size) {
		throw InCompatibleDimException("Vectors");
	}
	else {
		for (int i = 0; i < m_size; i++) {
			m_arr[i] += vector.m_arr[i];
		}
		return *this;
	}
}

// -=
Vector& Vector::operator-=(const Vector& vector) {//!!! Неверный тип возврата --- Исправлено
	if (m_size != vector.m_size) {
		throw InCompatibleDimException("Vectors");
	}
	else {
		for (int i = 0; i < m_size; i++) {
			m_arr[i] -= vector.m_arr[i];
		}
		return *this;
	}
}

// + ()
Vector operator+(const Vector& vector1, const Vector& vector2) {
	if (vector1.m_size != vector2.m_size) {
		throw InCompatibleDimException("Vectors");
	}
	else {
		Vector newVector(vector1);
		for (int i = 0; i < vector1.m_size; i++) {
			newVector.m_arr[i] += vector2.m_arr[i];
		}
		return newVector;
	}
}

// + ()
const Vector& Vector::operator+() const { //!!! Лишнее копирование при возврате --- Исправлено
	return *this;
}

// - ()
Vector operator-(const Vector& vector1, const Vector& vector2) {
	if (vector1.m_size != vector2.m_size) {
		throw InCompatibleDimException("Vectors");
	}
	else {
		Vector newVector(vector1);
		for (int i = 0; i < vector1.m_size; i++) {
			newVector.m_arr[i] -= vector2.m_arr[i];
		}
		return newVector;
	}
}

// - ()
Vector Vector::operator-() const {
	return *this*(-1.);
}

// * (   )
Vector operator*(const Vector& vector, const double value) {
	Vector newVector(vector);
	for (int i = 0; i < vector.m_size; i++) {
		newVector.m_arr[i] *= value;
	}
	return newVector;
}

// * (   )
Vector operator*(const double value, const Vector& vector) {
	return vector * value;
}

// * (    ())
double operator*(const Vector& vector1, const Vector& vector2) {
	if (vector1.m_size != vector2.m_size) {
		throw InCompatibleDimException("Vectors");
	}
	else {
		double value = 0;
		for (int i = 0; i < vector1.m_size; i++) {
			value += vector1.m_arr[i] * vector2.m_arr[i];
		}
		return value;
	}
}

//!!! Должно быть 2 версии оператора: константная (дляч чтения) и не константная (для записи) --- Исправлено
double& Vector::operator[](const int index) {
	if (index < 0 || index > m_size) {
		throw OutOfRangeException();
	}
	else return m_arr[index];
}

const double& Vector::operator[](const int index) const {
	if (index < 0 || index > m_size) {
		throw OutOfRangeException();
	}
	else return m_arr[index];
}

// <<
std::ostream& operator<<(std::ostream& out, const Vector& vector) {
	out << "(";
	for (int i = 0; i < vector.m_size - 1; i++) {
		out << vector.m_arr[i] << ", ";
	}
	out << vector.m_arr[vector.m_size - 1] << ")";
	return out;
}

// >>
std::istream& operator>>(std::istream& in, Vector& vector) {
	std::cout << "Input vector size: ";
	int size;
	in >> size;

	if (size != vector.m_size) {		
		delete[] vector.m_arr;
		vector.m_size = size;
		vector.m_arr = new double[size];
	}

	std::cout << "Input vector: ";
	for (int i = 0; i < size; i++) {
		in >> vector.m_arr[i];
	}

	return in;
}

//       double
Vector::operator double*() const {
	return m_arr;
}

//   
double Vector::getLength() const {
	double length = 0;
	for (int i = 0; i < m_size; i++) {
		length += m_arr[i] * m_arr[i];
	}
	length = sqrt(length);
	return length;
}