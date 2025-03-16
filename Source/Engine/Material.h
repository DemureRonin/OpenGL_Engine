#pragma once

#include <memory>


#include "Shader.h"
#include "ShaderParams.h"
#include "../Parsers/MaterialParser.h"

class Material : public Asset
{
private:
    const char* m_DebugName = "MATERIAL";

public:
    std::shared_ptr<Shader> shader = nullptr;
    std::shared_ptr<ShaderParams> shaderParams = nullptr;


    Material(const std::string& path, Engine::GUID inGUID): Asset(path, AssetType::Material, inGUID)
    {
        if (!MaterialParser::ParseMaterial(path.c_str(), shader, shaderParams))
        {
            ConsoleDebug::PrintError(m_DebugName, (std::string("Material ") + path + " failed to load").c_str());
            loadedSuccessfully = false;
        }
    }

    bool operator<(const Material& other) const
    {
        return GetGUID().ToString() < other.GetGUID().ToString();
    }

    std::shared_ptr<ShaderParams> GetShaderParams() const { return shaderParams; }
    bool IsLoaded();
};
