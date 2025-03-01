#include "Mesh.h"

#include "Material.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
    : vertices(std::move(vertices)), indices(std::move(indices)),
      VBO(this->vertices.data(), this->vertices.size() * sizeof(Vertex)),
      EBO(this->indices.data(), this->indices.size())
{
    SetupMesh();
}

void Mesh::Draw(const std::shared_ptr<Material>& material) const
{
    material->shader->Bind();
    for (unsigned int i = 0; i < material->textures.size(); i ++)
    {
        material->textures[i]->Bind(material->textures[i]->GetType());
        switch (material->textures[i]->GetType())
        {
        case ALBEDO:
            material->shader->SetInt("material.albedo", ALBEDO);
            break;
        case NORMAL:
            material->shader->SetInt("material.normal", NORMAL);
            break;
        case ROUGHNESS:
            material->shader->SetInt("material.roughness", ROUGHNESS);
            break;
        case METALLIC:
            material->shader->SetInt("material.metallic", METALLIC);
            break;
        case SPECULAR:
            material->shader->SetInt("material.specular", SPECULAR);
            break;
        }
    }
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

    VAO.AddVertexBuffer(VBO, m_Layout);
}
