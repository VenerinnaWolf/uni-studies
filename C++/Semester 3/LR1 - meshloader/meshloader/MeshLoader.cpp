#include "MeshLoader.h"
#include <algorithm>
using namespace std;

std::ostream& operator << (std::ostream& out, const std::set<Node>& elem) {
	for_each(elem.begin(), elem.end(), [&](auto& i) {
		out << "   ID node: " << i.ID_Node << std::endl;
		out << "   Coordinates: ";
		for_each(i.Coordin.begin(), i.Coordin.end(), [&](auto& j) {
			out << j << " ";
			});
		out << std::endl << "   Flag: " << i.flag << std::endl << std::endl;
		});
	return out;
}

std::ostream& operator << (std::ostream& out, const std::vector<Node>& elem) {
	for_each(elem.begin(), elem.end(), [&](auto& i) {
		out << "   ID node: " << i.ID_Node << std::endl;
		out << "   Coordinates: ";
		for_each(i.Coordin.begin(), i.Coordin.end(), [&](auto& j) {
			out << j << " ";
			});
		out << std::endl << "   Flag: " << i.flag << std::endl << std::endl;
		});
	return out;
}

std::ostream& operator << (std::ostream& out, const std::set <FiniteElement>& elem) {
	for_each(elem.begin(), elem.end(), [&](auto& i) {
		out << "   ID_KE: " << i.ID_KE << std::endl;
		out << "   ID_Material: " << i.ID_Material << std::endl;
		out << "   ID_Nodes: ";
		for_each(i.ID_Nodes.begin(), i.ID_Nodes.end(), [&](auto& j) {
			out << j << " ";
			});
		out << std::endl << std::endl;
		});
	return out;
}
std::ostream& operator << (std::ostream& out, const std::vector <FiniteElement>& elem) {
	for_each(elem.begin(), elem.end(), [&](auto& i) {
		out << "   ID_KE: " << i.ID_KE << std::endl;
		out << "   ID_Material: " << i.ID_Material << std::endl;
		out << "   ID_Nodes: ";
		for_each(i.ID_Nodes.begin(), i.ID_Nodes.end(), [&](auto& j) {
			out << j << " ";
			});
		out << std::endl << std::endl;
		});
	return out;
}

std::ostream& operator << (std::ostream& out, const std::vector <BoundaryFiniteElement>& elem) {
	for_each(elem.begin(), elem.end(), [&](auto& i) {
		out << "   ID_Element: " << i.ID_Element << std::endl;
		out << "   ID_Border: " << i.ID_Border << std::endl;
		out << "   ID_Nodes: ";
		for_each(i.ID_Nodes.begin(), i.ID_Nodes.end(), [&](auto& j) {
			out << j << " ";
			});
		out << std::endl << std::endl;
		});
	return out;
}

std::ostream& operator << (std::ostream& out, const std::vector<std::set<Node>>& elem) {
	int n = 1;
	for_each(elem.begin(), elem.end(), [&](auto& i) {
		out << "Container_" << n << endl;
		out << i;
		++n;
		});
	return out;
}

std::vector<Node>& MeshLoader::vector_Node() {
	return m_Node;
}

std::vector<FiniteElement>& MeshLoader::vector_FiniteElement() {
	return m_FiniteElement;
}

std::vector<BoundaryFiniteElement>& MeshLoader::vector_BoundaryFiniteElement() {
	return m_BoundaryFiniteElement;
}

std::vector<FiniteElement> MeshLoader::FiniteElementByThreeNodes(int id1, int id2, int id3) {
	std::vector<FiniteElement> result;
	auto a = m_FiniteElement.begin();

	while (a != m_FiniteElement.end()) {
		a = find_if(a, m_FiniteElement.end(), [id1, id2, id3](FiniteElement s) {
			return (find(s.ID_Nodes.begin(), s.ID_Nodes.end(), id1) != s.ID_Nodes.end() &&
				find(s.ID_Nodes.begin(), s.ID_Nodes.end(), id2) != s.ID_Nodes.end() &&
				find(s.ID_Nodes.begin(), s.ID_Nodes.end(), id3) != s.ID_Nodes.end());
			});
		if (a != m_FiniteElement.end()) {
			result.push_back(*a);
			a++;
		}
	}
    // ÍÅ ÍÀÄÎ ÓÊÀÇÀÒÅËÜ ÂÎÇÂĞÀÙÀÒÜ, ÊÒÎ ÏÀÌßÒÜ ÓÄÀËßÒÜ ÁÓÄÅÒ? ------------- Èñïğàâëåíî
    // ÂÎÒ Â ÔÓÍÊÖÈÈ main İÒÎÒ ÓÊÀÇÀÒÅËÜ ÍÅ ÓÄÀËßÅÒÑß - ÓÒÅ×ÊÀ ÏÀÌßÒÈ
	return result;
}

std::vector<FiniteElement> MeshLoader::FiniteElementByTwoNodes(int id1, int id2) {
	std::vector<FiniteElement> result;
	auto a = m_FiniteElement.begin();

	while (a != m_FiniteElement.end()) {
		a = find_if(a, m_FiniteElement.end(), [id1, id2](FiniteElement& elem) {
			return (find(elem.ID_Nodes.begin(), elem.ID_Nodes.end(), id1) != elem.ID_Nodes.end() &&
				find(elem.ID_Nodes.begin(), elem.ID_Nodes.end(), id2) != elem.ID_Nodes.end());
			});
		if (a != m_FiniteElement.end()) {
			result.push_back(*a);
			a++;
		}
	}
    // ÒÎÆÅ ÓÊÀÇÀÒÅËÜ ÂÎÇÂĞÀÙÀÅÒÑß ------------- Èñïğàâëåíî
	return result;

}

