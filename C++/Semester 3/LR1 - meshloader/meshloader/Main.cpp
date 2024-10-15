#include <iostream>
#include <memory>
#include "AneuMeshLoader.h"
using namespace std;

int main() {
    // ИСПОЛЬЗУЙ УМНЫЙ УКАЗАТЕЛЬ НА БАЗОВЫЙ КЛАСС, ------------- Исправлено
    // ЧТОБЫ РАБОТАЛ МЕХАНИЗМ ВИРТУАЛЬНЫХ ФУНКЦИЙ
    // ГДЕ УМНЫЙ УКАЗАТЕЛЬ? ------------- Исправлено
	shared_ptr<MeshLoader> MyKE = make_shared<AneuMeshLoader>();
	std::string str;
	cout << "Enter the file name:";
	cin >> str;
	MyKE->loadMesh(str);

	cout << "---------------STL-container nodes---------------"<<endl;
	cout << MyKE->vector_Node() <<endl;

	cout << "---------------STL-container finite elements---------------"<<endl;
	cout << MyKE->vector_FiniteElement()<<endl;

	cout << "---------------STL-container boundary finite elements---------------"<<endl;
	cout << MyKE->vector_BoundaryFiniteElement() <<endl;

	cout << "---------------Finite element by three nodes---------------" << endl;
	cout << "Enter three nodes:";
	int id1, id2, id3;
	cin >> id1 >> id2 >> id3;
	cout << MyKE->FiniteElementByThreeNodes(id1,id2,id3) << endl;

	cout << "---------------Finite element by two nodes---------------" << endl;
	cout << "Enter two nodes:";
	cin >> id1 >> id2;
	cout << MyKE->FiniteElementByTwoNodes(id1, id2) << endl;

	cout << "---------------Container of boundary nodes by border ID---------------" << endl;
	cout << "Enter border ID:";
	cin >> id1;
	cout << MyKE->BoundaryNodes(id1) << endl;

	cout << "---------------Container KE by border ID---------------" << endl;
	cout << "Enter border ID:";
	cin >> id1;
	cout << MyKE->ContainerKE_by_id_border(id1) << endl;

	cout << "---------------Container boundary KE by border ID---------------" << endl;
	cout << "Enter border ID:";
	cin >> id1;
	cout << MyKE->BoundaryKE(id1) << endl;

	cout << "---------------Container with containers of \"neighboring\" nodes---------------" << endl;	
	cout << *MyKE->Container_of_containers_of_neighboring_nodes() << endl;

	
	cout << "---------------Print Node---------------" << endl;
	MyKE->print_Node();

	cout << "---------------Print FiniteElement---------------" << endl;
	MyKE->print_FiniteElement();

	cout << "---------------Print BoundaryFiniteElement---------------" << endl;
	MyKE->print_BoundaryFiniteElement();

	cout << "---------------Inserting new nodes in the middle of the edges of the KE---------------" << endl;
	MyKE->NewNodes();
	cout << "STL-container nodes:" << endl;
	cout << MyKE->vector_Node() << endl;
	cout << "STL-container finite elements:" << endl;
	cout << MyKE->vector_FiniteElement() << endl;
	cout << "STL-container boundary finite elements:" << endl;
	cout << MyKE->vector_BoundaryFiniteElement() << endl;

	return 0;
}
