#include "Object.h"

#include "Managers/AssetLoader.h"
#include "Managers/ObjectManager.h"

void Object::Draw()
{
    transform.ApplyTranslation();
    if (model->meshes[0])
        model->meshes[0]->Draw();
}

void Object::SetModel(const std::shared_ptr<Model>& newModel)
{
    auto prevModel = model;
    this->model = newModel;
    if (prevModel == nullptr && newModel != nullptr)
    {
        SetMaterial(std::static_pointer_cast<Material>(AssetLoader::GetAsset(Engine::GUID::FromString(MATERIAL_LIT))));
        ObjectManager::AddObjectToRender(this->GetSharedPtr());
    }
}

void Object::SetMaterial(const std::shared_ptr<Material>& newMaterial)
{
    std::shared_ptr<Material> oldMaterial = this->material;
    this->material = newMaterial; 

    ObjectManager::UpdateObjectMaterial(this->GetSharedPtr(), oldMaterial, newMaterial);
}

