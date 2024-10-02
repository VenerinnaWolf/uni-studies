#pragma once

#include "Array.h"
#include "BitString.h"
#include "Decimal.h"
#include "Exceptions.h"

using std::cin;
using std::cout;
using std::endl;
using std::cerr;

class Application {
	Array* a;
	Array* b;
	Array* c;
public:
	void run();
	void TestArray();
	void TestBitString();
	void TestDecimal();
	void PrintMenu(std::string s);
};