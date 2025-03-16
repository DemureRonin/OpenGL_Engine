#include "Prefab.h"

#include "Managers/AssetLoader.h"


void Prefab::SetParent(const std::shared_ptr<Prefab>& inParent)
{
    parent = inParent;
}

void Prefab::AddChild(const std::shared_ptr<Prefab>& child)
{
    children.push_back(child);
}

void Prefab::ApplyTransformations()
{
    glm::mat4 parentMat = glm::mat4(1.0f);
    if (HasParent())
    {
        parentMat = parent->objectMatrix;
    }
    objectMatrix = transform.ApplyTranslation(parentMat);
}

void Prefab::Draw() const
{
    if (mesh)
        mesh->Draw();
}

void Prefab::SetMesh(const std::shared_ptr<Mesh>& newMesh)
{
    auto prevMesh = mesh;
    this->mesh = newMesh;
    if (prevMesh == nullptr && newMesh != nullptr)
    {
        SetMaterial(std::static_pointer_cast<Material>(AssetLoader::GetAsset(Engine::GUID::FromString(MATERIAL_LIT))));
    }
}

void Prefab::SetMaterial(const std::shared_ptr<Material>& newMaterial)
{
    std::shared_ptr<Material> oldMaterial = this->material;
    this->material = newMaterial;
}
