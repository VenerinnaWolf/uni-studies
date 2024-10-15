#include "IsoscelesTriangle.h"

IsoscelessTriangle::IsoscelessTriangle(double side1, double side2, double angle) : Triangle(side1, side2, angle) {}

//!!! Зачем явно объявлен конструктор копирования?

double IsoscelessTriangle::Perimeter() {
	return m_side1 + m_side2 + sqrt(m_side1 * m_side1 + m_side2 * m_side2 - 2 * m_side1 * m_side2 * cos(m_angle * PI / 180));
}
double IsoscelessTriangle::Area() {
	return m_side1 * m_side2 * sin(m_angle * PI / 180) / 2;
}


void IsoscelessTriangle::GetTriangle() {
	std::cout << "Input side of an isosceless triangle: ";
	std::cin >> m_side1;
	m_side2 = m_side1;
	std::cout << "Input apex angle (between two equal sides): ";
	std::cin >> m_angle;
}


void IsoscelessTriangle::PrintTriangle() {
	std::cout << "This is an isosceless triangle:" << std::endl;
	std::cout << "Side1 = side2 = " << m_side1 << ", angle between them = " << m_angle << " deg" << std::endl;
}