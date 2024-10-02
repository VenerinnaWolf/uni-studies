#pragma once
#include "Triangle.h"
#include "EquilateralTriangle.h"
#include "IsoscelesTriangle.h"
#include "RectTriangle.h"

using std::cin;
using std::cout;
using std::endl;

class Application {
	Triangle* tr;
public:
	void run();
	void PrintMenu(std::string s);
};