#include "Functions.h"
#include "FileRecord.h"

void Primary_input(const std::string& filename) {
	std::ofstream file(filename + ".bin", std::ios::out | std::ios::binary | std::ios::app);
	if (!file.is_open()) {
		std::cout << "Error: the file did not open!" << std::endl << std::endl;
	}
	else {
		bool Indicator = true;
		FileRecord elem;
		while (Indicator) {
			elem.NewFileRecord();
			file.write(reinterpret_cast<char*>(&elem), sizeof(FileRecord));
			std::cout << std::endl << "Add another item entry to the file?" << std::endl 
				<< "\t1 - yes" << std::endl 
				<< "\t0 - no" << std::endl << ">> ";
			std::cin >> Indicator;
			std::cout << std::endl;
		}
	}
	file.close();
}

void Add_to_file(const std::string& filename) {
	Primary_input(filename);
}

void Delete_a_record(const std::string& filename) {
	std::ifstream file(filename + ".bin", std::ios::binary);
	if (!file) {
		std::cout << "Error: the file did not open!" << std::endl << std::endl;
	}
	else {
		int num;
		std::cout << "Enter the record number to delete: ";
		std::cin >> num;
		List_FileRecords records;
		records.Input(file);
		file.close();
        // НЕ НАДО ДАВАТЬ ДОСТУП ПО ССЫЛКЕ К ЗАКРЫТОЙ ЧАСТИ КЛАССА  ---------- Исправлено
        // ВМЕСТО ЭТОГО НАПИШИ ФУНКЦИЮ erase ДЛЯ КЛАССА List_FileRecords,
        // КОТОРАЯ И БУДЕТ УДАЛЯТЬ ЗАПИСЬ
		records.erase_record(num);
		std::ofstream file(filename + ".bin", std::ios::binary);
		records.Output(file);
		std::cout << std::endl;
	}
	file.close();
}

void Replace_record(const std::string& filename) {
	std::ifstream file(filename + ".bin", std::ios::binary);
	if (!file) {
		std::cout << "Error: the file did not open!" << std::endl << std::endl;
	}
	else {
		int num;
		std::cout << "Enter the record number to replace: ";
		std::cin >> num;
		List_FileRecords records;
		records.Input(file);
		file.close();
		FileRecord record;
		record.NewFileRecord();
        // ТОЖЕ НАДО НАПИСАТЬ МЕТОД КЛАССА ДЛЯ ЗАМЕНЫ ЗАПИСИ ---------- Исправлено
		records.replace_record(num, record);
		std::ofstream file(filename + ".bin", std::ios::binary);
		records.Output(file);
		std::cout << std::endl;
	}
	file.close();
}

void Search_for_records(const std::string& filename) {
	std::ifstream file(filename + ".bin", std::ios::binary);
	if (!file) {
		std::cout << "Error: the file did not open!" << std::endl << std::endl;
	}
	else {
		std::string Newfilename;
		std::cout << "Enter a file name to save the found records: ";
		std::cin >> Newfilename;
		List_FileRecords records;
		records.Input(file);
		file.close();
		std::cout << "Search by..." << std::endl
			<< "\t1 - directory" << std::endl
			<< "\t2 - date" << std::endl
			<< "\t3 - deletion flag" << std::endl << ">> ";
		int switch_on;
		std::cin >> switch_on;
		switch (switch_on)
		{
		case 1:
			records = (records.Search_by_directory());
			break;
		case 2:
			records = (records.Search_by_date());
			break;
		case 3:
			records = (records.Search_by_deletion_flag());
			break;
		default:
			std::cout << "Wrong input" << std::endl;
			break;
		}
		std::ofstream file(Newfilename + ".bin", std::ios::binary);

		records.Output(file);
		std::cout << std::endl;
	}
	file.close();
}

void Convert_to_a_text_file(const std::string& filename) {
	std::ifstream file_bin(filename + ".bin", std::ios::binary);
	std::ofstream file_txt(filename + ".txt"); 
	if (!file_bin || !file_txt) {
		std::cout << "Error: the file did not open!" << std::endl << std::endl;
	}
	else {
		file_txt << std::setw(30) << std::left << "Directory" 
			<< std::setw(30) << std::left << "File name" 
			<< std::setw(30) << std::left << "Filename extension"
			<< std::setw(30) << std::left << "Date and time of creation" 
			<< std::setw(30) << std::left << "Attribute"
			<< std::setw(30) << std::left << "Deletion flag" 
			<< std::setw(30) << std::left << "Number of allocated sectors" << std::endl;
		List_FileRecords records;
		records.Input(file_bin);
        // ЧТО ЗА ПЕРЕМЕННЫЕ? НИГДЕ НЕ ИСПОЛЬЗУЮТСЯ ---------- Исправлено
		for (const auto& elem : records.Output_map_FileRecords()) {
			file_txt << std::setw(30) << std::left << elem.second.Output_directory() 
				<< std::setw(30) << std::left << elem.second.Output_name()
				<< std::setw(30) << std::left << elem.second.Output_filename_extension() 
				<< std::setw(2) << std::right << std::setfill('0') << elem.second.Output_date()[0] << "."
				<< std::setw(2) << std::right << std::setfill('0') << elem.second.Output_date()[1] << "."
				<< std::setw(4) << std::left << std::setfill(' ') << elem.second.Output_date()[2] << " "
				<< std::setw(2) << std::right << std::setfill('0') << elem.second.Output_time()[0] << ":"
				<< std::setw(2) << std::right << std::setfill('0') << elem.second.Output_time()[1] << std::setw(14) << std::setfill(' ') << ""
				<< std::setw(30) << std::left << elem.second.Output_attribute() 
				<< std::setw(30) << std::left << elem.second.Output_deletion_flag() 
				<< std::setw(30) << std::left << elem.second.Output_number_of_sectors() << std::endl;
		}
	}
	file_txt.close();
	file_bin.close();
	std::cout << std::endl;
}
