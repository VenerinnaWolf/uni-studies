#pragma once
#include <iostream>
#include "Container.h"
#include "Exception.h"

template <class _DataType>
class Vector;

template <typename _DataType>
class  VectorIterator {
	friend class Vector<_DataType>;

	Vector <_DataType>* vec;
	int curI;
public:
	VectorIterator(Vector <_DataType>* _vec, int _curI) :curI(_curI), vec(_vec) {}

	VectorIterator(const VectorIterator& iter) : vec(iter.vec), curI(iter.curI) {}

	~VectorIterator() {
		vec = nullptr;
	}

	VectorIterator& operator++() {
		if ((curI + 1) >= (vec->capacity())) {
			throw std::exception("Iterator error: iterator tried to go out of range");
		}
		curI++;
		return *this;
	}

	VectorIterator operator++(int) {
		if ((curI + 1) >= (vec->capacity())) {
			throw std::exception("Iterator error: iterator tried to go out of range");
		}
		VectorIterator iter(*this);
		curI++;
		return iter;
	}

	VectorIterator& operator--() {
		if ((curI - 1) < 0) {
			throw std::exception("Iterator error: iterator tried to go out of range");
		}
		curI--;
		return *this;
	}

	VectorIterator operator--(int) {
		if ((curI - 1) < 0) {
			throw std::exception("Iterator error: iterator tried to go out of range");
		}
		VectorIterator iter(*this);
		curI--;
		return iter;
	}

	_DataType& operator*() const {
		return vec->array[curI];
	}

	VectorIterator& operator=(const VectorIterator& iter2) {
		if (this == &iter2) {
			return *this;
		}
		curI = iter2.curI;
		vec = iter2.vec;

		return *this;
	}

	VectorIterator operator+(const int num) {
		if ((vec->capacity()) <= ((curI)+num)) {
			throw std::exception("Iterator error: iterator tried to go out of range");
		}
		VectorIterator iter2(*this);
		(iter2.curI) += num;
		return iter2;
	}

	VectorIterator operator-(const int num) {
		if ((0) > ((curI)-num)) {
			throw std::exception("Iterator error: iterator tried to go out of range");
		}

		VectorIterator iter2(*this);
		(iter2.curI) -= num;
		return iter2;
	}

	bool operator == (const VectorIterator& iter2) const {
		return (vec == iter2.vec) && (curI == iter2.curI);
	}

	bool operator != (const VectorIterator& iter2) const {
		return ((vec != iter2.vec) || (curI != iter2.curI));
	}

	bool operator < (const VectorIterator& iter2) const {
		if ((vec) != iter2.vec) {
			throw std::exception("Iterator error: iterators are from different vectors");
		}

		return ((curI) < (iter2.curI));
	}

	bool operator <= (const VectorIterator& iter2) const {
		if ((vec) != iter2.vec) {
			throw std::exception("Iterator error: iterators are from different vectors");
		}

		return ((curI) <= (iter2.curI));
	}

	bool operator > (const VectorIterator& iter2) const {
		if ((vec) != iter2.vec) {
			throw std::exception("Iterator error: iterators are from different vectors");
		}

		return ((curI) > (iter2.curI));
	}

	bool operator >= (const VectorIterator& iter2) const {
		if ((vec) != iter2.vec) {
			throw std::exception("Iterator error: iterators are from different vectors");
		}

		return ((curI) >= (iter2.curI));
	}

	VectorIterator& operator+=(const int num) {
		if ((vec->capacity()) <= ((curI)+num)) {
			throw std::exception("Iterator error: iterator tried to go out of range");
		}
		(curI) += num;
		return *this;
	}

	VectorIterator& operator-=(const int num) {
		if ((vec->capacity()) <= ((curI)+num)) {
			throw std::exception("Iterator error: iterator tried to go out of range");
		}
		(curI) -= num;

		return *this;
	}

	_DataType* operator->() const {     
		return &(vec->array[curI]);										
	}

	explicit operator _DataType() { //!!! Запретить неявные преобразования ---- Исправлено
		return vec->at(curI);
	}
};