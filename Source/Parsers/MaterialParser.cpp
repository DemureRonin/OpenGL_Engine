#include "MaterialParser.h"

#include "../Engine/Managers/AssetLoader.h"


std::vector<std::shared_ptr<Material>> MaterialParser::materials{};
const char* MaterialParser::m_DebugName = "MATERIAL_PARSER";
std::shared_ptr<Material> MaterialParser::ParseMaterial(const char* assetPath, Engine::GUID inGUID)
{
    std::ifstream file(assetPath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open material file: " << assetPath << '\n';
        return std::static_pointer_cast<Material>(AssetLoader::GetAsset(Engine::GUID::FromString(MATERIAL_ERROR)));
    }

    json data;
    try
    {
        file >> data;
    }
    catch (const json::exception& e)
    {
        std::cerr << "JSON parse error: " << e.what() << '\n';
        return std::static_pointer_cast<Material>(AssetLoader::GetAsset(Engine::GUID::FromString(MATERIAL_ERROR)));
    }

    auto params = LoadShaderParams(data);
    auto shader = std::static_pointer_cast<Shader>(
        AssetLoader::GetAsset(Engine::GUID::FromString(params->shaderIDString)));

    if (!shader || !shader->CompiledSuccessfully())
    {
        return std::static_pointer_cast<Material>(AssetLoader::GetAsset(Engine::GUID::FromString(MATERIAL_ERROR)));
    }

    return std::make_shared<Material>(assetPath, inGUID, shader, params);
}

std::shared_ptr<ShaderParams> MaterialParser::LoadShaderParams(const json& data)
{
    auto params = std::make_shared<ShaderParams>();
    params->shaderIDString = data.value("shaderGUID", "");


    if (data.contains("floatParams") && data["floatParams"].is_array())
    {
        for (const auto& param : data["floatParams"])
        {
            if (param.contains("name") && param.contains("value"))
            {
                params->floatParameters[param["name"].get<std::string>()] = param["value"].get<float>();
            }
        }
    }


    if (data.contains("intParams") && data["intParams"].is_array())
    {
        for (const auto& param : data["intParams"])
        {
            if (param.contains("name") && param.contains("value"))
            {
                params->intParameters[param["name"].get<std::string>()] = param["value"].get<int>();
            }
        }
    }


    if (data.contains("vec2Params") && data["vec2Params"].is_array())
    {
        for (const auto& param : data["vec2Params"])
        {
            if (param.contains("name") && param["value"].is_array() && param["value"].size() == 2)
            {
                params->vec2Parameters[param["name"].get<std::string>()] = glm::vec2(
                    param["value"][0].get<float>(), param["value"][1].get<float>());
            }
        }
    }


    if (data.contains("vec3Params") && data["vec3Params"].is_array())
    {
        for (const auto& param : data["vec3Params"])
        {
            if (param.contains("name") && param["value"].is_array() && param["value"].size() == 3)
            {
                params->vec3Parameters[param["name"].get<std::string>()] = glm::vec3(
                    param["value"][0].get<float>(), param["value"][1].get<float>(), param["value"][2].get<float>());
            }
        }
    }


    if (data.contains("vec4Params") && data["vec4Params"].is_array())
    {
        for (const auto& param : data["vec4Params"])
        {
            if (param.contains("name") && param["value"].is_array() && param["value"].size() == 4)
            {
                params->vec4Parameters[param["name"].get<std::string>()] = glm::vec4(
                    param["value"][0].get<float>(), param["value"][1].get<float>(),
                    param["value"][2].get<float>(), param["value"][3].get<float>());
            }
        }
    }


    if (data.contains("textureParams") && data["textureParams"].is_array())
    {
        for (const auto& textureEntry : data["textureParams"])
        {
            if (textureEntry.is_object())
            {
                for (auto it = textureEntry.begin(); it != textureEntry.end(); ++it)
                {
                    std::string type = it.key();
                    Engine::GUID textureID = Engine::GUID::FromString(it.value().get<std::string>());
                    params->textureParameters[type] = std::static_pointer_cast<Texture>(
                        AssetLoader::GetAsset(textureID));
                }
            }
        }
    }

    return params;
}



void MaterialParser::SaveMaterial(const std::shared_ptr<Material>& material, const char* assetPath)
{
    if (!material)
    {
        std::cerr << "Error: Attempted to save a null material." << '\n';
        return;
    }

    json data;


    if (material->shaderParams->shaderIDString.empty())
    {
        std::cerr << "Warning: Material has no shader assigned." << '\n';
    }
    data["GUID"] = material->GetGUID().ToString();
    data["shaderGUID"] = material->shaderParams->shaderIDString;


    for (const auto& [name, value] : material->shaderParams->floatParameters)
    {
        data["floatParams"].push_back({{"name", name}, {"value", value}});
    }


    for (const auto& [name, value] : material->shaderParams->intParameters)
    {
        data["intParams"].push_back({{"name", name}, {"value", value}});
    }


    for (const auto& [name, value] : material->shaderParams->vec2Parameters)
    {
        data["vec2Params"].push_back({{"name", name}, {"value", {value.x, value.y}}});
    }


    for (const auto& [name, value] : material->shaderParams->vec3Parameters)
    {
        data["vec3Params"].push_back({{"name", name}, {"value", {value.x, value.y, value.z}}});
    }


    for (const auto& [name, value] : material->shaderParams->vec4Parameters)
    {
        data["vec4Params"].push_back({{"name", name}, {"value", {value.x, value.y, value.z, value.w}}});
    }


    for (const auto& [type, texture] : material->shaderParams->textureParameters)
    {
        if (texture)
        {
            data["textureParams"].push_back({{type, texture->GetGUID().ToString()}});
        }
    }


    std::ofstream file(assetPath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open material file for writing: " << assetPath << '\n';
        return;
    }

    file << data.dump(4);
    file.close();
}
