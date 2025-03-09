#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#include "../Engine/ConsoleDebug/ConsoleDebug.h"
#include "../Utils/json.h"
#include "../Engine/Material.h"
#include "../Parsers/ShaderParser.h"


using json = nlohmann::json;

class MaterialParser
{
private:
    static const char* m_DebugName;

public:
    static std::vector<std::shared_ptr<Material>> materials;
    static std::shared_ptr<ShaderParams> LoadShaderParams(const json& data);
    static std::shared_ptr<Material> ParseMaterial(const char* assetPath, Engine::GUID inGUID);
    static void SaveMaterial(const std::shared_ptr<Material>& material, const char* assetPath);
};
