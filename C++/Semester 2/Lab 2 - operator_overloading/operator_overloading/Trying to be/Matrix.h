#pragma once
#include "Vector.h"

class Vector;

// Симметричные матрицы
class CSRMatrix
{
	// Все ненулевые элементы матрицы в строчном порядке
	double* m_aelem; 
	// Номер столбца каждого элемента из m_aelem
	int* m_jptr;
	// Количество элементов, с которого начинается каждая i-я строка матрицы
	int* m_iptr;
	// Размерность матрицы
	int m_size; 
	// Количество ненулевых элементов
	int m_nonZero;
public:
	// Конструкторы
	CSRMatrix();
	CSRMatrix(int size, int nonZero);
	CSRMatrix(const CSRMatrix& matrix);

	// Деструктор
	~CSRMatrix();

	// Операторы
	
	// * (матрицы на число)
	friend CSRMatrix operator*(const CSRMatrix& matrix, const double value);
	// * (числа на матрицу)
	friend CSRMatrix operator*(const double value, const CSRMatrix& matrix);
	// =
	CSRMatrix& operator=(const CSRMatrix& matrix);
	// <<
	friend std::ostream& operator<<(std::ostream& out, const CSRMatrix& matrix);
	// >>
	friend std::istream& operator>>(std::istream& in, CSRMatrix& matrix);
	// * (произведение матрицы на вектор)
	friend Vector operator*(const CSRMatrix& matrix, const Vector& vector);
	// * (произведение вектора на матрицу)
	friend Vector operator*(const Vector& vector, const CSRMatrix& matrix);

	// Размерность матрицы
	int getSize() const { return m_size; }
	// Количество ненулевых элементов
	int getNonZeros() const { return m_nonZero; }
};