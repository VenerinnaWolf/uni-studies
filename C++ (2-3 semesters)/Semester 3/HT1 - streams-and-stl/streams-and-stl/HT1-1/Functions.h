#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <list>
#include <deque>
#include <functional>
#include <iomanip>

using namespace std;

void createDataFileStream(std::string fileName) {
	ofstream file(fileName);
	srand(time(nullptr));
	if (!file.is_open()) cout << "File does not exist";
	else {
		for (int i = 0; i < 100; i++) {
			int a = rand() % 101 - 50;
			file << a << " ";
		}
	}
	file.close();
}

void createDataGenerateCopy(std::string fileName) {
	vector<int> vec(100);
	ofstream file(fileName);
	srand(time(nullptr));
	if (!file.is_open()) cout << "File does not exist";
	else {
		generate(vec.begin(), vec.end(), []() {return rand() % 101 - 50; });
		copy(vec.begin(), vec.end(), ostream_iterator<int>(file, " "));
	}
	file.close();
}

template <typename T>
void loadDataFileStream(T& container, std::string fileName) {
	ifstream file(fileName);
	if (!file.is_open()) cout << "File does not exist";
	else {
		for (int i = 0; i < 100; i++) {
			int a;
			file >> a;
			container.push_back(a);
		}
	}
	file.close();
}

template <typename T>
void loadDataIterCopy(T& container, std::string fileName) {
	ifstream file(fileName);
	if (!file.is_open()) cout << "File does not exist";
	else {
        // ПЕРЕД ЗАВИСИМЫМИ ТИПАМИ НАДО ПИСАТЬ КЛЮЧЕВОЕ СЛОВО typename  ------------- Исправлено (хотя у меня компилировалось и без этого)
        // НЕ КОМПИЛИРУЕТСЯ ЖЕ
        copy(istream_iterator<typename T::value_type>(file), istream_iterator<typename T::value_type>(), back_inserter(container));
	}
	file.close();
}

template<typename T>
// Разделить все нечетные по абсолютной величине числа на среднее арифметическое
void modify(T& container) {
	float average = 0;
	for_each(container.begin(), container.end(), [&average](const auto& elem) { average += elem; });
	average = average / container.size();
	int sum = 0;
	int abs_sum = 0;
	for (auto& elem : container) {
		if (abs(elem) % 2 != 0) elem = elem / average;
		sum += elem;
		abs_sum += abs(elem);
	}
	container.push_back(sum);
	container.push_back(abs_sum / container.size());
}

template<typename T>
void modifyIters(T Iter_begin, T Iter_end) {
	float average = 0;
	for_each(Iter_begin, Iter_end, [&average](const auto& elem) { average += elem; });
	average = average / distance(Iter_begin, Iter_end);
	for_each(Iter_begin, Iter_end, [average](auto& elem) { if (abs(elem) % 2 != 0) elem = elem / average; });
}

template<typename T>
void modifyForEach(T& container) {
	float average = 0;
	for_each(container.begin(), container.end(), [&average](const auto& elem) { average += elem; });
	average = average / container.size();
	for_each(container.begin(), container.end(), [average](auto& elem) { if (abs(elem) % 2 != 0) elem = elem / average; });
}

template<typename T>
void modifyTransformFiles(T& container, std::string fileName, std::string fileResult) {
	ifstream file(fileName);
    // typename ------------- Исправлено
	vector<typename T::value_type> buf(100);
	if (!file.is_open()) cout << "File does not exist";
	else {
        // typename ------------- Исправлено
        copy(istream_iterator<typename T::value_type>(file), istream_iterator<typename T::value_type>(), buf.begin());
	}
	file.close();
	float average = 0;
	for_each(buf.begin(), buf.end(), [&average](const auto& elem) { average += elem; });
	average = average / buf.size();
	ofstream fout(fileResult);
	transform(buf.begin(), buf.end(), ostream_iterator<int>(fout, " "), [average](auto& elem) { if (abs(elem) % 2 != 0) return int(elem / average); else return elem; });
}

template<typename T>
void outputResultFileStream(T& container, std::string fileName) {
	ofstream file(fileName);
	if (!file.is_open()) cout << "File does not exist";
	else {
        // НЕ ВСЕ ИТЕРАТОРЫ ПОДДЕРЖИВАЮТ ОПЕРАТОР МЕНЬШЕ ------------- Исправлено
		auto a = container.begin();
		while (a != container.end()) {
			file << *a << " ";
			++a;
		}
	}
	file.close();
}

template<typename T>
void outputResultCopyIter(T& container, std::string fileName) {
	ofstream file(fileName);
	if (!file.is_open()) cout << "File does not exist";
	else {
		copy(container.begin(), container.end(), ostream_iterator<int>(file, " "));
	}
	file.close();
}
