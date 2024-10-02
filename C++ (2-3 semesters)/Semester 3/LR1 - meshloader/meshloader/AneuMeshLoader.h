#pragma once
#include "MeshLoader.h"

class AneuMeshLoader :public MeshLoader {
public:
	void loadMesh(const std::string&) override;
};