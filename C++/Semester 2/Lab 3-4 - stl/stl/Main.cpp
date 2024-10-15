#include "Container.h"
#include "Algorithms.h"
#include "Exception.h"
#include <initializer_list>
using std::cout;
using std::endl;

struct Staff {
	int m_id;
    std::string m_name;
    double m_price;

    Staff() noexcept : m_id(0), m_name(""), m_price(0.) {}

	Staff(int id, std::string name, double price) noexcept :
        m_id(id), m_name(name), m_price(price) {}

	friend bool isEmpty(const Staff& element) {
		return ((element.m_id == 0) && (element.m_name == "") && (element.m_price == 0));
	}

	friend std::ostream& operator << (std::ostream& output, const Staff& element) noexcept
	{
		if (&element != nullptr && !isEmpty(element))
		{
			output << element.m_id << endl;
			output << "Name of product: " << element.m_name << endl;
			output << "Price: " << element.m_price << endl;
			output << endl;
		}
		return output;
	}
};

int main()
{
	try {
		auto print = [](const auto& el) {
			cout << el;
		};

		cout << "-------- Vector1 creation --------" << endl;
		Vector<Staff> v1{ {1, "meat", 524}, {2, "chicken", 350}, {3, "chocolate", 120} };
		forEach(v1.begin(), v1.end(), print);

		cout << "-------- Vector2 creation (using pushBack) --------" << endl;
		Vector<Staff> v2;
		Staff a{ 4, "milk", 140 };
		v2.pushBack(a);
		Staff b{ 5, "juice", 200 };
		v2.pushBack(b);
		forEach(v2.begin(), v2.end(), print);

		cout << "-------- Testing insert --------" << endl;
		v1.insert(v1.end(), v2.begin(), v2.end());
		cout << "Vector1 + Vector2:" << endl;
		forEach(v1.begin(), v1.end(), print);

		cout << "-------- Testing sort --------" << endl;
		cout << "Sorting by price" << endl;
		sort(v1.begin(), v1.end(), [](const auto& el) { return el.m_price; } );
		forEach(v1.begin(), v1.end(), print);

		cout << "-------- Testing findIf --------" << endl;
		cout << "Trying to find milk in our vector" << endl;
		Vector<Staff>::Iterator result = findIf(v1.begin(), v1.end(), [](const auto& el) { return el.m_name == "milk"; } );
		print(*result);

		cout << "-------- Changing vector --------" << endl;
		cout << "Changing price of a milk in our vector" << endl;
		result->m_price = 230;
		forEach(v1.begin(), v1.end(), print);

		cout << "-------- Testing copyIf --------" << endl;
		cout << "Copying in vector 3 all staff with price below 250" << endl;
		Vector<Staff> v3(v1.size(), Staff());
		copyIf(v1.begin(), v1.end(), v3.begin(), [](const auto& el) { return el.m_price < 250; } );
		forEach(v3.begin(), v3.end(), print);
	}
	catch (const std::exception& error) {
		std::cerr << error.what();
	}

    return 0;
}