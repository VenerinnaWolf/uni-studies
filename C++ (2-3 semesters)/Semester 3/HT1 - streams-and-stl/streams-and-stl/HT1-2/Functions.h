#pragma once
// ЗАЧЕМ ЗДЕСЬ ЭТО ВКЛЮЧЕНИЕ? --- Я ведь использую в функциях класс FileRecord. Или его переместить в .cpp файл?
#include <iostream>
#include <string>

void Primary_input(const std::string& filename);
void Add_to_file(const std::string& filename);
void Delete_a_record(const std::string& filename);
void Replace_record(const std::string& filename);
void Search_for_records(const std::string& filename);
void Convert_to_a_text_file(const std::string& filename);
