#pragma once
#include <string>
#include <vector>

#include "IndexBuffer.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"


struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 UV;
};

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<Texture>> textures;
    VertexArray VAO;
    VertexBuffer VBO;
    IndexBuffer EBO;

    Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);
    void Draw(const std::shared_ptr<Material>& material) const;
    
private:
    void SetupMesh();
    VertexBufferLayout m_Layout;
   
};