std::set<Node> MeshLoader::BoundaryNodes(int id) {
	std::set<Node> result;
	
	for_each(m_BoundaryFiniteElement.begin(), m_BoundaryFiniteElement.end(), [&](auto& elem1) {
		if (elem1.ID_Border == id) {
			for_each(elem1.ID_Nodes.begin(), elem1.ID_Nodes.end(), [&](auto& elem2) {
				result.insert(m_Node.at(elem2 - 1));
				});
		}
		});

    // ÇÄÅÑÜ ÏÎ×ÅÌÓ ÓÊÀÇÀÒÅËÜ ÎÑÒÀËÑß? ------------- Èñïğàâëåíî
	return result;
}

std::set<FiniteElement> MeshLoader::ContainerKE_by_id_border(int id_border) {
	std::set<FiniteElement> result;

	for_each(m_BoundaryFiniteElement.begin(), m_BoundaryFiniteElement.end(), [&](auto& elem1) {
		if (elem1.ID_Border == id_border) {
			for_each(m_FiniteElement.begin(), m_FiniteElement.end(), [&](auto& elem2) {
				if (find_if(elem1.ID_Nodes.begin(), elem1.ID_Nodes.end(), [&](auto& s) {
					return (find(elem2.ID_Nodes.begin(), elem2.ID_Nodes.end(), s) == elem2.ID_Nodes.end());
					}) == elem1.ID_Nodes.end()) {
					result.insert(elem2);
				}
				});
		}
		});
    // ÇÄÅÑÜ ÏÎ×ÅÌÓ ÓÊÀÇÀÒÅËÜ ÎÑÒÀËÑß? ------------- Èñïğàâëåíî
    return result;
}


std::vector<BoundaryFiniteElement> MeshLoader::BoundaryKE(int id) {
	std::vector<BoundaryFiniteElement> result;

	for_each(m_BoundaryFiniteElement.begin(), m_BoundaryFiniteElement.end(), [id, &result](auto elem) {
		if (elem.ID_Border == id) {
			result.push_back(elem);
		}
		});

    // ÇÄÅÑÜ ÏÎ×ÅÌÓ ÓÊÀÇÀÒÅËÜ ÎÑÒÀËÑß? ------------- Èñïğàâëåíî
    return result;
}

void MeshLoader::NewNodes() {
	unordered_set<Edge, EdgeHash> List_edge;
	for (auto& i : m_FiniteElement) {
		vector<int> a = i.ID_Nodes;
		for (auto elem1 = a.begin(); elem1 < a.end(); elem1++) {
			for (auto elem2 = elem1 + 1; elem2 < a.end(); elem2++) {
				Edge ed(*elem1, *elem2);
				if (List_edge.find(ed) == List_edge.end()) {
					Node el;
					el.ID_Node = m_Node.size() + 1;
					el.flag = false;
					for (int j = 0; j < m_Node.begin()->Coordin.size(); j++) {
						el.Coordin.at(j) = (m_Node.at(*elem1 - 1).Coordin.at(j) + m_Node.at(*elem2 - 1).Coordin.at(j)) / 2;
					}
					m_Node.push_back(el);
					i.ID_Nodes.push_back(el.ID_Node);
					ed.middle_id = el.ID_Node;
					List_edge.insert(ed);
				}
				else {
					auto el = List_edge.find(ed);
					i.ID_Nodes.push_back(el->middle_id);
				}
			}
		}
	}
	for (auto& i : m_BoundaryFiniteElement) {
		vector<int> a = i.ID_Nodes;
		for (auto elem1 = a.begin(); elem1 < a.end(); elem1++) {
			for (auto elem2 = elem1 + 1; elem2 < a.end(); elem2++) {
				Edge ed(*elem1, *elem2);
				if (List_edge.find(ed) != List_edge.end()) {
					auto el = List_edge.find(ed);
					i.ID_Nodes.push_back(el->middle_id);
				}
			}
		}
	}

}

std::vector<std::set<Node>>* MeshLoader::Container_of_containers_of_neighboring_nodes() {
	std::vector<std::set<Node>>* result = new std::vector<std::set<Node>>; 
	for_each(m_Node.begin(), m_Node.end(), [&](auto& elem1) {
		std::set<Node> NeighboringNodesOfNode_a;
		for_each(m_FiniteElement.begin(), m_FiniteElement.end(), [&](auto& elem2) {
			if (find(elem2.ID_Nodes.begin(), elem2.ID_Nodes.end(), elem1.ID_Node) != elem2.ID_Nodes.end()) {
				for_each(elem2.ID_Nodes.begin(), elem2.ID_Nodes.end(), [&](auto& elem3) {

					if (elem3 != elem1.ID_Node) NeighboringNodesOfNode_a.insert(m_Node.at(elem3 - 1));
					});
			}
			});
		result->push_back(NeighboringNodesOfNode_a);
		});
	return result;
}

void MeshLoader::print_Node() {
	cout << m_Node;
}

void MeshLoader::print_FiniteElement() {
	cout << m_FiniteElement;
}

void MeshLoader::print_BoundaryFiniteElement() {
	cout << m_BoundaryFiniteElement;
}
