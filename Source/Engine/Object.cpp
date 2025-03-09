#include "Object.h"

#include "Managers/ObjectManager.h"

void Object::Draw()
{
    transform.ApplyTranslation();
    if (model->meshes[0])
        model->meshes[0]->Draw();
}

void Object::SetModel(const std::shared_ptr<Model>& newMesh)
{
    this->model = newMesh;
}

void Object::SetMaterial(const std::shared_ptr<Material>& newMaterial)
{
    /*if (!material && newMaterial)
    {
        this->material = newMaterial;
        ObjectManager::AddObjectToRender(GetSharedPtr());
        return;
    }*/
    this->material = newMaterial;
}
