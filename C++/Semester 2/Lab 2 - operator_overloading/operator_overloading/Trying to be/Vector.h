#pragma once
#include <iostream>
#include <math.h>

class CSRMatrix;

class Vector
{
	int m_size;
	double* m_arr;
public:
	//  онструкторы
	Vector(); // ѕо умолчанию
	explicit Vector(const int size); 
	Vector(const Vector& vector); //  опирующий конструктор

	// ƒеструктор
	~Vector();

	// ќператоры
	// =
	Vector& operator=(const Vector& vector);
	// +=
	Vector& operator+=(const Vector& vector);
	// -=
	Vector& operator-=(const Vector& vector);
	// + (бинарный)
	friend Vector operator+(const Vector& vector1, const Vector& vector2);
	// + (унарный)
	const Vector& operator+() const;
	// - (бинарный)
	friend Vector operator-(const Vector& vector1, const Vector& vector2);
	// - (унарный)
	Vector operator-() const;
	// * (произведение вектора на число)
	friend Vector operator*(const Vector& vector, const double value);
	// * (произведение числа на вектор)
	friend Vector operator*(const double value, const Vector& vector);
	// * (произведение вектора на вектор (скал€рно))
	friend double operator*(const Vector& vector1, const Vector& vector2);
	// []
	double& operator[](const int index);
	const double& operator[](const int index) const;
	// <<
	friend std::ostream& operator<<(std::ostream& out, const Vector& vector);
	// >>
	friend std::istream& operator>>(std::istream& in, Vector& vector);
	// ќператор приведени€ типа к указателю на double
	operator double*() const;

	// * (произведение матрицы на вектор)
	friend Vector operator*(const CSRMatrix& matrix, const Vector& vector);
	// * (произведение вектора на матрицу)
	friend Vector operator*(const Vector& vector, const CSRMatrix& matrix);

	// Ќахождение длины вектора
	double getLength () const;
	// –азмерность вектора
	int getSize() const { return m_size; }
};

