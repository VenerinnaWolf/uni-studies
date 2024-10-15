#pragma once
#include <iostream>
#include <math.h>

class CSRMatrix;

class Vector
{
	int m_size;
	double* m_arr;
public:
	// ������������
	Vector(); // �� ���������
	explicit Vector(const int size); 
	Vector(const Vector& vector); // ���������� �����������

	// ����������
	~Vector();

	// ���������
	// =
	Vector& operator=(const Vector& vector);
	// +=
	Vector& operator+=(const Vector& vector);
	// -=
	Vector& operator-=(const Vector& vector);
	// + (��������)
	friend Vector operator+(const Vector& vector1, const Vector& vector2);
	// + (�������)
	const Vector& operator+() const;
	// - (��������)
	friend Vector operator-(const Vector& vector1, const Vector& vector2);
	// - (�������)
	Vector operator-() const;
	// * (������������ ������� �� �����)
	friend Vector operator*(const Vector& vector, const double value);
	// * (������������ ����� �� ������)
	friend Vector operator*(const double value, const Vector& vector);
	// * (������������ ������� �� ������ (��������))
	friend double operator*(const Vector& vector1, const Vector& vector2);
	// []
	double& operator[](const int index);
	const double& operator[](const int index) const;
	// <<
	friend std::ostream& operator<<(std::ostream& out, const Vector& vector);
	// >>
	friend std::istream& operator>>(std::istream& in, Vector& vector);
	// �������� ���������� ���� � ��������� �� double
	operator double*() const;

	// * (������������ ������� �� ������)
	friend Vector operator*(const CSRMatrix& matrix, const Vector& vector);
	// * (������������ ������� �� �������)
	friend Vector operator*(const Vector& vector, const CSRMatrix& matrix);

	// ���������� ����� �������
	double getLength () const;
	// ����������� �������
	int getSize() const { return m_size; }
};

