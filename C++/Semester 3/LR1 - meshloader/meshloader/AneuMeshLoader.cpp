#include "AneuMeshLoader.h"
#include <fstream>
#include "Exceptions.h"

void AneuMeshLoader::loadMesh(const std::string& str) {
	std::ifstream file(str);

	if (!file) {
		throw FileIsNotFound(str);
	}

	int n, k, c;
	double c2;
	file >> n >> k;
	m_Node.reserve(n);
    // ТАК КАК РАЗМЕР ВЕКТОРА УЗЛОВ (И ЭЛЕМЕНТОВ ТОЖЕ) ИЗВЕСТЕН ЗАРАНЕЕ, ------------- Исправлено
    // ТО НАДО ПОЛЬЗОВАТЬСЯ ФУНКЦИЕЙ vector::reserve,
    // ТАК МЫ ИЗБЕЖИМ КОПИРОВАНИЯ ЭЛЕМЕНТОВ ВЕКТОРА ПРИ УВЕЛИЧЕНИИ
    // ЁМКОСТИ ВЕКТОРА, КОГДА НЕТ МЕСТА ДЛЯ НОВОГО ЭЛЕМЕНТА
    // http://www.cplusplus.com/reference/vector/vector/reserve/
	for (int i = 1; i <= n; i++) {
		Node a;
		a.ID_Node = i;
		for (int j = 1; j <= k; j++) {
			file >> c2;
			a.Coordin.at(j-1) = c2;
		}
		a.flag = true;
		m_Node.push_back(std::move(a));
	}

	file >> n >> k;
	m_FiniteElement.reserve(n);
	for (int i = 1; i <= n; i++) {
		FiniteElement a;
		a.ID_KE = i;
		file >> a.ID_Material;
		a.ID_Nodes.reserve(k);
		for (int j = 1; j <= k; j++) {
			file >> c;
			a.ID_Nodes.push_back(c);
		}
		m_FiniteElement.push_back(std::move(a));
	}

	file >> n >> k;
	m_BoundaryFiniteElement.reserve(n);
	for (int i = 1; i <= n; i++) {
		BoundaryFiniteElement a;
		a.ID_Element = i;
		file >> a.ID_Border;
		a.ID_Nodes.reserve(k);
		for (int j = 1; j <= k; j++) {
			file >> c;
			a.ID_Nodes.push_back(c);
		}
		m_BoundaryFiniteElement.push_back(std::move(a));
	}

	file.close();
}
