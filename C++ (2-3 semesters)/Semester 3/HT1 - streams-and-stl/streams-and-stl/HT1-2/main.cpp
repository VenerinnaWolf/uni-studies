#include "Functions.h"
#include "FileRecord.h"

int main() {
	std::string filename;
	std::string filename_to_convert;
	std::cout << "Enter the file name: ";
	std::cin >> filename;
	std::cout << std::endl << "Entering the first entry:" << std::endl;
	Primary_input(filename);
	bool Continue = true;
	int switch_on;
	while (Continue) {
		std::cout << "Select an action:" << std::endl
			<< "\t1 - add record" << std::endl
			<< "\t2 - delete record" << std::endl
			<< "\t3 - replace record" << std::endl
			<< "\t4 - search for records" << std::endl
			<< "\t5 - convert to a text file" << std::endl
			<< "Or enter any other number to exit" << std::endl << ">> ";
		std::cin >> switch_on;
		std::cout << std::endl;
		switch (switch_on)
		{
		case 1:
			Add_to_file(filename);
			break;
		case 2:
			Delete_a_record(filename);
			break;
		case 3:
			Replace_record(filename);
			break;
		case 4:
			Search_for_records(filename);
			break;
		case 5:
			std::cout << "Enter the name of file you want to convert: ";
			std::cin >> filename_to_convert;
			Convert_to_a_text_file(filename_to_convert);
			break;
		default:
			Continue = false;
			break;
		}
	}
	return 0;
}