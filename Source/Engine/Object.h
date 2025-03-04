#pragma once

#include "Material.h"
#include "Mesh.h"
#include "Shader.h"

#include "Transform.h"
#include "glm/detail/func_packing_simd.inl"

class Object
{
public:
    Object(std::string& name, glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0),
           glm::vec3 scale = glm::vec3(1))
        : name(name), transform(position, rotation, scale)
    {
        transform.ApplyTranslation();
    }

    std::string name = "Object";
    std::string m_FilePath;
    Transform transform;
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;
    std::string GetFilePath() { return m_FilePath; }
    void Draw()
    {
        transform.ApplyTranslation();
        mesh->Draw(material);
    }

    void SetMesh(const std::shared_ptr<Mesh>& newMesh)
    {
        this->mesh.reset();
        this->mesh = newMesh;
    }

    void SetMaterial(const std::shared_ptr<Material>& newMaterial)
    {
        this->material.reset();
        this->material = newMaterial;
    }
};
