#include "Triangle.h"

Triangle::Triangle(double side1, double side2, double angle) :
	m_angle(angle),
	m_side1(side1),
	m_side2(side2) {}

Triangle::~Triangle() {}

//!!! Зачем явно объявлен конструктор колпирования? У вас указатели среди полей есть? --- Исправлено. Все конструкторы копирования удалила
