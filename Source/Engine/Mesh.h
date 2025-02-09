#pragma once
#include <string>
#include <vector>

#include "IndexBuffer.h"
#include "Shader.h"
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
    VertexArray VAO;
    VertexBuffer VBO;
    IndexBuffer EBO;

    Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);
    void Draw(Shader& shader);
    
private:
    void SetupMesh();
    VertexBufferLayout layout;
   
};

