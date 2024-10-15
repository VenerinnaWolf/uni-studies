#pragma once
#include <iostream>
#include <algorithm>
#include <map>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <string>

struct Date {
	int day;
	int month;
	int year;
};

struct Time {
	int hour;
	int minute;
};

class FileRecord {
private:
	char directory[30];
	char name[30];
	char filename_extension[30];
	char date_day[10];
	char date_month[10];
	char date_year[10];
	char time_hour[10];
	char time_minute[10];
	char attribute[30]; // Read-only, Hidden, System
	char deletion_flag[30];
	char number_of_sectors[30];
public:
	FileRecord() = default;
	FileRecord(const FileRecord& elem);
	FileRecord& operator =(const FileRecord& elem);

	void NewFileRecord();

	std::string Output_directory() const;
	std::string Output_name() const;
	std::string Output_filename_extension() const;
	std::vector<int> Output_date() const;
	std::vector<int> Output_time() const;
	std::string Output_attribute() const;
	std::string Output_deletion_flag() const;
	int Output_number_of_sectors() const;
};

class List_FileRecords {
private:
	std::map<size_t, FileRecord> map_FileRecords;
	size_t size = 0;
public:
	List_FileRecords() = default;
	FileRecord& operator[](size_t num);

	std::map<size_t, FileRecord>& Output_map_FileRecords();

	void erase_record(int);
	void replace_record(int, FileRecord);

	void Input(std::ifstream& file);
	void Output(std::ofstream& file);

	List_FileRecords Search_by_directory();
	List_FileRecords Search_by_date();
	List_FileRecords Search_by_deletion_flag();
};
