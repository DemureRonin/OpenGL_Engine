#pragma once
#include "Shader.h"

class DirectionalLight
{
public:
    DirectionalLight(glm::vec3 direction = glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3 ambient = glm::vec3(0.2f, 0.2f, 0.2f),
        glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f))
    {
        this->direction = direction;
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
    }

    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};
