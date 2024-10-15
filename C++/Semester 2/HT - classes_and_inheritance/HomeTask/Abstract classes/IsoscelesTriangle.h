#pragma once
#include "Triangle.h"

//   
class IsoscelessTriangle : public Triangle {
public:
	IsoscelessTriangle() = default;
	IsoscelessTriangle(double side1, double side2, double angle);

	//!!! virtual писать не обязательно, а вот override нужно --- Исправлено
	double Perimeter() override;
	double Area() override;
	void GetTriangle() override;
	void PrintTriangle() override;
};