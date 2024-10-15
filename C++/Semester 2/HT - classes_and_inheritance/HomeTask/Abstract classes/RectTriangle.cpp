#include "RectTriangle.h"

RectTriangle::RectTriangle(double side1, double side2, double angle) : Triangle(side1, side2, angle) {}

//!!! Зачем явно объявлен конструктор копирования?

double RectTriangle::Perimeter() {
	return m_side1 + m_side2 + sqrt(m_side1*m_side1 + m_side2*m_side2);
}
double RectTriangle::Area() {
	return m_side1 * m_side2 / 2;
}

void RectTriangle::GetTriangle() {
	std::cout << "Input first side of a rectangular triangle: ";
	std::cin >> m_side1;
	std::cout << "Input second side of a rectangular triangle: ";
	std::cin >> m_side2;
	m_angle = 90;
}


void RectTriangle::PrintTriangle() {
	std::cout << "This is a rectangular triangle:" << std::endl;
	std::cout << "Side1 = " << m_side1 << ", side2 = " << m_side2 << ", angle = " << m_angle << " deg" << std::endl;
}