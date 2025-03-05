#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#include "../Engine/ConsoleDebug/ConsoleDebug.h"
#include "../Utils/json.h"
#include "../Engine/Material.h"

#include "../Engine/Managers/TextureManager.h"
using json = nlohmann::json;
class MaterialParser
{
private:
    static unsigned int m_IDCount;
    static const char* m_DebugName;

public:
    static std::vector<std::shared_ptr<Material>> materials;
    static std::shared_ptr<Material> LoadMaterial(const char* filePath);
};


