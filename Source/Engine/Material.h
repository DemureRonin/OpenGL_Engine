#pragma once
#include <memory>
#include <vector>

#include "Shader.h"
#include "Texture.h"

class Material
{
private:
    unsigned int m_ID;
   

public:
    std::string m_FilePath;
    glm::vec4 tint;
    float shininess;
    float metallicProperty;
    float normalScale;
    std::shared_ptr<Shader> shader;
    std::vector<std::shared_ptr<Texture>> textures;
    unsigned int GetID() const { return m_ID; }
    std::string GetFilePath() const { return m_FilePath; }
    Material(const std::shared_ptr<Shader>& shader, const std::vector<std::shared_ptr<Texture>>& textures,float metallicProperty, float normalScale,
             unsigned int ID,
             glm::vec4 tint = glm::vec4(1.0f), float shininess = 1.0f)
        : tint(tint), shininess(shininess), metallicProperty(metallicProperty), normalScale(normalScale), m_ID(ID)
    {
        this->shader = shader;
        this->textures = textures;
    }

    bool operator<(const Material& other) const {
        return m_ID < other.GetID();
    }
};
