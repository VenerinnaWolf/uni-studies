#include "Matrix.h"
#include "Exceptions.h"

// 
CSRMatrix::CSRMatrix() : m_aelem(nullptr), m_iptr(nullptr), m_jptr(nullptr), m_nonZero(0), m_size(0) {}

CSRMatrix::CSRMatrix(int size, int nonZero) : m_size(size), m_nonZero(nonZero) {
	m_aelem = new double[nonZero];
	m_jptr = new int[nonZero];
	m_iptr = new int[size + 1];

	for (int i = 0; i < nonZero; i++) {
		m_aelem[i] = 0;
		m_jptr[i] = 0;
	}
	for (int i = 0; i < size + 1; i++) {
		m_iptr[i] = 0;
	}
}

CSRMatrix::CSRMatrix(const CSRMatrix& matrix) : m_size(matrix.m_size), m_nonZero(matrix.m_nonZero) {
	m_aelem = new double[m_nonZero];
	m_jptr = new int[m_nonZero];
	m_iptr = new int[m_size + 1];

	for (int i = 0; i < m_nonZero; i++) {
		m_aelem[i] = matrix.m_aelem[i];
		m_jptr[i] = matrix.m_jptr[i];
	}
	for (int i = 0; i < m_size + 1; i++) {
		m_iptr[i] = matrix.m_iptr[i];
	}
}

// 
CSRMatrix::~CSRMatrix() {
	delete[] m_aelem;
	delete[] m_iptr;
	delete[] m_jptr;
}

// 

// * (  )
CSRMatrix operator*(const CSRMatrix& matrix, const double value) {
	CSRMatrix newMatrix(matrix);
	for (int i = 0; i < matrix.m_nonZero; i++) {
		newMatrix.m_aelem[i] *= value;
	}
	return newMatrix;
}

// * (  )
CSRMatrix operator*(const double value, const CSRMatrix& matrix) {
	return matrix * value;
}

// =
CSRMatrix& CSRMatrix::operator=(const CSRMatrix& matrix) { //!!! Неверный тип возврата --- Исправлено
	if (this == &matrix) 
	    return *this;
	    
	if (m_size != matrix.m_size) {
		delete[] m_aelem;
		delete[] m_iptr;
		delete[] m_jptr;

		m_size = matrix.m_size;
		m_nonZero = matrix.m_nonZero;
		m_aelem = new double[m_nonZero];
		m_jptr = new int[m_nonZero];
		m_iptr = new int[m_size + 1];
	}

	for (int i = 0; i < m_nonZero; i++) {
		m_aelem[i] = matrix.m_aelem[i];
		m_jptr[i] = matrix.m_jptr[i];
	}
	
	for (int i = 0; i < m_size + 1; i++) {
		m_iptr[i] = matrix.m_iptr[i];
	}

	return *this;
}

// <<
std::ostream& operator<<(std::ostream& out, const CSRMatrix& matrix) {
	out << "aelem = (";
	for (int i = 0; i < matrix.m_nonZero - 1; i++) {
		out << matrix.m_aelem[i] << ", ";
	}
	out << matrix.m_aelem[matrix.m_nonZero-1] << ")" << std::endl;

	out << "jptr = (";
	for (int i = 0; i < matrix.m_nonZero - 1; i++) {
		out << matrix.m_jptr[i] << ", ";
	}
	out << matrix.m_jptr[matrix.m_nonZero-1] << ")" << std::endl;

	out << "iptr = (";
	for (int i = 0; i < matrix.m_size - 1; i++) {
		out << matrix.m_iptr[i] << ", ";
	}
	out << matrix.m_iptr[matrix.m_size-1] << ")" << std::endl;

	int k = 0, n = 0, m = 0;
	out << "Matrix:" << std::endl;
	for (int i = 0; i < matrix.m_size; ++i) {
		k = 0;
		for (int j = 0; j < matrix.m_size; ++j) {
			if ((matrix.m_jptr[n] == (j + 1)) && ((matrix.m_iptr[m + 1] - matrix.m_iptr[m]) > k)) {
				printf("%4.1lf ", matrix.m_aelem[n]);
				++n;
				++k;
			}
			else {
				printf("%4.1lf ", 0.);
			}
		}
		out << std::endl;
		++m;
	}

	return out;
}

// >>
std::istream& operator>>(std::istream& in, CSRMatrix& matrix) {
	int size;
	std::cout << "Input matrix size:" << std::endl;
	in >> size;

	int nonZero;
	std::cout << "Input number of non zero elements:" << std::endl;
	in >> nonZero;

	if ((size != matrix.m_size) && (nonZero != matrix.m_nonZero)) {
		delete[] matrix.m_aelem;
		delete[] matrix.m_jptr;
		delete[] matrix.m_iptr;

		matrix.m_size = size;
		matrix.m_nonZero = nonZero;
		matrix.m_aelem = new double[nonZero];
		matrix.m_jptr = new int[nonZero];
		matrix.m_iptr = new int[size + 1];
	}

	std::cout << "Input aelem:" << std::endl;
	for (int i = 0; i < nonZero; ++i) {
		in >> matrix.m_aelem[i];
	}

	std::cout << "Input jptr:" << std::endl;
	for (int i = 0; i < nonZero; ++i) {
		in >> matrix.m_jptr[i];
		if (matrix.m_jptr[i] > matrix.m_size) {
			throw OutOfRangeException();
		}
	}

	std::cout << "Input iptr:" << std::endl;
	for (int i = 0; i < size + 1; ++i) {
		in >> matrix.m_iptr[i];
	}

	return in;
}


// * (  )
Vector operator*(const CSRMatrix& matrix, const Vector& vector) {
	if (matrix.m_size != vector.m_size) {
		throw InCompatibleDimException("Matrix and Vector");
	}
	else {
		Vector result(vector.m_size);
		for (int i = 0; i < matrix.m_size; i++) {
			result[i] = 0;
			for (int j = matrix.m_iptr[i] - 1; j < matrix.m_iptr[i + 1] - 1; ++j) {
				result[i] += vector[matrix.m_jptr[j] - 1] * matrix.m_aelem[j];
			}
		}
		return result;
	}
}

// * (  )
Vector operator*(const Vector& vector, const CSRMatrix& matrix) {
	if (matrix.m_size != vector.m_size) {
		throw InCompatibleDimException("Matrix and Vector");
	}
	
	Vector result(vector.m_size);
	for (int i = 0; i < matrix.m_size; i++) {
		for (int j = matrix.m_iptr[i] - 1; j < matrix.m_iptr[i + 1] - 1; ++j) {
			result[matrix.m_jptr[j] - 1] += vector[i] * matrix.m_aelem[j];
		}
	}
	return result;
}