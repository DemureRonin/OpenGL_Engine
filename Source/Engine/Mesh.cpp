#include "Mesh.h"

#include "Material.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
    : vertices(vertices), indices(indices),
      VBO(this->vertices.data(), this->vertices.size() * (sizeof(Vertex))),
      EBO(this->indices.data(), this->indices.size())
{
    SetupMesh();
}

void Mesh::Draw(const std::shared_ptr<Material>& material) const
{
    VAO.Bind();
    EBO.Bind();

    glDrawElements(GL_TRIANGLES, EBO.GetCount(), GL_UNSIGNED_INT, nullptr);
    VAO.Unbind();
}

void Mesh::SetupMesh()
{
    m_Layout.Push(GL_FLOAT, 3);
    m_Layout.Push(GL_FLOAT, 3);
    m_Layout.Push(GL_FLOAT, 2);
    m_Layout.Push(GL_FLOAT, 3);
    m_Layout.Push(GL_FLOAT, 3);

    VAO.AddVertexBuffer(VBO, m_Layout);
}
