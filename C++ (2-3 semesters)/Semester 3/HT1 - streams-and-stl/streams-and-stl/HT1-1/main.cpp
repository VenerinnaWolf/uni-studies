#include "Functions.h"

int main() {
	std::string fileName("MyFile.txt");
	std::string fileResult("result.txt");
	bool exit = false;
	int function_number;
	vector<int> vec;
	ifstream file;
	while (!exit) {
		cout << "Select the function:" << endl
			<< "    1) createDataFileStream" << endl
			<< "    2) createDataGenerateCopy" << endl
			<< "    3) loadDataFileStream" << endl
			<< "    4) loadDataIterCopy" << endl
			<< "    5) modify" << endl
			<< "    6) modifyIters" << endl
			<< "    7) modifyForEach" << endl
			<< "    8) modifyTransformFiles" << endl
			<< "    9) outputResultFileStream" << endl
			<< "    10) outputResultCopyIter" << endl
			<< "Or enter any other number to exit" << endl
			<< ">> ";
		cin >> function_number;
		cout << endl;
		switch (function_number)
		{
		case 1:
			createDataFileStream(fileName);
			file.open(fileName);
			cout << "File output:" << endl;
			if (!file.is_open()) cout << "File does not exist";
			else {
				for_each(istream_iterator<int>(file), istream_iterator<int>(), [](auto& s) {cout << s << " "; });
			}
			cout << endl << endl;
			file.close();
			break;
		case 2:
			createDataGenerateCopy(fileName);
			file.open("MyFile.txt");
			cout << "File output:" << endl;
			if (!file.is_open()) cout << "File does not exist";
			else {
				for_each(istream_iterator<int>(file), istream_iterator<int>(), [](auto& s) {cout << s << " "; });
			}
			cout << endl << endl;
			file.close();
			break;
		case 3:
			loadDataFileStream(vec, fileName);
			cout << "Container output:" << endl;
			for_each(vec.begin(), vec.end(), [](auto s) {cout << s << " "; });
			cout << endl << endl;
			break;
		case 4:
			loadDataIterCopy(vec, fileName);
			cout << "Container output:" << endl;
			for_each(vec.begin(), vec.end(), [](auto s) {cout << s << " "; });
			cout << endl << endl;
			break;
		case 5:
			modify(vec);
			cout << "Container output:" << endl;
			for_each(vec.begin(), vec.end(), [](auto s) {cout << s << " "; });
			cout << endl << endl;
			break;
		case 6:
			modifyIters(vec.begin(), vec.end());
			cout << "Container output:" << endl;
			for_each(vec.begin(), vec.end(), [](auto s) {cout << s << " "; });
			cout << endl << endl;
			break;
		case 7:
			modifyForEach(vec);
			cout << "Container output:" << endl;
			for_each(vec.begin(), vec.end(), [](auto s) {cout << s << " "; });
			cout << endl << endl;
			break;
		case 8:

			modifyTransformFiles(vec, fileName, fileResult);
			file.open(fileResult);
			cout << "File output:" << endl;
			if (!file.is_open()) cout << "File does not exist";
			else {
				for_each(istream_iterator<int>(file), istream_iterator<int>(), [](auto& s) {cout << s << " "; });
			}
			cout << endl << endl;
			file.close();
			break;
		case 9:
			outputResultFileStream(vec, fileName);
			file.open(fileName);
			cout << "File output:" << endl;
			if (!file.is_open()) cout << "File does not exist";
			else {
				for_each(istream_iterator<int>(file), istream_iterator<int>(), [](auto& s) {cout << s << " "; });
			}
			cout << endl << endl;
			file.close();
			break;
		case 10:
			outputResultCopyIter(vec, fileName);
			file.open(fileName);
			cout << "File output:" << endl;
			if (!file.is_open()) cout << "File does not exist";
			else {
				for_each(istream_iterator<int>(file), istream_iterator<int>(), [](auto& s) {cout << s << " "; });
			}
			cout << endl << endl;
			file.close();
			break;
		default:
			exit = true;
			break;
		}
	}
	file.close();
	return 0;
}