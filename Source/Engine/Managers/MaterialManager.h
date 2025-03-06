#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include "../Material.h"
class MaterialManager
{
private:
    static std::unordered_map<std::string, std::shared_ptr<Material>> materials;

public:
    static std::shared_ptr<Material> LoadMaterial(const std::string& filePath);
    static std::shared_ptr<Material> GetMaterial(const std::string& filePath);
    
    
};
