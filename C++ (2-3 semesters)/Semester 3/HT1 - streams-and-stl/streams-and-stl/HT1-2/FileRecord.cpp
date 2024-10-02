#include "FileRecord.h"

// FileRecord

FileRecord::FileRecord(const FileRecord& elem) {
	strcpy_s(directory, elem.directory);
	strcpy_s(name, elem.name);
	strcpy_s(filename_extension, elem.filename_extension);
	strcpy_s(date_day, elem.date_day);
	strcpy_s(date_month, elem.date_month);
	strcpy_s(date_year, elem.date_year);
	strcpy_s(time_hour, elem.time_hour);
	strcpy_s(time_minute, elem.time_minute);
	strcpy_s(attribute, elem.attribute);
	strcpy_s(deletion_flag, elem.deletion_flag);
	strcpy_s(number_of_sectors, elem.number_of_sectors);
}

FileRecord& FileRecord::operator =(const FileRecord& elem) {
    // ГДЕ ПРОВЕРКА НА САМОПРИСВАИВАНИЕ ---------- Исправлено
	if (this == &elem)
		return *this;

	strcpy_s(directory, elem.directory);
	strcpy_s(name, elem.name);
	strcpy_s(filename_extension, elem.filename_extension);
	strcpy_s(date_day, elem.date_day);
	strcpy_s(date_month, elem.date_month);
	strcpy_s(date_year, elem.date_year);
	strcpy_s(time_hour, elem.time_hour);
	strcpy_s(time_minute, elem.time_minute);
	strcpy_s(attribute, elem.attribute);
	strcpy_s(deletion_flag, elem.deletion_flag);
	strcpy_s(number_of_sectors, elem.number_of_sectors);
	return *this;
}

void FileRecord::NewFileRecord() {
	std::cout << "\tEnter the directory, where file is located: ";
	std::cin >> directory;
	std::cout << "\tEnter the name of file: ";
	std::cin >> name;
	std::cout << "\tEnter the filename extension: ";
	std::cin >> filename_extension;
	std::cout << "\tEnter the date of creation:" << std::endl 
			  << "\t\tday: ";
	std::cin >> date_day;
	std::cout << "\t\tmonth: ";
	std::cin >> date_month;
	std::cout << "\t\tyear: ";
	std::cin >> date_year;
	std::cout << "\tEnter the time of creation:" << std::endl 
			  << "\t\thours: ";
	std::cin >> time_hour;
	std::cout << "\t\tminutes: ";
	std::cin >> time_minute;
	std::cout << "\tSelect the attribute:" << std::endl
		<< "\t\t1 - Read-only" << std::endl
		<< "\t\t2 - Hidden" << std::endl
		<< "\t\t3 - System" << std::endl << "\t>> ";
	int a;
	std::cin >> a;
	switch (a) {
	case 1:
		strcpy_s(attribute, "Read-only");
		break;
	case 2:
		strcpy_s(attribute, "Hidden");
		break;
	case 3:
		strcpy_s(attribute, "System");
		break;
	default:
		std::cout << "Wrong input. Selected attribute - Read-only" << std::endl;
		strcpy_s(attribute, "Read-only");
		break;
	}
	std::cout << "\tEnter the deletion flag (true or false): ";
	std::cin >> deletion_flag;
	std::cout << "\tEnter the the number of allocated sectors: ";
	std::cin >> number_of_sectors;
}

std::string FileRecord::Output_directory() const { return directory; }

std::string FileRecord::Output_name() const { return name; }

std::string FileRecord::Output_filename_extension() const {	return filename_extension; }

std::vector<int> FileRecord::Output_date() const {
	std::vector<int> date_v;
	date_v.push_back(atoi(date_day));
	date_v.push_back(atoi(date_month));
	date_v.push_back(atoi(date_year));
	return date_v;
}

std::vector<int> FileRecord::Output_time() const {
	std::vector<int> time_v;
	time_v.push_back(atoi(time_hour));
	time_v.push_back(atoi(time_minute));
	return time_v;
}

std::string FileRecord::Output_attribute() const { return attribute; }

std::string FileRecord::Output_deletion_flag() const { return deletion_flag; }

int FileRecord::Output_number_of_sectors() const { return atoi(number_of_sectors); }


//List_FileRecords

FileRecord& List_FileRecords::operator[](size_t num) {
	return map_FileRecords[num];
}

void List_FileRecords::erase_record(int num) {
	map_FileRecords.erase(num);
}

void List_FileRecords::replace_record(int num, FileRecord record) {
	map_FileRecords[num] = record;
}

void List_FileRecords::Input(std::ifstream& file) {
	FileRecord elem;

	while (file.read(reinterpret_cast<char*>(&elem), sizeof(FileRecord))) {
		map_FileRecords[++size] = elem;
	}
}

void List_FileRecords::Output(std::ofstream& file) {
	for_each(map_FileRecords.begin(), map_FileRecords.end(), [&](auto& elem) {
		file.write(reinterpret_cast<char*>(&(elem.second)), sizeof(FileRecord)); 
		});
}

std::map<size_t, FileRecord>& List_FileRecords::Output_map_FileRecords() {
	return map_FileRecords;
}

List_FileRecords List_FileRecords::Search_by_directory() {
	std::string str;
	std::cout << "Enter the directory:";
	std::cin >> str;
	List_FileRecords result;
	for (auto& elem : map_FileRecords) {
		if (elem.second.Output_directory() == str) {
			result[++(result.size)] = elem.second;
		}
	}
	return result;
}

List_FileRecords List_FileRecords::Search_by_date() {
	std::vector<int> date_v;
	int n;
	std::cout << "Enter the date:" << std::endl
		<< "\t\tday:";
	std::cin >> n;
	date_v.push_back(n);
	std::cout << "\t\tmonth:";
	std::cin >> n;
	date_v.push_back(n);
	std::cout << "\t\tyear:";
	std::cin >> n;
	date_v.push_back(n);
	List_FileRecords result;
	for (auto& elem : map_FileRecords) {
		if (elem.second.Output_date() == date_v) {
			result[++(result.size)] = elem.second;
		}
	}
	return result;
}

List_FileRecords List_FileRecords::Search_by_deletion_flag() {
	std::string str;
	std::cout << "Enter the deletion flag:";
	std::cin >> str;
	List_FileRecords result;
	for (auto& elem : map_FileRecords) {
		if (elem.second.Output_deletion_flag() == str) {
			result[++(result.size)] = elem.second;
		}
	}
	return result;
}
