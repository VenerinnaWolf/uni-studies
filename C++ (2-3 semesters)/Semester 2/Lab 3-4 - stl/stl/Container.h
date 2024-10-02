#pragma once
#include "Iterator.h"
#include <iostream>

template <typename _DataType>
class Vector {
	friend class VectorIterator<_DataType>;

	_DataType* array;
	_DataType* vectorEnd;
	_DataType* memoryEnd;

public:
	using Iterator = VectorIterator<_DataType>;

	// Конструктор по умолчанию
	Vector() : array(nullptr), vectorEnd(nullptr), memoryEnd(nullptr) {
	}

	// Конструктор, принимающий количество элементов и значение, инициализирующее элементы вектора
	Vector(int size, const _DataType& initVal = _DataType()) {
		array = new _DataType[size * 2];
		memoryEnd = array + size * 2;
		vectorEnd = array + size;

		for (int i = 0; i < size; ++i) {
			array[i] = initVal;
		}
	}

	// Конструктор, принимающий интервал [beg, end), заданный итераторами
	template <class IterType>
	Vector(IterType beg, IterType end) {
		array = new _DataType[end - beg];
		memoryEnd = array + (end - beg);
		vectorEnd = array + (end - beg);
		Iterator tmp(beg);
		for (beg; beg != end; ++beg) {
			*tmp = *beg;
			++tmp;
		}
	}

	// Конструктор, принимающий список инициализации std::initializer_list
	Vector<_DataType>(const std::initializer_list<_DataType>& list) { 
		int size = list.size();
		int cap = size * 2;
		array = new _DataType[cap];
		memoryEnd = array + cap;
		vectorEnd = array + size;
		Iterator i(begin());
		for (auto I = list.begin(); I != list.end(); ++I) {  
			*i = *I;
			++i;
		}
	}

	// Копирующий конструктор
	Vector(const Vector& vector) {
		array = new _DataType[vector.memoryEnd];
		memoryEnd = array + vector.memoryEnd;
		vectorEnd = array + vector.vectorEnd();
		for (int i = 0; i < memoryEnd; ++i) {
			array[i] = vector.array[i];
		}
	}

	// Конструктор переноса	
	Vector(Vector&& vector) {
		memoryEnd = vector.memoryEnd;
		vectorEnd = vector.vectorEnd;
		array = vector.array;

		vector.array = nullptr;
		vector.memoryEnd = nullptr;
		vector.vectorEnd = nullptr;
	}

	// Деструктор
	~Vector() {
		delete[] array;
	}


	// Операторы

	Vector<_DataType>& operator=(const Vector<_DataType>& v) {
		if (this == &v) return *this;

		if (this->capacity() != v.capacity()) { //!!! Какой смысл сравнивать указатели у разных объектов? Видимо, capacity сравнивать нужно? ---- Исправлено
			delete[] array;
			array = new _DataType[v.capacity()];
		}

		memoryEnd = array + v.capacity();
		vectorEnd = array + v.size();

		for (int i = 0; i < capacity(); ++i) {
			array[i] = v.array[i];
		}
		return *this;
	}

	Vector& operator=(Vector&& v) {
		if (this == &v) {
			return *this;
		}
		delete[] array;
		memoryEnd = v.memoryEnd;
		vectorEnd = v.vectorEnd;
		array = v.array;
		v.array = nullptr;
		v.memoryEnd = nullptr;
		v.vectorEnd = nullptr;
		return *this;
	}

	_DataType& operator[](int i) {
		return array[i];
	}

	const _DataType& operator[](int i) const {
		return array[i];
	}


	// Методы

	const _DataType& at(int i) const {
		if (i > size() || i < 0) {
			throw OutOfRangeException(i);
		}
		return array[i];
	}

	_DataType& at(int i) {
		if (i > size() || i < 0) {
			throw OutOfRangeException(i);
		}
		return array[i];
	}

	Iterator begin() {
		return Iterator(this, 0);
	}

	Iterator end() {
		return Iterator(this, size());
	}

