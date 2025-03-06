#pragma once

#include <memory>


#include "Shader.h"
#include "ShaderParams.h"

class Material
{
private:
    unsigned int m_ID;
    std::string m_FilePath;

public:
    std::shared_ptr<Shader> shader = nullptr;
    std::shared_ptr<ShaderParams> shaderParams;


    Material(unsigned int ID, std::shared_ptr<Shader> sh,
             std::shared_ptr<ShaderParams>& params): m_ID(ID)
    {
        shaderParams = params;
        shader = sh;
    }

    bool operator<(const Material& other) const
    {
        return m_ID < other.GetID();
    }

    unsigned int GetID() const { return m_ID; }
    std::string GetFilePath() const { return m_FilePath; }
    bool IsLoaded();
};
