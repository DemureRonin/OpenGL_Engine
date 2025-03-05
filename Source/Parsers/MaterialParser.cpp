#include "MaterialParser.h"

unsigned int MaterialParser::m_IDCount = 0;
std::vector<std::shared_ptr<Material>> MaterialParser::materials{};
const char* MaterialParser::m_DebugName = "MATERIAL_PARSER";

std::shared_ptr<Material> MaterialParser::LoadMaterial(const char* filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open material file: " << filePath << std::endl;
        return nullptr;
    }

    json data;
    try
    {
        file >> data;
    }
    catch (const json::exception& e)
    {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return nullptr;
    }
    ShaderParams params;
    // Parse shader file
    params.shaderFile = data.value("shaderFile", "");

    // Parse float parameters
    if (data.contains("floatParams") && data["floatParams"].is_array())
    {
        for (const auto& param : data["floatParams"])
        {
            if (param.contains("name") && param.contains("value"))
            {
                params.floatParameters[param["name"].get<std::string>()] = param["value"].get<float>();
            }
        }
    }

    // Parse int parameters
    if (data.contains("intParams") && data["intParams"].is_array())
    {
        for (const auto& param : data["intParams"])
        {
            if (param.contains("name") && param.contains("value"))
            {
                params.intParameters[param["name"].get<std::string>()] = param["value"].get<int>();
            }
        }
    }

    // Parse vec2 parameters
    if (data.contains("vec2Params") && data["vec2Params"].is_array())
    {
        for (const auto& param : data["vec2Params"])
        {
            if (param.contains("name") && param.contains("value") && param["value"].is_array() && param["value"].size()
                == 2)
            {
                params.vec2Parameters[param["name"].get<std::string>()] = glm::vec2(
                    param["value"][0].get<float>(),
                    param["value"][1].get<float>()
                );
            }
        }
    }

    // Parse vec3 parameters
    if (data.contains("vec3Params") && data["vec3Params"].is_array())
    {
        for (const auto& param : data["vec3Params"])
        {
            if (param.contains("name") && param.contains("value") && param["value"].is_array() && param["value"].size()
                == 3)
            {
                params.vec3Parameters[param["name"].get<std::string>()] = glm::vec3(
                    param["value"][0].get<float>(),
                    param["value"][1].get<float>(),
                    param["value"][2].get<float>()
                );
            }
        }
    }

    // Parse vec4 parameters
    if (data.contains("vec4Params") && data["vec4Params"].is_array())
    {
        for (const auto& param : data["vec4Params"])
        {
            if (param.contains("name") && param.contains("value") && param["value"].is_array() && param["value"].size()
                == 4)
            {
                params.vec4Parameters[param["name"].get<std::string>()] = glm::vec4(
                    param["value"][0].get<float>(),
                    param["value"][1].get<float>(),
                    param["value"][2].get<float>(),
                    param["value"][3].get<float>()
                );
            }
        }
    }

    // Parse texture parameters
    if (data.contains("textureParams") && data["textureParams"].is_array())
    {
        if (data["textureParams"].empty())
        {
            params.textureParameters[0] = TextureManager::LoadTexture(WHITE_TEXTURE);
            std::cout << "No textures found in the material file." << std::endl;
        }
        else
        {
            for (const auto& param : data["textureParams"])
            {
                if (param.contains("name") && param.contains("filePath"))
                {
                    std::string name = param["name"].get<std::string>();
                    std::string texturePath = param["filePath"].get<std::string>();

                    // Load texture and store as shared_ptr
                    params.textureParameters[name] = TextureManager::LoadTexture(texturePath);
                }
            }
        }
    }
    auto shader = std::make_shared<Shader>(params.shaderFile.c_str());
    auto mat = std::make_shared<Material>(m_IDCount++, shader, params);

    return mat;
}
