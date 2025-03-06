#include "MaterialManager.h"

#include "../../Parsers/MaterialParser.h"
std::unordered_map<std::string, std::shared_ptr<Material>>  MaterialManager::materials{};
std::shared_ptr<Material> MaterialManager::LoadMaterial(const std::string& filePath)
{
    auto it = materials.find(filePath);
    if (it != materials.end())
    {
        return it->second;
    }
    
    auto material = MaterialParser::LoadMaterial(filePath.c_str());
    materials[filePath] = material;
    return material;
}

std::shared_ptr<Material> MaterialManager::GetMaterial(const std::string& filePath)
{
    auto it = materials.find(filePath);
    return (it != materials.end()) ? it->second : nullptr;
}
