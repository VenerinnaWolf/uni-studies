#pragma once
#include "Triangle.h"

//   
class RectTriangle : public Triangle {
public:
	RectTriangle() = default;
	RectTriangle(double side1, double side2, double angle);

    //!!! virtual писать не обязательно, а вот override нужно --- Исправлено
	double Perimeter() override;
	double Area() override;
	void GetTriangle() override;
	void PrintTriangle() override;
};