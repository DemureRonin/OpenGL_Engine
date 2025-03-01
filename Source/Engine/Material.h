#pragma once
#include <memory>
#include <vector>

#include "Shader.h"
#include "Texture.h"

class Material
{
public:
    glm::vec4 tint;
    float shininess;
    std::shared_ptr<Shader> shader;
    std::vector<std::shared_ptr<Texture>> textures;

    Material(const std::shared_ptr<Shader>& shader, const std::vector<std::shared_ptr<Texture>>& textures,
             glm::vec4 tint = glm::vec4(1.0f), float shininess = 1.0f)
        : tint(tint), shininess(shininess)
    {
        this->shader = shader;
        this->textures = textures;
    }
};
