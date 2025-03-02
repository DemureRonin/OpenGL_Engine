#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#include "../Utils/json.h"
#include "../Engine/Material.h"
#include "../Engine/LitShader.h"
#include "../Engine/Managers/TextureManager.h"
using json = nlohmann::json;
class MaterialParser
{
private:
    static unsigned int m_IDCount;

public:
    static std::shared_ptr<Material> ParseMaterial(const char* filePath, LitShader& shader);
};


