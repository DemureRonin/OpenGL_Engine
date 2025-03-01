#pragma once

#include "Material.h"
#include "Mesh.h"
#include "Shader.h"

#include "Transform.h"
#include "glm/detail/func_packing_simd.inl"
#include "glm/vec3.hpp"

class Object
{
public:
    Object(glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1))
        : transform(position, rotation, scale){}
    
    Transform transform;
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;
    
    void Draw() const
    {
        mesh->Draw(material);
    }
    void SetMesh( const std::shared_ptr<Mesh>& newMesh) 
    {
        this->mesh.reset();
        this->mesh = newMesh;
    }
    void SetMaterial( const std::shared_ptr<Material>& newMaterial) 
    {
        this->material.reset();
        this->material = newMaterial;
    }
};
