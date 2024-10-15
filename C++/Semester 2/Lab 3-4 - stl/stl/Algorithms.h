#pragma once
#include "Iterator.h"
#include <iostream>
#include <concepts>

// Выполнено задние на защиту
//!!! Задание на защиту
//!!! Реализовать концепции с основными ограничениями для шаблонов алгоритмов.

template<typename _IterType>
concept ConceptIter = requires(_IterType i, _IterType j, int k)
{
	{ ++i } -> std::same_as<_IterType&>;
	{ i++ } -> std::same_as<_IterType>;
	{ --i } -> std::same_as<_IterType&>;
	{ i-- } -> std::same_as<_IterType>;
	{ i + k } -> std::same_as<_IterType>;
	{ i - k } -> std::same_as<_IterType>;
	{ i += k } -> std::same_as<_IterType&>;
	{ i -= k } -> std::same_as<_IterType&>;
	{ i == j } -> std::same_as<bool>;
	{ i != j } -> std::same_as<bool>;
	{ i > j } -> std::same_as<bool>;
	{ i >= j } -> std::same_as<bool>;
	{ i < j } -> std::same_as<bool>;
	{ i <= j } -> std::same_as<bool>;
	{ *i } -> std::same_as<std::iter_reference_t<_IterType>>;
	*i = *j; 
	i = j;
};

template<typename _IterType, typename _Pred>
concept ConceptPred = requires(_Pred pred1, _Pred pred2, _IterType i)
{
	{pred1(*i)} -> std::same_as<bool>;
};

template<typename _IterType, typename _Pred>
concept ConceptLambda = requires(_Pred lambda, _IterType i)
{
	lambda(*i);
};

template<typename _IterType, typename _F>
requires ConceptIter<_IterType> && ConceptLambda<_IterType, _F>
_IterType findIf(_IterType beg, _IterType end, _F pred) {
	while (beg != end) {
		if (pred(*beg)) {
			break;
		}
		++beg;
	}
	_IterType res(beg);
	return res;
}

template<typename _IterType, typename _F>
requires ConceptIter<_IterType> && ConceptLambda<_IterType, _F>
_IterType minElement(_IterType beg, _IterType end, _F pred) {
	_IterType res = beg;
	while (beg != end) {
		if (pred(*res, *beg)) { //!!! Неверный предикат. Он не к double должен приводить, а быть бинарным придикатом, реализующим сравнение на < ---- Исправлено
			res = beg;
		}
		++beg;
	}
	return res;
}

template<typename _IterType, typename _F>
requires ConceptIter<_IterType>&& ConceptLambda<_IterType, _F>
_IterType maxElement(_IterType beg, _IterType end, _F pred) {
	_IterType res = beg;
	while (beg != end) {
		if (pred(*beg, *res)) { //!!! Неверный предикат. Он не к double должен приводить, а быть бинарным придикатом, реализующим сравнение на > ---- Исправлено
			res = beg;
		}
		++beg;
	}
	return res;
}

template<typename _IterType, typename _op>
requires ConceptIter<_IterType> && ConceptLambda<_IterType, _op>
void forEach(_IterType beg, _IterType end, _op op) {
	while (beg != end) {
		op(*beg);
		++beg;
	}
}

template <typename _IterType, typename _F>
requires ConceptIter<_IterType> && ConceptLambda<_IterType, _F>
void sort(_IterType beg, _IterType end, _F func) {
	for (; beg != end; beg++) {
		std::iter_swap(beg, minElement(beg, end, func));
	}
}

template<typename _IterType, typename _F>
requires ConceptIter<_IterType> && ConceptPred<_IterType, _F>
int copyIf(_IterType sourceBeg, _IterType sourceEnd, _IterType destBeg, _F pred) {
	int cntCopied = 0;
	while (sourceBeg != sourceEnd) {
		if (pred(*sourceBeg)) {
			*destBeg = *sourceBeg;
			++destBeg;
			++cntCopied;
		}
		++sourceBeg;
	}
	return cntCopied;
}