#pragma once
#include "../Engine/Mesh.h"
#include "../Engine/Model.h"

class MeshParser
{
private:
    static const char* m_DebugName;
public:
    static std::shared_ptr<Mesh> ParseMesh(const char* filePath);
};
