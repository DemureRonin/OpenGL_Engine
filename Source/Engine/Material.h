#pragma once

#include <memory>


#include "Shader.h"
#include "ShaderParams.h"

class Material : public Asset
{
public:
    std::shared_ptr<Shader> shader = nullptr;
    std::shared_ptr<ShaderParams> shaderParams = nullptr;

   

    Material(const std::string& path, Engine::GUID inGUID, const std::shared_ptr<Shader>& sh,
             const std::shared_ptr<ShaderParams>& params): Asset(path, AssetType::Material, inGUID)
    {
        shaderParams = params;
        shader = sh;
    }

    bool operator<(const Material& other) const
    {
        return GetGUID().ToString() < other.GetGUID().ToString();
    }
    
    bool IsLoaded();
};
