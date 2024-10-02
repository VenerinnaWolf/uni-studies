#pragma once
// ЭТОТ МАКРОС СОСТОИТ ИЗ ДВУХ ЧАСТЕЙ: НАЗВАНИЕ БИБЛИОТЕКИ И СУФФИКСА _EXPORTS
// НАЗВАНИЕ БИБЛИОТЕКИ - ЭТО ИМЯ ПРОЕКТА, В ТВОЁМ СЛУЧАЕ DLL1
#ifdef DLL1_EXPORTS
	#define DLL1_API __declspec(dllexport)
#else
	#define DLL1_API __declspec(dllimport)
#endif
extern "C" DLL1_API void sort(int* array, size_t size);
