#include "Scene.h"

#include "../Parsers/SceneParser.h"
#include "Managers/AssetLoader.h"

Scene::Scene(const std::string& assetPath, Engine::GUID inGUID, const std::shared_ptr<Camera>& inCamera,
             const DirectionalLight& inDirLight) : Asset(assetPath, AssetType::Scene, inGUID)
{
    camera = inCamera;
    dirLight = inDirLight;
    auto objects = SceneParser::ParseScene(assetPath.c_str());
    for (const auto& obj : objects)
    {
        AddObject(obj);
    }
}

void Scene::ApplyObjectTransformations(const std::shared_ptr<Prefab>& obj) const   
{
    obj->ApplyTransformations();
    for (const auto& child : obj->children)
    {
        ApplyObjectTransformations(child);
    }
}

void Scene::Render() const
{
    for (const auto& obj : rootObjects)
    {
        ApplyObjectTransformations(obj);
    }

    for (const auto& pair : materialObjectMap)
    {
        std::shared_ptr<Material> material = pair.first;
        std::vector<std::shared_ptr<Prefab>> objs = pair.second;
        material->shader->Bind();
        material->shader->SetMaterialUniforms(material);
        material->shader->SetDirectionalLightUniforms(dirLight);


        for (const auto& obj : objs)
        {
            if (obj->mesh == nullptr) continue;
            material->shader->SetObjectUniforms(*camera, *obj);
            obj->Draw();
        }
    }
}

void Scene::AddObject(const std::shared_ptr<Prefab>& object)
{
    if (!object) return;
    if (!object->HasParent())
    {
        rootObjects.push_back(object);
    }
    if (object->HasChildren())
    {
        for (const auto& child : object->children)
        {
            AddObject(child);
        }
    }
    sceneObjects.push_back(object);
    AddObjectToRender(object);
}

void Scene::RemoveObject(const std::shared_ptr<Prefab>& object)
{
    for (const auto& child : object->children)
    {
        RemoveObject(child);
    }
    if (object)
        std::erase(sceneObjects, object);
    if (object->material)
        RemoveObjectFromRender(object, object->material);
}

void Scene::AddObjectToRender(const std::shared_ptr<Prefab>& object)
{
    if (!object || !object->material) return;
    materialObjectMap[object->material].push_back(object);
}

void Scene::RemoveObjectFromRender(const std::shared_ptr<Prefab>& object, const std::shared_ptr<Material>& material)
{
    if (!object || !material) return;

    auto it = materialObjectMap.find(material);
    if (it != materialObjectMap.end())
    {
        auto& objects = it->second;
        std::erase(objects, object);

        if (objects.empty())
        {
            materialObjectMap.erase(it);
        }
    }
}

std::shared_ptr<Prefab> Scene::CreatePrimitive(Engine::GUID guid)
{
    std::string name = "Primitive";
    auto primitiveObject = AddEmpty(name);
    primitiveObject->SetMesh(std::static_pointer_cast<Model>(AssetLoader::GetAsset(guid))->meshes[0]);
    AddObjectToRender(primitiveObject);
    return primitiveObject;
}

std::shared_ptr<Prefab> Scene::CreateEmpty(const std::string& inName)
{
    return std::make_shared<Prefab>(Engine::GUID::Generate(), inName, glm::vec3(0),
                                    glm::vec3(0), glm::vec3(1));
}

std::shared_ptr<Prefab> Scene::AddEmpty(const std::string& inName)
{
    auto object = std::make_shared<Prefab>(Engine::GUID::Generate(), inName, glm::vec3(0),
                                           glm::vec3(0), glm::vec3(1));
    AddObject(object);
    return object;
}

void Scene::UpdateObjectMaterial(const std::shared_ptr<Prefab>& object, const std::shared_ptr<Material>& oldMaterial,
                                 const std::shared_ptr<Material>& newMaterial)
{
    if (!object) return;

    if (oldMaterial)
    {
        RemoveObjectFromRender(object, oldMaterial);
    }

    if (newMaterial)
    {
        AddObjectToRender(object);
    }
}

std::shared_ptr<Prefab> Scene::AddChild(const std::shared_ptr<Prefab>& parent, const std::string& inName)
{
    if (!parent)
    {
        std::cerr << "Error: Attempted to add a child to a null parent!" << std::endl;
        return nullptr;
    }

    auto child = std::make_shared<Prefab>(Engine::GUID::Generate(), inName, glm::vec3(0),
                                          glm::vec3(0), glm::vec3(1));

    std::cout << "Adding child: " << child->name << " to parent: " << parent->name << std::endl;

    child->SetParent(parent);
    parent->AddChild(child);
    AddObject(child);
    return child;
}

std::shared_ptr<Prefab> Scene::AddModel(const std::shared_ptr<Model>& model)
{
    auto parent = AddEmpty(model->name);
    auto name = "Mesh";
    int i = 0;
    for (const auto& mesh : model->meshes)
    {
        auto child = AddChild(parent, name + std::to_string(i++));

        child->SetMesh(mesh);
        AddObjectToRender(child);
    }
    return parent;
}
