#include "EquilateralTriangle.h"

EquilateralTriangle::EquilateralTriangle(double side1, double side2, double angle) : Triangle(side1, side2, angle) {}

//!!! С какой целью явно оюъявлен конструктор копирования?

double EquilateralTriangle::Perimeter() {
	return 3 * m_side1;
}
double EquilateralTriangle::Area() {
	return m_side1 * m_side2 * sin(m_angle * PI / 180) / 2;
}


void EquilateralTriangle::GetTriangle() {
	std::cout << "Input side of an equilateral triangle: ";
	std::cin >> m_side1;
	m_side2 = m_side1;
	m_angle = 60.;
}


void EquilateralTriangle::PrintTriangle() {
	std::cout << "This is an equilateral triangle:" << std::endl;
	std::cout << "Side1 = side2 = side3 = " << m_side1 << ", angle = " << m_angle << " deg" << std::endl;
}