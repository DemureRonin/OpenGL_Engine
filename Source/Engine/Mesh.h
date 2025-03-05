#pragma once
#include <string>
#include <vector>


#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "Buffers/VAO/VertexArray.h"
#include "Buffers/EBO/IndexBuffer.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"


struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 UV;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

class Mesh
{
private:
    VertexBufferLayout m_Layout;
    std::string m_FilePath;
    void SetupMesh();

public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<Texture>> textures;
    VertexArray VAO;
    VertexBuffer VBO;
    IndexBuffer EBO;

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::string& filePath);
    void Draw() const;
    std::string GetFilePath() { return m_FilePath; }
};
