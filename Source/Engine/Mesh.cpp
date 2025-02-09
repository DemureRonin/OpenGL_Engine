#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
    : vertices(std::move(vertices)), indices(std::move(indices)),
      VBO(this->vertices.data(), this->vertices.size() * sizeof(Vertex)),
      EBO(this->indices.data(), this->indices.size())
{
    SetupMesh();
}

void Mesh::Draw(Shader& shader)
{
    shader.Bind();
    VAO.Bind();
    EBO.Bind();

    glDrawElements(GL_TRIANGLES, EBO.GetCount(), GL_UNSIGNED_INT, nullptr);
    VAO.Unbind();
}

void Mesh::SetupMesh()
{
    layout.Push(GL_FLOAT, 3);
    layout.Push(GL_FLOAT, 3);
    layout.Push(GL_FLOAT, 2);

    VAO.AddVertexBuffer(VBO, layout);
}
