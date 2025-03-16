#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#include "../Engine/ConsoleDebug/ConsoleDebug.h"
#include "../Utils/json.h"

#include "../Parsers/ShaderParser.h"


class Material;
class Shader;
using json = nlohmann::json;

class MaterialParser
{
private:
    static const char* m_DebugName;

public:
    static std::shared_ptr<ShaderParams> LoadShaderParams(const json& data);
    static void Fallback(const char* assetPath, std::shared_ptr<Shader>& shader, std::shared_ptr<ShaderParams>& params);
    static bool ParseMaterial(const char* assetPath, std::shared_ptr<Shader>& shader,
                              std::shared_ptr<ShaderParams>& params);
    static void SaveMaterial(const std::shared_ptr<Material>& material, const char* assetPath);
};
