#pragma once
#include <iostream>
#include <map>
#include "bankomat.h"
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::map;

class Application {
	map<int, Bankomat> bankomats;
public:
	void run();
	void PrintMenu();
};