	void pushBack(const _DataType& elem) {

		int oldSize;
		if (array == nullptr) {
			array = new _DataType[2];
			vectorEnd = array;
			memoryEnd = array + 1;
			oldSize = 0;
		}
		else {
			oldSize = size();
			vectorEnd = vectorEnd + 1;
		}
		array[oldSize] = elem;
		if (capacity() == size()) {
			int cap = capacity();
			int size = this->size();
			_DataType* newArr = new _DataType[cap * 2];
			for (int i = 0; i < this->size(); ++i) {
				newArr[i] = array[i];
			}
			_DataType* buf = array;
			array = newArr;
			memoryEnd = array + cap * 2;
			vectorEnd = array + size;
			delete[] buf;
		}
	}

	void popBack() {
		if (size() != 0) {
			array[size() - 1] = _DataType();
			vectorEnd = array + size() - 2;
		}
	}

	Iterator insert(Iterator pos, const _DataType& elem) {
		if (this != pos.vec) {
			throw std::exception("Container error: attempt of using wrong iterator for this container");
		}
		vectorEnd = array + size();
		int cur = pos.curI;
		for (int i = size() - 1; i > cur; --i) {
			array[i] = array[i - 1];
		}
		array[cur] = elem;
		return pos;
	}

	template <class IterType>
	Iterator insert(Iterator pos, IterType beg, IterType end) {
		if (this != pos.vec) {
			throw std::exception("Container error: attempt of using wrong iterator for this container");
		}
		if (beg.vec != end.vec) {
			throw std::exception("Container error: attempt of using interval with different containers of begin and end iterators");
		}
		int delta = end.curI - beg.curI;
		_DataType* array2 = new _DataType[delta];
		for (int i = 0; i < delta; ++i) {
			array2[i] = (_DataType)beg;
			++beg;
		}
		int oldSize = size();
		resize(size() + delta);
		for (int i = size() - 1; i > pos.curI + delta - 1; --i) {
			array[i] = array[i - delta];
		}
		for (int i = pos.curI; i < pos.curI + delta; ++i) {
			array[i] = array2[i - pos.curI];
		}
		return pos;
	}

	Iterator erase(Iterator pos) {
		for (int c = pos.curI; c < size() - 1; ++c) {
			array[c] = array[c + 1];
		}
		vectorEnd = array + size() - 2;
		return pos;
	}

	void reserve(int num) {
		if (num < 0) {
			throw std::exception("Container error: attempt of decreasing of vector capacity (method reverse)");
		}
		if (num == 0) {
			return;
		}
		int cap = capacity() + num;
		int s = size();
		_DataType* newArr = new _DataType[cap];
		for (int i = 0; i < s; ++i) {
			newArr[i] = array[i];
		}
		_DataType* buf = array;
		array = newArr;
		memoryEnd = array + cap - 1;
		vectorEnd = array + s - 1;
		delete[] buf;
	}

	void resize(int num) {
		if (num < 0) {
			throw std::exception("Container error: attempt of changing vector's size to 0 or less (method resize)");
		}
		if (array == nullptr) {
			array = new _DataType[num * 2];
			memoryEnd = array + num * 2 - 1;
			vectorEnd = array + num - 1;
			for (int c = 0; c < size() - 1; ++c) {
				array[c] = _DataType();
			}
		}
		else {
			int oldSize = size();
			int s = num;
			int cap = capacity();
			if (s >= capacity()) {
				cap *= 2;
			}
			_DataType* oldArr = array;
			array = new _DataType[cap];
			memoryEnd = array + cap - 1;
			vectorEnd = array + s - 1;
			for (int c = 0; c < oldSize; ++c) {
				array[c] = oldArr[c];
			}
			for (int c = oldSize; c < s; ++c) {
				array[c] = _DataType();
			}
			delete[] oldArr;
		}

	}

	bool empty() {
		return array == vectorEnd;
	}

	int size() const {
		return vectorEnd - array + 1;
	}

	int capacity() const {
		return memoryEnd - array + 1;
	}

	void clear() {
		for (int i = 0; i < size(); ++i) {
			array[i] = _DataType();
		}
		vectorEnd = array;
	}
};