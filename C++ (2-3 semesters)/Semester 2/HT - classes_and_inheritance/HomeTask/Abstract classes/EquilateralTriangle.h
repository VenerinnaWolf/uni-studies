#pragma once
#include "Triangle.h"

//   
class EquilateralTriangle : public Triangle {
public:
	EquilateralTriangle() = default;
	EquilateralTriangle(double side1, double side2, double angle);

	//!!! virtual писать не обязательно, а вот override нужно --- Исправлено
	double Perimeter() override;
	double Area() override;
	void GetTriangle() override;
	void PrintTriangle() override;
};