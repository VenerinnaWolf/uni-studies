#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <unordered_set>


// узел
struct Node {    
	// ID узла
	int ID_Node = 1;
    // КООРДИНАТ ВСЕГДА ТРИ, ЛУЧШЕ ИСПОЛЬЗОВАТЬ std::array ------------- Исправлено
	// координаты
	std::array<double, 3> Coordin;
	// флаг, определяющий, является ли данный узел вершиной КЭ
	bool flag = true;
	bool operator < (const Node& elem) const {
		return (ID_Node < elem.ID_Node);
	}
};

// конечный элемент
struct FiniteElement {  
	// ID KЭ
	int ID_KE = 1;
	// ID материала
	int ID_Material = 1;
	// вектор ID узлов КЭ
	std::vector<int> ID_Nodes;
	bool operator < (const FiniteElement& elem) const {
		return (ID_KE < elem.ID_KE);
	}
};

// граничный конечный элемент
struct BoundaryFiniteElement {  
	// ID элемента
	int ID_Element = 1;
	// ID поверхности
	int ID_Border = 1;
	// вектор ID узлов
	std::vector<int> ID_Nodes;
};

struct Edge
{
	int first_id;
	int last_id;
	int middle_id = 0;
	Edge() = default;
	Edge(int id1, int id2) : first_id(id1), last_id(id2) {}

	bool operator == (const Edge& elem) const {
        // ОПЕРАТОР == УЖЕ ВОЗВРАЩАЕТ ТИП bool, ПОЭТОМУ НАДО СОКРАЩАТЬ ЗАПИСЬ: ------------- Исправлено
        // return (first_id == elem.first_id && last_id == elem.last_id) ||
        //        (first_id == elem.last_id && last_id == elem.first_id);
		return (first_id == elem.first_id && last_id == elem.last_id) ||
			   (first_id == elem.last_id && last_id == elem.first_id);
	}
};


class EdgeHash
{
public:
	std::size_t operator() (const Edge& _p) const
	{
		std::size_t o_seed = 0;
		if (_p.first_id > _p.last_id) {
			o_seed ^= std::hash<int>() (_p.first_id) + 0x9e3779b9 + (o_seed << 6) + (o_seed >> 2);
			o_seed ^= std::hash<int>() (_p.last_id) + 0x9e3779b9 + (o_seed << 6) + (o_seed >> 2);
		}
		else {
			o_seed ^= std::hash<int>() (_p.last_id) + 0x9e3779b9 + (o_seed << 6) + (o_seed >> 2);
			o_seed ^= std::hash<int>() (_p.first_id) + 0x9e3779b9 + (o_seed << 6) + (o_seed >> 2);
		}

		return o_seed;
	};
};

std::ostream& operator << (std::ostream& out, const std::vector <Node>& elem);
std::ostream& operator << (std::ostream& out, const std::vector <FiniteElement>& elem);
std::ostream& operator << (std::ostream& out, const std::set <FiniteElement>& elem);
std::ostream& operator << (std::ostream& out, const std::vector <BoundaryFiniteElement>& elem);
std::ostream& operator << (std::ostream& out, const std::vector<std::set<Node>>& elem);
std::ostream& operator << (std::ostream& out, const std::set <Node>& elem);
