#pragma once
#include <iostream>
#include <math.h>

#define PI 3.14159265

//    
class Triangle {
protected:
	double m_side1;
	double m_side2;
	double m_angle;
public:
	Triangle() = default;
	Triangle(double side1, double side2, double angle);
		
    //!!! Где виртуальный декструктор? --- Исправлено
	virtual ~Triangle();

	//  
	virtual double Perimeter() = 0;
	//  
	virtual double Area() = 0;

	//   
	virtual void GetTriangle() = 0;
	//   
	virtual void PrintTriangle() = 0;
};