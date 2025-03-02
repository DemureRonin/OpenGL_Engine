#pragma once
#include "../Engine/Mesh.h"
#include "../Engine/Model.h"

class MeshParser
{
public:
    static std::shared_ptr<Mesh> ParseMesh(const char* filePath);
};
