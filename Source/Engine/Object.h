#pragma once

#include "Mesh.h"
#include "Shader.h"

#include "Transform.h"
#include "glm/detail/func_packing_simd.inl"
#include "glm/vec3.hpp"

class Object
{
public:
    Object(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1))
        : transform(position, rotation, scale), mesh(std::make_shared<Mesh>(vertices, indices)) {}
    
    Transform transform;
    std::shared_ptr<Mesh> mesh;
    void Draw(Shader shader)
    {
        mesh->Draw(shader);
    }
    void SetMesh( std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) 
    {
        mesh.reset();
        mesh = std::make_shared<Mesh>(vertices, indices);
      
    }
};
