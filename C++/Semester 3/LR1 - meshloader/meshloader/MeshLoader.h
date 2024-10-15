#pragma once
#include "Data_types.h"

class MeshLoader {
protected:
	std::vector<Node> m_Node;
	std::vector<FiniteElement> m_FiniteElement;
	std::vector<BoundaryFiniteElement> m_BoundaryFiniteElement;

public:
	virtual void loadMesh(const std::string&)=0;
	virtual ~MeshLoader() = default;

	//методы, позволяющие получить STL-контейнеры узлов, конечных элементов и граничных элементов
	std::vector<Node>& vector_Node();
	std::vector<FiniteElement>& vector_FiniteElement();
	std::vector<BoundaryFiniteElement>& vector_BoundaryFiniteElement();

	//методы, позволяющие найти КЭ по ID трех и двух его вершинных узлов
	std::vector<FiniteElement> FiniteElementByThreeNodes(int, int, int);
	std::vector<FiniteElement> FiniteElementByTwoNodes(int id1, int id2);

	//методы, возвращающие контейнеры граничных узлов, КЭ и граничных КЭ по id границы
	std::set<Node> BoundaryNodes(int id);
	std::set<FiniteElement> ContainerKE_by_id_border(int id_border);
	std::vector<BoundaryFiniteElement> BoundaryKE(int id);

	//метод, создающий новые узлы
	void NewNodes();

	//Контейнер контейнеров "соседних" узлов	
	std::vector<std::set<Node>>* Container_of_containers_of_neighboring_nodes();

	//методы вывода
	void print_Node();
	void print_FiniteElement();
	void print_BoundaryFiniteElement();

	//операторы вывода
	friend std::ostream& operator << (std::ostream& out, const std::vector <Node>& elem);
	friend std::ostream& operator << (std::ostream& out, const std::vector <FiniteElement>& elem);
	friend std::ostream& operator << (std::ostream& out, const std::vector <BoundaryFiniteElement>& elem);	
	friend std::ostream& operator << (std::ostream& out, const std::vector <std::set<Node>>& elem);
};

